import math


def get_base6_digit_count(n: int) -> int:
    return math.floor(math.log(n, 6)) + 1


def base6_digit_from_colour(c: str) -> int:
    match c:
        case 'w': return 1
        case 'u': return 2
        case 'b': return 3
        case 'r': return 4
        case 'g': return 5
    raise RuntimeError('Invalid digit')


def colour_from_base6_digit(i: int) -> str:
    match i:
        case 1: return 'w'
        case 2: return 'u'
        case 3: return 'b'
        case 4: return 'r'
        case 5: return 'g'
    raise RuntimeError('Invalid digit')


def base6_str_to_base10_int(s: str) -> int:
    n = 0
    for c in s:
        n *= 6
        n += base6_digit_from_colour(c)
    return n


def base10_int_to_base6_str(i: int) -> str:
    s = ''
    while i > 0:
        d = i % 6
        s = colour_from_base6_digit(d) + s
        i //= 6
    return s
