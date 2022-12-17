# from collections import *
# from itertools import *
# from math import *
from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [3068, 1514285714288]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(s: str) -> int or str:
    A = list(s)
    # A = list(map(int, s.split(',')))
    # A = [line for line in s.split('\n')]
    # A = [line for line in s.split('\n')]
    # A = [list(map(int, line)) for line in s.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    # M = len(A[0])

    MOD = N * 5 * (346 if N != 40 else 7)
    X = 1000000000000
    XM = X % MOD
    T = 2022 if LEVEL == 1 else XM + MOD * 2
    print("T =", T)
    print("MOD =", MOD)

    R = T * 5 // 3
    C = 7
    print("R, C =", R, C)
    G = [['.' for _ in range(C)] for _ in range(R)]

    ROCKS = [
        [(0, 0), (0, 1), (0, 2), (0, 3)],
        [(-1, 0), (0, 1), (-1, 1), (-2, 1), (-1, 2)],
        [(0, 0), (0, 1), (0, 2), (-1, 2), (-2, 2)],
        [(0, 0), (-1, 0), (-2, 0), (-3, 0)],
        [(0, 0), (0, 1), (-1, 0), (-1, 1)]
    ]

    def rock_ok(row, col, shape) -> bool:
        for part in shape:
            nr = row + part[0]
            nc = col + part[1]
            if not (0 <= nc < C) or G[nr][nc] == '#':
                return False
        return True

    tallest_rock = [R - 1 for _ in range(C)]
    for c in range(C):
        G[R-1][c] = '#'

    jet_idx = 0
    heights = []
    for rock in range(T):
        r, c = min(tallest_rock) - 4, 2
        rk = rock % 5
        while True:
            if A[jet_idx] == '<':
                if rock_ok(r, c - 1, ROCKS[rk]):
                    c -= 1
            elif A[jet_idx] == '>':
                if rock_ok(r, c + 1, ROCKS[rk]):
                    c += 1
            jet_idx += 1
            if jet_idx == N:
                jet_idx = 0

            if rock_ok(r + 1, c, ROCKS[rk]):
                r += 1
            else:
                for part in ROCKS[rk]:
                    nr = r + part[0]
                    nc = c + part[1]
                    G[nr][nc] = '#'
                    tallest_rock[nc] = min(tallest_rock[nc], nr)
                break
        if (rock + 1) % MOD == XM:
            heights.append([])
            for c in range(C):
                heights[-1].append(R - tallest_rock[c] - 1)
            print(rock)
        # print('\n'.join([''.join(r) for r in G[-20:]]))
        # print()

    for i in range(1, len(heights)):
        for c in range(C):
            print(heights[i][c], end=" ")
        print()
    for i in range(1, len(heights)):
        for c in range(C):
            print(heights[i][c] - heights[i-1][c], end=" ")
        print()

    # for i in range(1, len(heights)):
    #     for j in range(i + 1, len(heights)):
    #         ok = True
    #         for c in range(C):
    #             if heights[i][c] - heights[i-1][c] != heights[j][c] - heights[j-1][c]:
    #                 ok = False
    #                 break
    #         if ok:
    #             print(i, j)

    if LEVEL == 1:
        return R - min(tallest_rock) - 1
    else:
        return max(heights[2]) + (X // MOD - 2) * (max(heights[-1]) - max(heights[-2]))


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
    # assert submit_answer(2022, 17, LEVEL, answer) is True


if __name__ == '__main__':
    main()
