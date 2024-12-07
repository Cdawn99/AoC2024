import sys


def evaluate(numbers, ops):
    val = int(numbers[0])
    for num, op in zip(numbers[1:], ops):
        match op:
            case '+':
                val += int(num)
            case '*':
                val *= int(num)
            case '||':
                val = int(str(val) + num)
    return val


def gen_ops(opcount):
    ops = ['*'] * opcount
    final_ops = ['||'] * opcount
    while ops != final_ops:
        yield ops
        for i in range(opcount):
            carry = 1 if ops[i] == '||' else 0
            ops[i] = '||' if ops[i] == '+' else '+' if ops[i] == '*' else '*'
            if carry == 0:
                break
    yield ops


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print(f'Usage: {sys.argv[0]} <equations.txt>')
        sys.exit(1)

    with open(sys.argv[1], 'r') as f:
        equations = f.read().splitlines()

    calibration = 0
    for equation in equations:
        value, numbers = equation.split(': ')

        value = int(value)
        numbers = numbers.split(' ')

        is_valid = False
        opcount = len(numbers) - 1

        for ops in gen_ops(opcount):
            result = evaluate(numbers, ops)
            if result == value:
                is_valid = True
                calibration += value
                break

    print(f'Total calibration result: {calibration}')
