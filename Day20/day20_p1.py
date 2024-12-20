from day20 import get_cheats_1, path_len

import sys

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print(f'Usage: {sys.argv[0]} <map.txt>')
        sys.exit(1)

    with open(sys.argv[1]) as f:
        racetrack = f.read().strip().split('\n')

    good_cheat_count = 0
    for cheat in get_cheats_1(racetrack):
        time_saved = path_len(racetrack, cheat) - 2
        if time_saved >= 100:
            good_cheat_count += 1

    print(f'Number of cheats that save at least 100ps: {good_cheat_count}')
