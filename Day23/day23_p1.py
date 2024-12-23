import sys

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print(f'Usage: {sys.argv[0]} <network_info.txt>')
        sys.exit(1)

    with open(sys.argv[1]) as f:
        network_info = f.read().strip().split('\n')

    network = {}
    for info in network_info:
        u, v = info.split('-')
        if network.get(u) is None:
            network[u] = set()
        if network.get(v) is None:
            network[v] = set()
        network[u].add(v)
        network[v].add(u)

    lan_party_count = 0
    for v in network.keys():
        for n1 in network[v]:
            for n2 in network[n1]:
                if n2 == v:
                    continue
                if v in network[n2] and (v[0] == 't' or n1[0] == 't' or n2[0] == 't'):
                    lan_party_count += 1
    lan_party_count //= 6  # Deal with multi-counting.

    print(f'Number of candidate LAN parties: {lan_party_count}')
