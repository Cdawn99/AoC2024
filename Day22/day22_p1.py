from day22 import compute_next_secret

import sys
import numpy as np

REPEAT_COUNT = 2000

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print(f'Usage: {sys.argv[0]} <secret_numbers.txt>')
        sys.exit(1)

    with open(sys.argv[1]) as f:
        numbers = f.read().strip().split('\n')

    numbers = np.array([i for i in map(np.uint64, numbers)])

    for _ in range(REPEAT_COUNT):
        numbers = compute_next_secret(numbers)

    print(f'Sum of secret numbers: {int(sum(numbers))}')
