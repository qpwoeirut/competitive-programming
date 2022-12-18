# from collections import *
# from itertools import *
# from math import *
from submit_answer import submit_answer
import sys


sys.setrecursionlimit(16000)


chx = [1, -1,  0,  0,  0 ,0]
chy = [0,  0,  1, -1,  0, 0]
chz = [0,  0,  0,  0, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [64, 58]
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

    cubes = set()
    for i in range(N):
        cubes.add(tuple(map(int, A[i].split(','))))
    bounds = [(min(cubes, key=lambda t: t[i])[i] - 2, max(cubes, key=lambda t: t[i])[i] + 2) for i in range(3)]
    print(bounds)

    area = 0
    if LEVEL == 1:
        for cube in cubes:
            for d in range(6):
                ncube = (cube[0] + chx[d], cube[1] + chy[d], cube[2] + chz[d])
                if ncube not in cubes:
                    area += 1

    visited = set()

    def dfs(x, y, z):
        if (x, y, z) in visited or not (bounds[0][0] <= x <= bounds[0][1] and bounds[1][0] <= y <= bounds[1][1] and bounds[2][0] <= z <= bounds[2][1]):
            return 0
        if (x, y, z) in cubes:
            return 1
        visited.add((x, y, z))

        a = 0
        for d in range(6):
            a += dfs(x + chx[d], y + chy[d], z + chz[d])
        return a


    # for i in range(N):

    if LEVEL == 1:
        return area
    else:
        return dfs(bounds[0][0], bounds[1][0], bounds[2][0])


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
    assert submit_answer(2022, 18, LEVEL, answer) is True


if __name__ == '__main__':
    main()
