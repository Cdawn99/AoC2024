import sys
import numpy as np

if __name__ =='__main__':
    if len(sys.argv) != 2:
        print(f'Usage: {sys.argv[0]} <map.txt>')
        sys.exit(1)

    with open(sys.argv[1]) as f:
        disk_map_compressed = f.read().strip()

    disk_map = np.array([], dtype=np.int64)
    id = 0
    for i, v in enumerate(disk_map_compressed, start=1):
        for j in range(int(v)):
            if i % 2 == 0:
                disk_map = np.append(disk_map, -1)
            else:
                disk_map = np.append(disk_map, id)
        if i % 2 != 0:
            id += 1

    max_id_idx = len(disk_map)
    while id >= 0:
        id -= 1

        while disk_map[max_id_idx - 1] != id:
            max_id_idx -= 1

        min_id_idx = max_id_idx - 1
        while disk_map[min_id_idx - 1] == id:
            min_id_idx -= 1
        id_size = max_id_idx - min_id_idx

        # print(f'id = {id} -> {min_id_idx}:{max_id_idx} ({id_size})')

        min_empty_slot_idx = 0
        while True:
            while disk_map[min_empty_slot_idx] != -1:
                min_empty_slot_idx += 1

            max_empty_slot_idx = min_empty_slot_idx + 1
            while disk_map[max_empty_slot_idx] == -1:
                max_empty_slot_idx += 1
            empty_slot_size = max_empty_slot_idx - min_empty_slot_idx
            # print(f'empty -> {min_empty_slot_idx}:{max_empty_slot_idx} ({empty_slot_size})')

            if empty_slot_size >= id_size:
                break
            min_empty_slot_idx += empty_slot_size
            if min_empty_slot_idx >= min_id_idx:
                break

        if min_empty_slot_idx < min_id_idx:
            disk_map[min_empty_slot_idx:min_empty_slot_idx+id_size] = id
            disk_map[min_id_idx:max_id_idx] = -1

    disk_map[disk_map == -1] = 0

    checksum = 0
    for i, v in enumerate(disk_map):
        checksum += i * v

    print(f'Filesystem checksum: {checksum}')
