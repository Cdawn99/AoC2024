from day16 import dijkstra, Direction
import sys


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print(f'Usage: {sys.argv[0]} <map.txt>')
        sys.exit(1)

    with open(sys.argv[1]) as f:
        maze = f.read().strip().split('\n')

    height = len(maze)
    width = len(maze[0])

    dist, _ = dijkstra(maze, width, height)

    score1 = dist[(width - 2, 1, Direction.EAST)]
    score2 = dist[(width - 2, 1, Direction.NORTH)]

    min_score = score1 if score1 < score2 else score2
    print(f'Lowest score a Reindeer could get: {min_score}')
