import sys
from functools import cache


@cache
def do_design_is_possible(d: str, m: str, ps: tuple) -> bool:
    if d == m:
        return True

    matches = [
        m + p
        for p in ps
        if d[:len(m + p)] == m + p
    ]

    result = False
    for ms in matches:
        result = result or do_design_is_possible(d, ms, ps)
        if result:
            break

    return result


def design_is_possible(d: str, ps: tuple):
    matches = [
        p
        for p in ps
        if d[:len(p)] == p
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

    patterns = tuple(i for i in patterns.split(', '))
    designs = designs.split('\n')

    possible_count = 0
    for d in designs:
        if design_is_possible(d, patterns):
            possible_count += 1

    print(f'Number of possible designs: {possible_count}')
