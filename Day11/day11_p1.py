import sys

NUM_BLINKS = 25


def update_arrangement(arrangement):
    new_arrangement = []
    for stone in arrangement:
        if stone == 0:
            new_arrangement.append(1)
        elif len(str(stone)) % 2 == 0:
            stone = str(stone)
            new_arrangement.append(int(stone[:len(stone)//2]))
            new_arrangement.append(int(stone[len(stone)//2:]))
        else:
            new_arrangement.append(stone * 2024)
    return new_arrangement


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print(f'Usage: {sys.argv[0]} <arrangement.txt>')
        sys.exit(1)

    with open(sys.argv[1]) as f:
        arrangement = list(map(int, f.read().split()))

    for i in range(NUM_BLINKS):
        arrangement = update_arrangement(arrangement)

    print(f'Number of stones after {NUM_BLINKS} blinks: {len(arrangement)}')
