from day18 import compute_min_steps

import sys

NUM_BYTES = 1024

if __name__ == '__main__':
    if len(sys.argv) < 4:
        print(f'Usage {sys.argv[0]} <bytes.txt> <width> <height>')
        sys.exit(1)

    with open(sys.argv[1]) as f:
        falling_bytes = f.read().strip().split('\n')

    width = int(sys.argv[2])
    height = int(sys.argv[3])

    mem_space = [[0] * width for _ in range(height)]

    count = 0
    for byte in falling_bytes:
        x, y = map(int, byte.split(','))
        mem_space[y][x] = -1
        count += 1
        if count == NUM_BYTES:
            break

    min_steps = compute_min_steps(mem_space, width, height)
    while min_steps != sys.maxsize and count != len(falling_bytes):
        x, y = map(int, falling_bytes[count].split(','))
        mem_space[y][x] = -1
        min_steps = compute_min_steps(mem_space, width, height)
        count += 1

    print(f'First byte to cut the path off: {falling_bytes[count - 1]}')
