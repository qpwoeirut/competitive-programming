# from collections import *
# from itertools import *
# from math import *
from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [10, 29]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(s: str) -> int or str:
    # A = list(map(int, s.split(',')))
    # A = [line for line in s.split('\n')]
    A = list(s)
    # A = [line for line in s.split('\n')]
    # A = [list(map(int, line)) for line in s.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    # M = len(A[0])

    # for i in range(N):


    # for i in range(N):

    ans = N
    for i in range(N):
        print(A[i:i+4])
        if LEVEL == 1:
            if len(set(A[i:i+4])) == 4:
                return i+4
        else:
            if len(set(A[i:i+14])) == 14:
                return i+14

    if LEVEL == 1:
        return
    else:
        return


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
    assert submit_answer(2022, 6, LEVEL, answer) is True


if __name__ == '__main__':
    main()
