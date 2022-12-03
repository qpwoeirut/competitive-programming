# from collections import *
# from itertools import *
# from math import *
from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [157, 70]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(s: str) -> int:
    # A = list(map(int, file.readline().split(',')))
    A = [line.strip() for line in s.split('\n')]
    # A = [line.strip() for line in file]
    # A = [list(map(int, line.strip())) for line in file]

    N = len(A)
    print("N =", N)
    print(A[:10])
    # M = len(A[0])

    priority = 0
    for i in range(N):
        n = len(A[i]) // 2
        first = set(A[i][:n])
        second = set(A[i][n:])
        both = first.intersection(second)
        for x in both:
            print(x)
            priority += ord(x) - ord('a') + 1 if x.islower() else ord(x) - ord('A') + 27

    ans2 = 0
    for i in range(0, N, 3):
        a = set(A[i])
        b = set(A[i+1])
        c = set(A[i+2])
        d = a.intersection(b).intersection(c)
        for x in d:
            print(x)
            ans2 += ord(x) - ord('a') + 1 if x.islower() else ord(x) - ord('A') + 27


    if LEVEL == 1:
        return priority
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
    assert submit_answer(2022, 3, LEVEL, answer) is True


if __name__ == '__main__':
    main()
