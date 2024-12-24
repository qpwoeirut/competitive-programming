from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [2024, None]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    # A = [line for line in input_string.split('\n')]
    # A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line.split())) for line in input_string.split('\n')]

    vals0, gates0 = map(lambda s: s.split('\n'), input_string.split('\n\n'))
    vals0 = {line.split(': ')[0]: int(line.split(': ')[1]) for line in vals0}
    gates0 = {line.split()[4]: (line.split()[0], line.split()[2], line.split()[1]) for line in gates0}

    ans1 = 0
    ans2 = 0

    def run(vals, gates):
        vals = vals.copy()
        gates = gates.copy()
        for _ in gates:
            for gate, op in gates.items():
                if gate in vals:
                    continue
                if op[0] not in vals or op[1] not in vals:
                    continue
                if op[2] == 'AND':
                    vals[gate] = vals[op[0]] & vals[op[1]]
                elif op[2] == 'OR':
                    vals[gate] = vals[op[0]] | vals[op[1]]
                elif op[2] == 'XOR':
                    vals[gate] = vals[op[0]] ^ vals[op[1]]
                else:
                    assert False, op
            if all(g in vals for g in gates):
                break
        return vals.copy()


    if LEVEL == 1:
        vals0 = run(vals0, gates0)
        for i in range(100):
            s = 'z' + str(i).zfill(2)
            if s in vals0:
                ans1 |= vals0[s] << i
        return ans1
    else:
        swaps = []
        # x11 XOR y11 -> qff
        # x11 AND y11 -> qnw
        # ncw XOR qnw -> z11
        # ncw AND qnw -> stw
        # qff OR stw -> wsv
        # mgj XOR wsv -> z12
        # x12 XOR y12 -> mgj
        gates0['qff'], gates0['qnw'] = gates0['qnw'], gates0['qff']
        swaps.extend(['qff', 'qnw'])

        # x16 AND y16 -> z16
        # guessing
        gates0['pbv'], gates0['z16'] = gates0['z16'], gates0['pbv']
        swaps.extend(['pbv', 'z16'])

        # y22 XOR x22 -> dfc
        # x22 AND y22 -> tqj
        # srv XOR dfc -> z22
        # srv AND dfc -> rng
        # tqj OR rng -> cts
        # cts XOR bcd -> qqp
        # bcd AND cts -> jcd
        # x23 XOR y23 -> bcd
        # wdr OR jcd -> z23
        # qqp XOR dmw -> z24
        # qqp AND dmw -> kqp
        gates0['qqp'], gates0['z23'] = gates0['z23'], gates0['qqp']
        swaps.extend(['qqp', 'z23'])

        gates0['fbq'], gates0['z36'] = gates0['z36'], gates0['fbq']
        swaps.extend(['fbq', 'z36'])

        for k in vals0:
            vals0[k] = 0
        init = run(vals0, gates0)
        for i in range(100):
            z = 'z' + str(i).zfill(2)
            if z not in gates0:
                continue
            x = 'x' + str(i).zfill(2)
            y = 'y' + str(i).zfill(2)
            if x not in vals0 or y not in vals0:
                continue

            print(x, y)

            vals0[x] ^= 1
            print([(k, v) for k, v in run(vals0, gates0).items() if v != init[k] and k[0] not in 'xy'])
            vals0[y] ^= 1
            print([(k, v) for k, v in run(vals0, gates0).items() if v != init[k] and k[0] not in 'xy'])
            vals0[x] ^= 1
            print([(k, v) for k, v in run(vals0, gates0).items() if v != init[k] and k[0] not in 'xy'])
            vals0[y] ^= 1
        ans2 = ','.join(sorted(swaps))
        return ans2


def main():
    # with open("sample.txt") as sample_file:
    #     sample_input = sample_file.read().strip('\n')
    # sample_answer = solve(sample_input)
    # print("Answer for sample:", sample_answer)
    # assert sample_answer == SAMPLE_ANSWER and sample_answer is not None, f"Got {sample_answer} instead of {SAMPLE_ANSWER}"

    with open("input.txt") as input_file:
        inp = input_file.read().strip('\n')
    answer = solve(inp)
    print("Answer:", answer)
    assert submit_answer(2024, 24, LEVEL, answer) is True


if __name__ == '__main__':
    main()
