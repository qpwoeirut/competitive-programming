# from collections import *
# from itertools import *
# from math import *
from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [24, 93]
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

    R = 250
    C = 1000
    G = [['.' for _ in range(C)] for _ in range(R)]
    r_max = 0
    for i in range(N):
        points = A[i].split(" -> ")
        for i in range(1, len(points)):
            c, r = map(int, points[i - 1].split(','))
            c1, r1 = map(int, points[i].split(','))
            r_max = max(r_max, r, r1)

            G[r][c] = '#'

            while r < r1:
                r += 1
                G[r][c] = '#'
            while r > r1:
                r -= 1
                G[r][c] = '#'
            while c < c1:
                c += 1
                G[r][c] = '#'
            while c > c1:
                c -= 1
                G[r][c] = '#'

    if LEVEL == 1:
        sand = 0
        while True:
            sr, sc = 0, 500
            sand += 1
            while sr < 200:
                if G[sr+1][sc] == '.':
                    sr += 1
                elif G[sr+1][sc-1] == '.':
                    sr += 1
                    sc -= 1
                elif G[sr+1][sc+1] == '.':
                    sr += 1
                    sc += 1
                else:
                    G[sr][sc] = '#'
                    break
            else:
                break

        sand -= 1  # can't fall at source

        print('\n'.join([''.join(r) for r in G]))
        return sand
    else:
        for c in range(C):
            G[r_max + 2][c] = '#'
        sand = set()
        def dfs(r, c):
            print(r, c)
            if G[r][c] == '#' or (r, c) in sand:
                return
            sand.add((r, c))
            dfs(r + 1, c - 1)
            dfs(r + 1, c)
            dfs(r + 1, c + 1)

        dfs(0, 500)
        return len(sand)


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
    assert submit_answer(2022, 14, LEVEL, answer) is True


if __name__ == '__main__':
    main()
