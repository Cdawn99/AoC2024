import sys
import re

if __name__ == '__main__':
    if len(sys.argv) == 1:
        print(f'Usage: {sys.argv[0]} <mem.txt>')
        sys.exit(1)

    mem_path = sys.argv[1]

    with open(mem_path, 'r') as f:
        mem = f.read()

    mem_clean = re.findall(r'mul\((\d{1,3}),(\d{1,3})\)', mem)

    sum_mul = 0
    for x, y in mem_clean:
        sum_mul += int(x) * int(y)

    print(f'Sum of multiplications: {sum_mul}')
