from day18 import compute_min_steps

import sys

if __name__ == '__main__':
    if len(sys.argv) < 5:
        print(f'Usage {sys.argv[0]} <bytes.txt> <width> <height> <num_bytes>')
        sys.exit(1)

    with open(sys.argv[1]) as f:
        falling_bytes = f.read().strip().split('\n')

    width = int(sys.argv[2])
    height = int(sys.argv[3])
    num_bytes = int(sys.argv[4])

    mem_space = [[0] * width for _ in range(height)]

    count = 0
    for byte in falling_bytes:
        x, y = map(int, byte.split(','))
        mem_space[y][x] = -1
        count += 1
        if count == num_bytes:
            break

    min_steps = compute_min_steps(mem_space, width, height)
    print(f'Shortest path takes {min_steps} steps')
