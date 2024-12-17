def match_to_int(match):
    return int(match[0])


class Opcodes:
    ADV = 0
    BXL = 1
    BST = 2
    JNZ = 3
    BXC = 4
    OUT = 5
    BDV = 6
    CDV = 7


class Interpreter:
    def __init__(self, ra: int, rb: int, rc: int):
        self.ra = ra
        self.rb = rb
        self.rc = rc

        self.output = ''

    def step(self, ip: int, opcode: int, operand: int) -> int:
        ip += 2

        match opcode:
            case Opcodes.ADV:
                num = self.ra
                denom = 2**self._combo_op(operand)
                self.ra = num // denom
            case Opcodes.BXL:
                self.rb ^= operand
            case Opcodes.BST:
                self.rb = self._combo_op(operand) % 8
            case Opcodes.JNZ:
                if self.ra != 0:
                    ip = operand
            case Opcodes.BXC:
                self.rb ^= self.rc
            case Opcodes.OUT:
                val = self._combo_op(operand) % 8
                if len(self.output) == 0:
                    self.output = str(val)
                else:
                    self.output += f',{val}'
            case Opcodes.BDV:
                num = self.ra
                denom = 2**self._combo_op(operand)
                self.rb = num // denom
            case Opcodes.CDV:
                num = self.ra
                denom = 2**self._combo_op(operand)
                self.rc = num // denom

        return ip

    def _combo_op(self, operand: int):
        match operand:
            case 0 | 1 | 2 | 3:
                return operand
            case 4:
                return self.ra
            case 5:
                return self.rb
            case 6:
                return self.rc
        raise RuntimeError(f'ERROR: Reserved or invalid combo operand: `{operand}`')
