from day24 import Circuit

import sys

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print(f'Usage: {sys.argv[0]} <circuit.txt>')
        sys.exit(1)

    with open(sys.argv[1]) as f:
        initial_state, gates = f.read().strip().split('\n\n')

    circuit = Circuit(initial_state, gates)
    z = circuit.compute()
    x, y = circuit.get_inputs()
    print(f'acutal   = {bin(z)}')
    print(f'expected = {bin(x + y)}')
    circuit.print_computation_graph()
