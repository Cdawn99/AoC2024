from day17 import match_to_int, Interpreter

import sys
import re

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print(f'Usage: {sys.argv[0]} <info.txt>')
        sys.exit(1)

    with open(sys.argv[1]) as f:
        info = f.read()

    data = map(match_to_int, re.finditer(r'\d+', info))

    interpreter = Interpreter(next(data), next(data), next(data))
    instructions = list(data)

    ip = 0
    while ip < len(instructions):
        ip = interpreter.step(ip, instructions[ip], instructions[ip + 1])

    print(interpreter.output)
