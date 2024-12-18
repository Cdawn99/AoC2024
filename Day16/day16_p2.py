from day16 import dijkstra, Direction
import sys
from collections import deque

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print(f'Usage: {sys.argv[0]} <map.txt>')
        sys.exit(1)

    with open(sys.argv[1]) as f:
        maze = f.read().strip().split('\n')

    height = len(maze)
    width = len(maze[0])

    dist, pred = dijkstra(maze, width, height)

    end_1 = (width - 2, 1, Direction.EAST)
    end_2 = (width - 2, 1, Direction.NORTH)

    end_dist_1 = dist[end_1]
    end_dist_2 = dist[end_2]

    q = deque()
    if end_dist_1 <= end_dist_2:
        q.append(end_1)
    if end_dist_1 >= end_dist_2:
        q.append(end_2)

    tiles = set()
    while len(q) != 0:
        p = q.popleft()
        tiles.add(p[:2])
        for v in pred[p]:
            q.append(v)

    print(f'Number of tiles: {len(tiles)}')
