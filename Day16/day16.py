import sys


class Direction:
    EAST = (1, 0)
    NORTH = (0, -1)
    WEST = (-1, 0)
    SOUTH = (0, 1)


def turn(direction: Direction, towards: str):
    if towards != 'left' and towards != 'right':
        raise RuntimeError('ERROR: Invalid turning direction')
    match direction:
        case Direction.EAST:
            return Direction.NORTH if towards == 'left' else Direction.SOUTH
        case Direction.NORTH:
            return Direction.WEST if towards == 'left' else Direction.EAST
        case Direction.WEST:
            return Direction.SOUTH if towards == 'left' else Direction.NORTH
        case Direction.SOUTH:
            return Direction.EAST if towards == 'left' else Direction.WEST
    raise RuntimeError('ERROR: Invalid direction')


def get_neighbors(pos: tuple[int, int, Direction]) -> list[tuple[int, int, Direction]]:
    forward = (pos[0] + pos[2][0], pos[1] + pos[2][1], pos[2])
    left = (pos[0], pos[1], turn(pos[2], 'left'))
    right = (pos[0], pos[1], turn(pos[2], 'right'))

    return [forward, left, right]


def dijkstra(maze: list[str], width: int, height: int) -> tuple[dict, dict]:
    dist = {
        (x, y, d): sys.maxsize
        for x in range(width)
        for y in range(height)
        for d in [Direction.EAST, Direction.NORTH, Direction.WEST, Direction.SOUTH]
    }
    dist[(1, height - 2, Direction.EAST)] = 0

    visited = {
        (x, y, d): False
        for x in range(width)
        for y in range(height)
        for d in [Direction.EAST, Direction.NORTH, Direction.WEST, Direction.SOUTH]
    }

    pred = {
        (x, y, d): None
        for x in range(width)
        for y in range(height)
        for d in [Direction.EAST, Direction.NORTH, Direction.WEST, Direction.SOUTH]
    }
    pred[(1, height - 2, Direction.EAST)] = []

    q = [(1, height - 2, Direction.EAST)]
    while len(q) > 0:
        # print(q)
        pos = q.pop(0)
        neighbors = get_neighbors(pos)
        neighbors.sort(key=lambda n: dist[n])
        for n in neighbors:
            if visited[n] or maze[n[1]][n[0]] == '#':
                continue
            if n not in q and maze[n[1]][n[0]] != 'E':
                q.append(n)
            d = dist[pos]
            if pos[0] == n[0] and pos[1] == n[1]:
                d += 1000
            else:
                d += 1
            if d < dist[n]:
                dist[n] = d
                pred[n] = [pos]
            elif d == dist[n]:
                pred[n].append(pos)
        visited[pos] = True
        q.sort(key=lambda n: dist[n])

    return dist, pred
