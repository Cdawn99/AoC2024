import sys
from collections import deque


def bfs(graph: dict, v: str) -> set:
    visited = set()
    q = deque()
    q.append(v)
    while len(q) != 0:
        u = q.popleft()
        if u in visited:
            continue
        for n in graph[u]:
            if n in visited or n in q:
                continue
            q.append(n)
        visited.add(u)
    return visited


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

    for v in network.keys():
        to_remove = set()
        for n1 in network[v]:
            cycle_found = False
            for n2 in network[n1]:
                if n2 == v:
                    continue
                if v in network[n2]:
                    cycle_found = True
            if not cycle_found:
                to_remove.add(n1)
        network[v].difference_update(to_remove)
        for u in to_remove:
            network[u].discard(v)

    cliques = []
    visited = set()
    for v in network.keys():
        if v in visited:
            continue
        cliques.append(bfs(network, v))
        visited = visited.union(cliques[-1])

    def is_max_connected(clique: set) -> bool:
        for v in clique:
            if len(network[v]) != len(clique) - 1:
                return False
        return True

    computers = [i for i in filter(is_max_connected, cliques)]
    password = ','.join(sorted(computers[0]))

    print(f'LAN party password: `{password}`')
