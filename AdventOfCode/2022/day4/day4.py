# from collections import *
# from itertools import *
# from math import *
from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [2, 4]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(s: str) -> int:
    # A = list(map(int, s.split(',')))
    A = [line.strip() for line in s.split('\n')]
    # A = [line.strip() for line in s.split('\n')]
    # A = [list(map(int, line.strip())) for line in s.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    # M = len(A[0])

    ans = 0
    ans2 = 0
    for i in range(N):
        a, b = A[i].split(',')
        a0, a1 = map(int, a.split('-'))
        b0, b1 = map(int, b.split('-'))
        if (a0 <= b0 and b1 <= a1) or (b0 <= a0 and a1 <= b1):
            ans += 1
        if (a0 <= b0 <= a1) or (a0 <= b1 <= a1) or (b0 <= a0 <= b1) or (b0 <= a1 <= b1):
            ans2 += 1

    # for i in range(N):

    if LEVEL == 1:
        return ans
    else:
        return ans2


def main():
    with open("sample.txt") as sample_file:
        sample_input = sample_file.read().strip()
    sample_answer = solve(sample_input)
    print("Answer for sample:", sample_answer)
    assert solve(sample_input) == SAMPLE_ANSWER,\
        f"Got {sample_answer} instead of {SAMPLE_ANSWER}"

    with open("input.txt") as input_file:
        inp = input_file.read().strip()
    answer = solve(inp)
    print("Answer:", answer)
    assert submit_answer(2022, 4, LEVEL, answer) is True


if __name__ == '__main__':
    main()
