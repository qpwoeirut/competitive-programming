# from collections import *
# from itertools import *
# from math import *
from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [18, 54]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    A = [line for line in input_string.split('\n')]
    # A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line)) for line in input_string.split('\n')]

    N = len(A)
    M = len(A[0])
    print("N =", N, M)

    blizzards = [[set() for _ in range(4)]]
    for r in range(N):
        for c in range(M):
            if A[r][c] in "^>v<":
                blizzards[0]["^>v<".index(A[r][c])].add((r, c))


    time = 0
    positions = [{(0, 1)}]
    while (N-1, M-2) not in positions[-1]:
        time += 1
        print(time)
        positions.append(set())
        blizzards.append([set() for _ in range(4)])

        for d in range(4):
            for bliz in blizzards[-2][d]:
                nr = bliz[0] + chr[d]
                nc = bliz[1] + chc[d]
                if nr == 0:
                    nr = N - 2
                if nr == N - 1:
                    nr = 1
                if nc == 0:
                    nc = M - 2
                if nc == M - 1:
                    nc = 1
                blizzards[-1][d].add((nr, nc))
        for pos in positions[-2]:
            if all(pos not in blizzards[-1][d] for d in range(4)):
                positions[-1].add(pos)
            for d in range(4):
                nr, nc = pos[0] + chr[d], pos[1] + chc[d]
                if 0 <= nr < N and 0 <= nc < M and A[nr][nc] != '#' and all((nr, nc) not in blizzards[-1][d] for d in range(4)):
                    positions[-1].add((nr, nc))

    if LEVEL == 2:
        positions[-1] = {(N - 1, M - 2)}
        while (0, 1) not in positions[-1]:
            time += 1
            print(time)
            positions.append(set())
            blizzards.append([set() for _ in range(4)])

            for d in range(4):
                for bliz in blizzards[-2][d]:
                    nr = bliz[0] + chr[d]
                    nc = bliz[1] + chc[d]
                    if nr == 0:
                        nr = N - 2
                    if nr == N - 1:
                        nr = 1
                    if nc == 0:
                        nc = M - 2
                    if nc == M - 1:
                        nc = 1
                    blizzards[-1][d].add((nr, nc))
            for pos in positions[-2]:
                if all(pos not in blizzards[-1][d] for d in range(4)):
                    positions[-1].add(pos)
                for d in range(4):
                    nr, nc = pos[0] + chr[d], pos[1] + chc[d]
                    if 0 <= nr < N and 0 <= nc < M and A[nr][nc] != '#' and all((nr, nc) not in blizzards[-1][d] for d in range(4)):
                        positions[-1].add((nr, nc))

        positions[-1] = {(0, 1)}
        while (N - 1, M - 2) not in positions[-1]:
            time += 1
            print(time)
            positions.append(set())
            blizzards.append([set() for _ in range(4)])

            for d in range(4):
                for bliz in blizzards[-2][d]:
                    nr = bliz[0] + chr[d]
                    nc = bliz[1] + chc[d]
                    if nr == 0:
                        nr = N - 2
                    if nr == N - 1:
                        nr = 1
                    if nc == 0:
                        nc = M - 2
                    if nc == M - 1:
                        nc = 1
                    blizzards[-1][d].add((nr, nc))
            for pos in positions[-2]:
                if all(pos not in blizzards[-1][d] for d in range(4)):
                    positions[-1].add(pos)
                for d in range(4):
                    nr, nc = pos[0] + chr[d], pos[1] + chc[d]
                    if 0 <= nr < N and 0 <= nc < M and A[nr][nc] != '#' and all((nr, nc) not in blizzards[-1][d] for d in range(4)):
                        positions[-1].add((nr, nc))

    return time


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
    assert submit_answer(2022, 24, LEVEL, answer) is True


if __name__ == '__main__':
    main()
