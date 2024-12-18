import sys
from collections import deque


def get_neighbors(pos: tuple[int, int], width: int, height: int) -> list[tuple[int, int]]:
    neighbors = []

    right = (pos[0] + 1, pos[1])
    if (0 <= right[0] < width and 0 <= right[1] < height):
        neighbors.append(right)

    down = (pos[0], pos[1] + 1)
    if (0 <= down[0] < width and 0 <= down[1] < height):
        neighbors.append(down)

    left = (pos[0] - 1, pos[1])
    if (0 <= left[0] < width and 0 <= left[1] < height):
        neighbors.append(left)

    up = (pos[0], pos[1] - 1)
    if (0 <= up[0] < width and 0 <= up[1] < height):
        neighbors.append(up)

    return neighbors


def compute_min_steps(mem_space: list[list[int]], width: int, height: int) -> int:
    dist = {(x, y): sys.maxsize for x in range(width) for y in range(height)}
    dist[(0, 0)] = 0
    visited = {(x, y): False for x in range(width) for y in range(height)}

    q = deque()
    q.append((0, 0))
    while len(q) > 0:
        pos = q.popleft()
        for n in get_neighbors(pos, width, height):
            if visited[n] or mem_space[n[1]][n[0]] == -1:
                continue
            if n not in q:
                q.append(n)
            d = dist[pos] + 1
            if d < dist[n]:
                dist[n] = d
        visited[pos] = True

    return dist[(width - 1, height - 1)]
