from day20 import get_cheats_2, path_len

import sys

MAX_CHEAT_DIST = 20

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print(f'Usage: {sys.argv[0]} <map.txt>')
        sys.exit(1)

    with open(sys.argv[1]) as f:
        racetrack = f.read().strip().split('\n')

    # d = {}
    # for cheat in get_cheats_2(racetrack, MAX_CHEAT_DIST + 1):
    #     time_saved = path_len(racetrack, cheat) - (cheat[1] - cheat[0]).l1_norm()
    #     if time_saved < 50:
    #         continue
    #     # print(f'Cheat: {cheat}')
    #     # print(f'Time saved: {time_saved}')
    #     # print('------------------------------')
    #     if d.get(time_saved) is None:
    #         d[time_saved] = 0
    #     d[time_saved] += 1

    # for k, v in d.items():
    #     print(f'There are {v} cheats that save {k}ps.')

    good_cheat_count = 0
    count = 0
    for cheat in get_cheats_2(racetrack, MAX_CHEAT_DIST + 1):
        count += 1
        time_saved = path_len(racetrack, cheat) - (cheat[1] - cheat[0]).l1_norm()
        if time_saved >= 100:
            good_cheat_count += 1
        if count % 1000 == 0:
            print(f'count = {count}')
            print(f'good  = {good_cheat_count}')
            print('------------------------------')

    print(f'Number of cheats that save at least 100ps: {good_cheat_count}')
