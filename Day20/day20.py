from collections import deque
from collections.abc import Iterator


class Position:
    def __init__(self, x: int, y: int):
        self.x = x
        self.y = y

    def is_within_walls(self, width: int, height: int) -> bool:
        return 0 < self.x < width - 1 and 0 < self.y < height - 1

    def l1_norm(self) -> int:
        return abs(self.x) + abs(self.y)

    def __add__(self, other):
        if isinstance(other, Position):
            return Position(self.x + other.x, self.y + other.y)
        else:
            return NotImplemented

    def __sub__(self, other):
        if isinstance(other, Position):
            return Position(self.x - other.x, self.y - other.y)
        else:
            return NotImplemented

    def __neg__(self):
        return Position(-self.x, -self.y)

    def __eq__(self, other):
        if isinstance(other, Position):
            return self.x == other.x and self.y == other.y
        else:
            return NotImplemented

    def __str__(self):
        return f'({self.x}, {self.y})'

    def __repr__(self):
        return f'Position({self.x}, {self.y})'


class Direction:
    EAST = Position(1, 0)
    WEST = Position(-1, 0)
    NORTH = Position(0, -1)
    SOUTH = Position(0, 1)


DIRS = [Direction.EAST, Direction.NORTH, Direction.WEST, Direction.SOUTH]


def get_initial_cheating_info(racetrack: list[str]) -> tuple[Position, Position, Direction]:
    current = None
    end = None
    for y, row in enumerate(racetrack[1:-1], start=1):
        for x, tile in enumerate(row[1:-1], start=1):
            if tile == 'S':
                current = Position(x, y)
            elif tile == 'E':
                end = Position(x, y)
            if current is not None and end is not None:
                break
        if current is not None and end is not None:
            break

    direction = None
    for d in DIRS:
        pos = current + d
        if racetrack[pos.y][pos.x] == '.':
            direction = d
            break

    if current is None or end is None or direction is None:
        raise RuntimeError(
            'ERROR: one of start/end/initial direction was not found\n'
            f'start: {current}, end: {end}, initial direction: {direction}'
        )

    return current, end, direction


def get_cheats_1(racetrack: list[str]) -> Iterator[tuple[Position, Position, Direction]]:
    current, end, direction = get_initial_cheating_info(racetrack)

    height = len(racetrack)
    width = len(racetrack[0])
    visited = []
    while current != end:
        next_dir = direction
        for d in DIRS:
            if d == -direction:
                continue
            pos = current + d
            pos2 = pos + d
            if direction != d and racetrack[pos.y][pos.x] == '.':
                next_dir = d
            elif pos.is_within_walls(width, height) and racetrack[pos.y][pos.x] == '#' and (racetrack[pos2.y][pos2.x] == '.' or racetrack[pos2.y][pos2.x] == 'E') and pos2 not in visited:
                yield current, pos2, direction
        direction = next_dir
        visited.append(current)
        current += direction


def get_cheat_destinations(racetrack: list[str], src: Position, max_cheat_dist: int) -> Iterator[Position]:
    height = len(racetrack)
    width = len(racetrack[0])

    dist = {(x, y): max_cheat_dist for x in range(1, width - 1) for y in range(1, height - 1)}
    dist[(src.x, src.y)] = 0
    visited = {(x, y): False for x in range(1, width - 1) for y in range(1 ,height - 1)}

    q = deque()
    q.append((src.x, src.y))
    while len(q) > 0:
        pos = q.popleft()
        for d in DIRS:
            n = (pos[0] + d.x, pos[1] + d.y)
            if not Position(*n).is_within_walls(width, height) or visited[n]:
                continue
            d = dist[pos] + 1
            if d < dist[n]:
                dist[n] = d
                if n not in q:
                    q.append(n)
                if racetrack[n[1]][n[0]] != '#':
                    yield Position(*n)
        visited[pos] = True


def get_cheats_2(racetrack: list[str], max_cheat_dist: int) -> Iterator[tuple[Position, Position, Direction]]:
    current, end, direction = get_initial_cheating_info(racetrack)

    visited = []
    while current != end:
        next_dir = direction
        for d in DIRS:
            if d == -direction:
                continue
            pos = current + d
            if direction != d and racetrack[pos.y][pos.x] == '.':
                next_dir = d
        direction = next_dir

        for cheat_dest in get_cheat_destinations(racetrack, current, max_cheat_dist):
            if cheat_dest not in visited:
                yield current, cheat_dest, direction

        visited.append(current)
        current += direction


def path_len(racetrack: list[str], cheat_info: tuple[Position, Position, Direction]) -> int:
    path_length = 0

    s, e, d = cheat_info

    while s != e:
        next_pos = s + d
        if racetrack[next_pos.y][next_pos.x] == '#':
            match d:
                case Direction.EAST | Direction.WEST:
                    p = s + Direction.NORTH
                    d = Direction.NORTH if racetrack[p.y][p.x] == '.' or racetrack[p.y][p.x] == 'E' else Direction.SOUTH
                case Direction.NORTH | Direction.SOUTH:
                    p = s + Direction.EAST
                    d = Direction.EAST if racetrack[p.y][p.x] == '.' or racetrack[p.y][p.x] == 'E' else Direction.WEST
        s += d
        path_length += 1

    return path_length
