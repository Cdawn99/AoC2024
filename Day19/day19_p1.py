from day19 import base6_str_to_base10_int, get_base6_digit_count

import sys
from functools import cache


@cache
def do_design_is_possible(d: int, m: int, ps: tuple) -> bool:
    dcount = get_base6_digit_count(d)
    mcount = get_base6_digit_count(m)
    if dcount == mcount:
        return d == m

    matches = [
        p * 6**mcount + m
        for p in ps
        if p * 6**mcount + m == d % 6**(mcount + get_base6_digit_count(p))
    ]

    result = False
    for ms in matches:
        result = result or do_design_is_possible(d, ms, ps)
        if result:
            break

    return result


def design_is_possible(d: int, ps: tuple):
    matches = [
        p
        for p in ps
        if d % 6**get_base6_digit_count(p) == p
    ]
    for m in matches:
        if do_design_is_possible(d, m, ps):
            return True
    return False


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print(f'Usage: python3 {sys.argv[0]} <input.txt>')
        sys.exit(1)

    with open(sys.argv[1]) as f:
        patterns, designs = f.read().strip().split('\n\n')

    patterns = tuple(i for i in map(base6_str_to_base10_int, patterns.split(', ')))
    designs = [i for i in map(base6_str_to_base10_int, designs.split('\n'))]

    possible_count = 0
    for d in designs:
        if design_is_possible(d, patterns):
            possible_count += 1

    print(f'Number of possible designs: {possible_count}')
