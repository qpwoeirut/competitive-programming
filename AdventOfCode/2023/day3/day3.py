# from collections import *
# from itertools import *
# from math import *
from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 1
SAMPLE_ANSWERS = [4361, 467835]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]



def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    A = [line for line in input_string.split('\n')]
    # A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line)) for line in input_string.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    M = len(A[0])
    print(M)


    ok = [[False for _ in range(M)] for _ in range(N)]
    id = [[-1 for _ in range(M)] for _ in range(N)]
    def dfs(r, c):
        if not (0 <= r < N and 0 <= c < M):
            return
        if A[r][c] == '.' or ok[r][c]:
            return
        ok[r][c] = True
        dfs(r + 1, c)
        dfs(r, c + 1)
        dfs(r - 1, c)
        dfs(r, c - 1)
        dfs(r + 1, c + 1)
        dfs(r - 1, c + 1)
        dfs(r - 1, c - 1)
        dfs(r + 1, c - 1)

    for r in range(N):
        for c in range(M):
            if A[r][c] != '.' and not A[r][c].isnumeric():
                dfs(r, c)

    vals = dict()
    ans1 = 0
    ans2 = 0
    n = 0
    for r in range(N):
        s = ""
        for c in range(M):
            if A[r][c].isnumeric() and ok[r][c]:
                s += A[r][c]
                id[r][c] = n
            elif s:
                ans1 += int(s)
                vals[n] = int(s)
                s = ""
                n += 1
        if s:
            ans1 += int(s)
            vals[n] = int(s)
            n += 1
    print(vals)

    for r in range(N):
        for c in range(M):
            if A[r][c] == '*':
                ids = {id[r + cr][c + cc] for cr, cc in zip(chr, chc)}
                ids.remove(-1)
                if len(ids) == 2:
                    a, b = ids
                    print(a, b)
                    ans2 += vals[a] * vals[b]

    if LEVEL == 1:
        return ans1
    else:
        return ans2


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
    assert submit_answer(2023, 3, LEVEL, answer) is True


if __name__ == '__main__':
    main()
