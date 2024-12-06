import sys
import re

if __name__ == '__main__':
    if len(sys.argv) == 1:
        print(f'Usage: {sys.argv[0]} <mem.txt>')
        sys.exit(1)

    mem_path = sys.argv[1]

    with open(mem_path, 'r') as f:
        mem = f.read()

    sum_mul = 0
    do_sum = True
    for x in re.finditer(r'do\(\)|don\'t\(\)|mul\((\d{1,3}),(\d{1,3})\)', mem):
        match x[0]:
            case 'do()':
                do_sum = True
            case 'don\'t()':
                do_sum = False
            case _:
                if do_sum:
                    sum_mul += int(x[1]) * int(x[2])

    print(f'Sum of multiplications: {sum_mul}')
