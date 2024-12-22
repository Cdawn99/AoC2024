def mix(a, b): return a ^ b
def prune(a): return a % 16777216


def compute_next_secret(n):
    a = n * 64
    n = mix(n, a)
    n = prune(n)

    b = n // 32
    n = mix(n, b)
    n = prune(n)

    c = n * 2048
    n = mix(n, c)
    n = prune(n)

    return n
