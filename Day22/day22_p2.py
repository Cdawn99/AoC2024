from day22 import compute_next_secret

import sys
import numpy as np

REPEAT_COUNT = 2000

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print(f'Usage: {sys.argv[0]} <secret_numbers.txt>')
        sys.exit(1)

    with open(sys.argv[1]) as f:
        init_nums = f.read().strip().split('\n')
    init_nums = np.array([i for i in map(np.int64, init_nums)])

    nums = [init_nums]
    for _ in range(REPEAT_COUNT):
        nums.append(compute_next_secret(nums[-1]))
    nums = np.stack(nums)
    nums = nums % 10
    diffs = nums[1:] - nums[:-1]

    nums = nums.transpose()
    diffs = diffs.transpose()

    buyer_info = []
    seqs = set()
    for b, d in zip(nums, diffs):
        info = {}
        for i, p in enumerate(b[4:], start=0):
            sequence = tuple(n for n in d[i:i+4])
            if info.get(sequence) is not None:
                continue
            info[sequence] = p
            seqs.add(sequence)
        buyer_info.append(info)

    bananas = []
    for s in seqs:
        t = 0
        for i in buyer_info:
            p = i.get(s)
            t += p if p is not None else 0
        bananas.append(t)

    print(f'Maximum possible amount of bananas that can be get: {max(bananas)}')
