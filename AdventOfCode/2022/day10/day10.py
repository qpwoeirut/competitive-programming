# from collections import *
# from itertools import *
# from math import *
from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [13140, -1]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(s: str) -> int or str:
    # A = list(s)
    # A = list(map(int, s.split(',')))
    A = [line for line in s.split('\n')]
    # A = [line for line in s.split('\n')]
    # A = [list(map(int, line)) for line in s.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    # M = len(A[0])

    X = 1
    cycle = 0
    value = []

    for i in range(N):
        if A[i] == "noop":
            value.append(X)
            cycle += 1
        else:
            instr, V = A[i].split()
            V = int(V)
            value.append(X)
            value.append(X)
            cycle += 2
            X += V

    print(value)

    screen = [["." for _ in range(40)] for _ in range(6)]
    for i, v in enumerate(value):
        r, c = i // 40, i % 40
        if abs(c - value[i]) <= 1:
            screen[r][c] = "#"

    if LEVEL == 1:
        print(value[19])
        print(value[59])
        return sum([value[i-1] * i for i in range(20, len(value), 40)])
    else:
        print('\n'.join([''.join(row) for row in screen]))
        return -1


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
    if LEVEL == 1:
        assert submit_answer(2022, 10, LEVEL, answer) is True


if __name__ == '__main__':
    main()
