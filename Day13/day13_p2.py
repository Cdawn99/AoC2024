import sys
import re
import numpy as np
from numpy.linalg import solve

CORRECTION = 10000000000000


def cost(a, b):
    return 3 * a + b


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print(f'Usage: {sys.argv[0]} <machine_info.txt>')
        sys.exit(1)

    with open(sys.argv[1]) as f:
        machine_info = f.read().strip().split('\n\n')

    min_token_count = 0
    for info in machine_info:
        button_a, button_b, prize = info.split('\n')

        button_a = re.findall(r'(\d+)\D*(\d+)', button_a)[0]
        button_b = re.findall(r'(\d+)\D*(\d+)', button_b)[0]
        prize = re.findall(r'(\d+)\D*(\d+)', prize)[0]

        button_a = np.int64(button_a)
        button_b = np.int64(button_b)
        prize = np.int64(prize) + CORRECTION

        AB = np.column_stack((button_a, button_b))

        solution = np.rint(solve(AB, prize))
        if np.all(AB @ solution == prize):
            min_token_count += cost(*solution)

    print(f'Fewest token to spend: {min_token_count}')
