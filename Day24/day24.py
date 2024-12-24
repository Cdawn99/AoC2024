class Circuit:
    def __init__(self, initial_state: str, gates: str):
        self._state = {}
        self._computation_graph = {}
        self._compute_called = False

        for state in initial_state.split('\n'):
            var, val = state.split(': ')
            self._state[var] = int(val)

        for gate in gates.split('\n'):
            x, op, y, _, z = gate.split(' ')
            self._computation_graph[z] = (x, y, op)

    def get_inputs(self) -> tuple[int, int]:
        xs = sorted(filter(lambda x: x[0] == 'x', self._state.keys()), reverse=True)
        ys = sorted(filter(lambda y: y[0] == 'y', self._state.keys()), reverse=True)

        xs = ''.join(map(lambda x: str(self._state[x]), xs))
        ys = ''.join(map(lambda y: str(self._state[y]), ys))

        return int(xs, 2), int(ys, 2)

    def print_computation_graph(self):
        visited = set()
        q = sorted(filter(lambda z: z[0] == 'z', self._computation_graph.keys()), reverse=True)
        q = list(map(lambda z: (z, 0), q))
        while len(q) != 0:
            z, d = q.pop(-1)
            if z[0] in 'xy':
                continue
            x, y, op = self._computation_graph[z]
            s = ' ' * d
            if self._compute_called:
                print(f'{s}{z} = {x} {op} {y} ({self._state[z]} = {self._state[x]} {op} {self._state[y]})')
            else:
                print(f'{s}{z} = {x} {op} {y}')
            if x not in visited:
                q.append((x, d+1))
            if y not in visited:
                q.append((y, d+1))
            visited.add(z)

    def compute(self) -> int:
        self._compute_called = True
        zs = sorted(filter(lambda z: z[0] == 'z', self._computation_graph.keys()), reverse=True)
        for z in zs:
            self._state[z] = self._do_compute(z)
        return int(''.join(map(lambda z: str(self._state[z]), zs)), 2)

    def _apply_gate(self, x: int, y: int, op: str) -> int:
        match op:
            case 'AND':
                return x & y
            case 'OR':
                return x | y
            case 'XOR':
                return x ^ y
            case _:
                raise RuntimeError(f'ERROR: Unknown operation: `{op}`')

    def _do_compute(self, z: str) -> int:
        x, y, op = self._computation_graph[z]

        if self._state.get(x) is None:
            self._state[x] = self._do_compute(x)

        if self._state.get(y) is None:
            self._state[y] = self._do_compute(y)

        x = self._state[x]
        y = self._state[y]
        return self._apply_gate(x, y, op)
