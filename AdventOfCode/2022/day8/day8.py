# from collections import *
# from itertools import *
# from math import *
from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [21, 8]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(s: str) -> int or str:
    # A = list(s)
    # A = list(map(int, s.split(',')))
    # A = [line for line in s.split('\n')]
    # A = [line for line in s.split('\n')]
    A = [list(map(int, line)) for line in s.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    M = len(A[0])

    visible = [[False for _ in A[0]] for _ in A]
    for r in range(N):
        mx = -1
        for c in range(M):
            if A[r][c] > mx:
                visible[r][c] = True
                mx = A[r][c]
        mx = -1
        for c in reversed(range(M)):
            if A[r][c] > mx:
                visible[r][c] = True
                mx = A[r][c]
    for c in range(M):
        mx = -1
        for r in range(N):
            if A[r][c] > mx:
                visible[r][c] = True
                mx = A[r][c]
        mx = -1
        for r in reversed(range(N)):
            if A[r][c] > mx:
                visible[r][c] = True
                mx = A[r][c]

    score = 0
    for r in range(N):
        for c in range(M):
            left = 0 if c == 0 else 1
            while c > left and A[r][c - left] < A[r][c]:
                left += 1
            down = 0 if r == 0 else 1
            while r > down and A[r - down][c] < A[r][c]:
                down += 1
            right = 0 if c + 1 == M else 1
            while c + right + 1 < M and A[r][c + right] < A[r][c]:
                right += 1
            up = 0 if r + 1 == N else 1
            while r + up + 1 < N and A[r + up][c] < A[r][c]:
                up += 1
            score = max(score, left * down * right * up)
            print((r, c), (left, down, right, up))


    if LEVEL == 1:
        return sum([row.count(True) for row in visible])
    else:
        return score


def main():
    with open("sample.txt") as sample_file:
        sample_input = sample_file.read().strip('\n')
    sample_answer = solve(sample_input)
    print("Answer for sample:", sample_answer)
    assert sample_answer == SAMPLE_ANSWER, f"Got {sample_answer} instead of {SAMPLE_ANSWER}"

    with open("input.txt") as input_file:
        inp = input_file.read().strip('\n')
    answer = solve(inp)
    print("Answer:", answer)
    assert submit_answer(2022, 8, LEVEL, answer) is True


if __name__ == '__main__':
    main()
