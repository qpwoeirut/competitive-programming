# from collections import *
# from itertools import *
# from math import *
from submit_answer import submit_answer


LEVEL = 2
SAMPLE_ANSWERS = [, ]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


def solve(s: str):
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
        sample_input = sample_file.read()
    sample_answer = solve(sample_input)
    print("Answer for sample:", sample_answer)
    assert solve(sample_input) == SAMPLE_ANSWER, f"Got {sample_answer} instead of {SAMPLE_ANSWER}"

    with open("input.txt") as input_file:
        inp = input_file.read()
    answer = solve(inp)
    print("Answer:", answer)
    assert submit_answer(2022, 1, LEVEL, answer) is True


if __name__ == '__main__':
    main()
