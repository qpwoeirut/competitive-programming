# from collections import *
# from itertools import *
# from math import *
from submit_answer import submit_answer



#      E   S   W   N
chr = [0,  1,  0, -1, -1, -1,  1,  1]
chc = [1,  0, -1,  0, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [6032, 5031]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    A = [line for line in input_string.split('\n')]
    # A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line)) for line in input_string.split('\n')]

    dir_str = A[-1]
    A = A[:-2]

    N = len(A)
    M = max([len(r) for r in A])
    S = 4 if N == 12 else 50
    for i in range(N):
        A[i] = A[i].ljust(M, ' ')

    print("N, M, S =", N, M, S)

    print(dir_str)

    directions = []
    cur = ""
    for c in dir_str:
        if c in "LR":
            directions.append(int(cur))
            directions.append(c)
            cur = ""
        else:
            cur += c
    directions.append(int(cur))
    print(directions)

    r, c, d = 0, A[0].index('.'), 0
    for direction in directions:
        print(direction)
        if type(direction) == int:
            for x in range(direction):
                print(r, c, d)
                old_d = d
                if LEVEL == 1:
                    nr = (r + chr[d]) % N
                    nc = (c + chc[d]) % M
                    while A[nr][nc] == ' ':
                        nr = (nr + chr[d]) % N
                        nc = (nc + chc[d]) % M
                else:
                    fr, fc = r // S, c // S
                    lr, lc = r % S, c % S
                    if 0 <= lr + chr[d] < S and 0 <= lc + chc[d] < S:
                        nr = r + chr[d]
                        nc = c + chc[d]
                        print("Added")
                    elif 0 <= r + chr[d] < N and 0 <= c + chc[d] < M and A[r + chr[d]][c + chc[d]] != ' ':
                        nr = r + chr[d]
                        nc = c + chc[d]
                        print("Added across")
                    else:
                        print("Moved across")
                        if S == 4:
                            if fr == 0 and fc == 2:
                                if d == 0:
                                    fr, fc = 2, 3
                                    d = 2
                                    lr = S - lr - 1
                                elif d == 2:
                                    fr, fc = 1, 1
                                    lr, lc = lc, lr
                                    d = 1
                                elif d == 3:
                                    fr, fc = 1, 0
                                    lc = S - lc - 1
                                    d = 1
                                else:
                                    assert False
                            elif fr == 1 and fc == 0:
                                if d == 1:
                                    fr, fc = 2, 2
                                    lr, lc = S - 1, S - lc - 1
                                    d = 3
                                elif d == 2:
                                    fr, fc = 2, 3
                                    lr, lc = S - 1, S - lr - 1
                                    d = 3
                                elif d == 3:
                                    fr, fc = 0, 2
                                    lc = S - lc - 1
                                    d = 1
                                else:
                                    assert False
                            elif fr == 1 and fc == 1:
                                if d == 1:
                                    fr, fc = 2, 2
                                    lr, lc = lc, S - lr - 1
                                    d = 0
                                elif d == 3:
                                    fr, fc = 0, 2
                                    lr, lc = lc, 0
                                else:
                                    assert False
                            elif fr == 1 and fc == 2:
                                if d == 0:
                                    fr, fc = 2, 3
                                    lr, lc = 0, S - lr - 1
                                    d = 1
                                else:
                                    assert False
                            elif fr == 2 and fc == 2:
                                if d == 1:
                                    fr, fc = 1, 0
                                    lc = S - lc - 1
                                    d = 3
                                elif d == 2:
                                    fr, fc = 1, 1
                                    lr, lc = S - 1, S - lr - 1
                                    d = 3
                                else:
                                    assert False
                            elif fr == 2 and fc == 3:
                                if d == 0:
                                    fr, fc = 0, 2
                                    lr, lc = S - lr - 1, S - 1
                                    d = 2
                                elif d == 1:
                                    fr, fc = 1, 0
                                    lr, lc = S - lc - 1, 0
                                    d = 0
                                elif d == 3:
                                    fr, fc = 1, 2
                                    lr = S - 1
                                else:
                                    assert False
                            else:
                                assert False
                        else:  # literally evil
                            #         1 1 1 1 2 2 2 2
                            #         1 1 1 1 2 2 2 2
                            #         1 1 1 1 2 2 2 2
                            #         1 1 1 1 2 2 2 2
                            #         3 3 3 3
                            #         3 3 3 3
                            #         3 3 3 3
                            #         3 3 3 3
                            # 4 4 4 4 5 5 5 5
                            # 4 4 4 4 5 5 5 5
                            # 4 4 4 4 5 5 5 5
                            # 4 4 4 4 5 5 5 5
                            # 6 6 6 6
                            # 6 6 6 6
                            # 6 6 6 6
                            # 6 6 6 6
                            if fr == 0 and fc == 1:
                                if d == 2:
                                    fr, fc = 2, 0
                                    lr = S - lr - 1
                                    d = 0
                                elif d == 3:
                                    fr, fc = 3, 0
                                    lr, lc = lc, 0
                                    d = 0
                                else:
                                    assert False
                            elif fr == 0 and fc == 2:
                                if d == 0:
                                    fr, fc = 2, 1
                                    lr = S - lr - 1
                                    d = 2
                                elif d == 1:
                                    fr, fc = 1, 1
                                    lr, lc = lc, S - 1
                                    d = 2
                                elif d == 3:
                                    fr, fc = 3, 0
                                    lr = S - 1
                                else:
                                    assert False
                            elif fr == 1 and fc == 1:
                                if d == 0:
                                    fr, fc = 0, 2
                                    lr, lc = S - 1, lr
                                    d = 3
                                elif d == 2:
                                    fr, fc = 2, 0
                                    lr, lc = 0, lr
                                    d = 1
                                else:
                                    assert False
                            elif fr == 2 and fc == 0:
                                if d == 2:
                                    fr, fc = 0, 1
                                    lr = S - lr - 1
                                    d = 0
                                elif d == 3:
                                    fr, fc = 1, 1
                                    lr, lc = lc, 0
                                    d = 0
                                else:
                                    assert False
                            elif fr == 2 and fc == 1:
                                if d == 0:
                                    fr, fc = 0, 2
                                    lr = S - lr - 1
                                    d = 2
                                elif d == 1:
                                    fr, fc = 3, 0
                                    lr, lc = lc, S - 1
                                    d = 2
                                else:
                                    assert False
                            elif fr == 3 and fc == 0:
                                if d == 0:
                                    fr, fc = 2, 1
                                    lr, lc = S - 1, lr
                                    d = 3
                                elif d == 1:
                                    fr, fc = 0, 2
                                    lr = 0
                                elif d == 2:
                                    fr, fc = 0, 1
                                    lr, lc = 0, lr
                                    d = 1
                                else:
                                    assert False
                            else:
                                assert False

                        nr = fr * S + lr
                        nc = fc * S + lc

                if A[nr][nc] == '#':
                    d = old_d
                    break
                else:
                    assert A[nr][nc] == '.'
                    r, c = nr, nc
        elif direction == 'L':
            d = (d - 1) % 4
        elif direction == 'R':
            d = (d + 1) % 4
        else:
            assert False

    return 1000 * (r + 1) + 4 * (c + 1) + d


def main():
    with open("sample.txt") as sample_file:
        sample_input = sample_file.read().strip('\n')
    sample_answer = solve(sample_input)
    print("Answer for sample:", sample_answer)
    assert sample_answer == SAMPLE_ANSWER and sample_answer is not None, f"Got {sample_answer} instead of {SAMPLE_ANSWER}"

    with open("input.txt") as input_file:
        inp = input_file.read().strip('\n')
    answer = solve(inp)
    print("Answer:", answer)
    assert answer not in [32553, 10340, 139351], "old wrong ans"
    assert submit_answer(2022, 22, LEVEL, answer) is True


if __name__ == '__main__':
    main()
