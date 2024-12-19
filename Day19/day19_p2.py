from day19 import base6_str_to_base10_int, get_base6_digit_count

import sys
from functools import cache


@cache
def do_design_combination_count(d: int, m: int, ps: tuple) -> bool:
    if d == m:
        return 1

    mcount = get_base6_digit_count(m)

    matches = [
        p * 6**mcount + m
        for p in ps
        if p * 6**mcount + m == d % 6**(mcount + get_base6_digit_count(p))
    ]

    count = 0
    for ms in matches:
        count += do_design_combination_count(d, ms, ps)

    return count


def design_combination_count(d: int, ps: tuple):
    matches = [
        p
        for p in ps
        if d % 6**get_base6_digit_count(p) == p
    ]
    count = 0
    for m in matches:
        count += do_design_combination_count(d, m, ps)
    return count


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print(f'Usage: python3 {sys.argv[0]} <input.txt>')
        sys.exit(1)

    with open(sys.argv[1]) as f:
        patterns, designs = f.read().strip().split('\n\n')

    patterns = tuple(i for i in map(base6_str_to_base10_int, patterns.split(', ')))
    designs = [i for i in map(base6_str_to_base10_int, designs.split('\n'))]

    combination_count = 0
    for d in designs:
        combination_count += design_combination_count(d, patterns)

    print(f'Number of possible designs: {combination_count}')
