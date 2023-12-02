# from collections import *
# from itertools import *
# from math import *
from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 1
SAMPLE_ANSWERS = [None, None]
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
    # M = len(A[0])

    ans1 = 0
    ans2 = 0
    # for i in range(N):


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
    assert sample_answer == SAMPLE_ANSWER and sample_answer is not None, f"Got {sample_answer} instead of {SAMPLE_ANSWER}"

    with open("input.txt") as input_file:
        inp = input_file.read().strip('\n')
    answer = solve(inp)
    print("Answer:", answer)
    assert submit_answer({{year}}, {{day}}, LEVEL, answer) is True


if __name__ == '__main__':
    main()
