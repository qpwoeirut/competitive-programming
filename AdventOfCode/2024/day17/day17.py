from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = ["4,6,3,5,6,3,5,2,1,0", None]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    A = [line for line in input_string.split('\n')]
    # A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line.split())) for line in input_string.split('\n')]

    reg_a0 = int(A[0].split()[2])
    reg_b0 = int(A[1].split()[2])
    reg_c0 = int(A[2].split()[2])
    prog = list(map(int, A[4].split()[1].split(',')))

    N = len(prog)

    def run(reg_a):
        reg_b = 0
        reg_c = 0

        def combo(x):
            if 0 <= x <= 3:
                return x
            if x == 4:
                return reg_a
            if x == 5:
                return reg_b
            if x == 6:
                return reg_c
            raise ValueError(x)

        out = []
        i = 0
        while i+1 < N:
            # print(i, prog[i], prog[i+1], reg_a, reg_b, reg_c)
            op = prog[i]
            if op == 0:
                reg_a >>= combo(prog[i+1])
            elif op == 1:
                reg_b ^= prog[i+1]
            elif op == 2:
                reg_b = combo(prog[i+1]) % 8
            elif op == 3:
                if reg_a != 0:
                    i = prog[i+1]
                    continue
            elif op == 4:
                reg_b ^= reg_c
            elif op == 5:
                out.append(combo(prog[i+1]) % 8)
            elif op == 6:
                reg_b = reg_a >> combo(prog[i+1])
            elif op == 7:
                reg_c = reg_a >> combo(prog[i+1])
            else:
                assert False, i

            i += 2
        return out

    if LEVEL == 1:
        return ','.join([str(x) for x in run(reg_a0)])
    else:
        ans2 = None
        for base_val in [x << (3 * (len(prog) - 1)) for x in range(8)]:
            ans = None
            cur = {base_val}
            while cur and (ans is None or min(cur) < ans):
                print(cur)
                cur2 = set()
                for c in cur:
                    for a in range(1000):
                        out = run((c << 3) + a)
                        ok = True
                        for x, y in zip(out[::-1], prog[::-1]):
                            ok &= x == y
                        if ok:
                            cur2.add((c << 3) + a)
                            if len(out) == len(prog):
                                ans = min(ans if ans else float('inf'), (c << 3) + a)
                                break
                cur = cur2
            if ans:
                ans2 = min(ans, ans2 if ans2 else float('inf'))
        return ans2


def main():
    if LEVEL == 1:
        with open("sample.txt") as sample_file:
            sample_input = sample_file.read().strip('\n')
        sample_answer = solve(sample_input)
        print("Answer for sample:", sample_answer)
        assert sample_answer == SAMPLE_ANSWER and sample_answer is not None, f"Got {sample_answer} instead of {SAMPLE_ANSWER}"

    with open("input.txt") as input_file:
        inp = input_file.read().strip('\n')
    answer = solve(inp)
    print("Answer:", answer)
    assert submit_answer(2024, 17, LEVEL, answer) is True


if __name__ == '__main__':
    main()
