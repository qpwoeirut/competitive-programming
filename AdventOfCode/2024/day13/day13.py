import math

import sympy.solvers.solvers
from sympy import symbols
from sympy.solvers import solvers

from submit_answer import submit_answer

#      N   E   S   W
chr = [-1, 0, 1, 0, -1, -1, 1, 1]
chc = [0, 1, 0, -1, -1, 1, -1, 1]

LEVEL = 2
SAMPLE_ANSWERS = [480, None]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    A = [line for line in input_string.split('\n')]
    # A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line.split())) for line in input_string.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    # M = len(A[0])

    machines = []
    for i in range(0, N, 4):
        bAx, bAy = A[i].split()[-2:]
        bAx = bAx.removeprefix('X+').removesuffix(',')
        bAy = bAy.removeprefix('Y+')
        bBx, bBy = A[i + 1].split()[-2:]
        bBx = bBx.removeprefix('X+').removesuffix(',')
        bBy = bBy.removeprefix('Y+')
        prizeX, prizeY = A[i + 2].split()[-2:]
        prizeX = prizeX.removeprefix('X=').removesuffix(',')
        prizeY = prizeY.removeprefix('Y=')

        off = 0
        if LEVEL == 2:
            off = 10000000000000

        machines.append((int(bAx), int(bAy), int(bBx), int(bBy), int(prizeX) + off, int(prizeY) + off))

    ans1 = 0
    ans2 = 0
    for i, machine in enumerate(machines):
        a, b = symbols("a b", integer=True)
        res = sympy.solve((
            a * machine[0] + b * machine[2] - machine[4],
            a * machine[1] + b * machine[3] - machine[5]),
            (a, b)
        )
        if not res:
            continue
        cost = res[a] * 3 + res[b]
        ans1 += cost
        ans2 += cost

    # for i in range(N):

    if LEVEL == 1:
        return ans1
    else:
        return ans2


def main():
    with open("sample.txt") as sample_file:
        sample_input = sample_file.read().strip('\n')
    sample_answer = solve(sample_input)
    print("Answer for sample:", sample_answer)
    if LEVEL == 1:
        assert sample_answer == SAMPLE_ANSWER and sample_answer is not None, f"Got {sample_answer} instead of {SAMPLE_ANSWER}"

    with open("input.txt") as input_file:
        inp = input_file.read().strip('\n')
    answer = solve(inp)
    print("Answer:", answer)
    assert submit_answer(2024, 13, LEVEL, answer) is True


if __name__ == '__main__':
    main()
