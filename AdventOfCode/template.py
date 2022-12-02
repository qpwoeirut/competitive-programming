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


def solve(s: str) -> int:
    # A = list(map(int, file.readline().split(',')))
    A = [line.strip() for line in s.split('\n')]
    # A = [line.strip() for line in file]
    # A = [list(map(int, line.strip())) for line in file]

    N = len(A)
    print("N =", N)
    print(A[:10])
    # M = len(A[0])

    # for i in range(N):


    # for i in range(N):

    if LEVEL == 1:
        return
    else:
        return


def main():
    with open("sample.txt") as sample_file:
        sample_input = sample_file.read().strip()
    sample_answer = solve(sample_input)
    print("Answer for sample:", sample_answer)
    assert solve(sample_input) == SAMPLE_ANSWER or SAMPLE_ANSWER is None,\
        f"Got {sample_answer} instead of {SAMPLE_ANSWER}"

    with open("input.txt") as input_file:
        inp = input_file.read().strip()
    answer = solve(inp)
    print("Answer:", answer)
    assert submit_answer({{year}}, {{day}}, LEVEL, answer) is True


if __name__ == '__main__':
    main()
