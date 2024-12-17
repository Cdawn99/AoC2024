def run(a: int, b: int):
    output = ''
    while a != 0:
        b = (a % 8) ^ (a // (2**((a % 8) ^ 5))) ^ 3
        if len(output) == 0:
            output = str(b % 8)
        else:
            output += f',{b % 8}'
        a = a // 8
    return output


if __name__ == '__main__':
    expected = '2,4,1,5,7,5,0,3,4,0,1,6,5,5,3,0'

    ras = []
    for i in range(1, 8):
        output = run(i, 0)
        if output == expected[-len(output):]:
            ras.append(i)

    octal_digit_count = 1
    while octal_digit_count < 16:
        new_ras = []
        for a in ras:
            a *= 8
            for i in range(8):
                output = run(a + i, 0)
                if output == expected[-len(output):]:
                    new_ras.append(a + i)
        ras = new_ras
        octal_digit_count += 1

    # print(f'len(ras) = {len(ras)}')
    # print(f'ras = {ras}')
    # print(f'----------------------------------------')

    a = min(ras)
    print(f'a = {a}')
    print(f'acutal   = {run(a, 0)}')
    print(f'expected = {expected}')
    print()
