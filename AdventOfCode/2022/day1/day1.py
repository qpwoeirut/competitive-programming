# from collections import *
# from itertools import *
# from math import *
from submit_answer import submit_answer


LEVEL = 2
SAMPLE_ANSWERS = [24000, 45000]
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

    cals = [0]
    for i in range(N):
        if A[i] == "":
            cals.append(0)
        else:
            cals[-1] += int(A[i])


    # for i in range(N):

    if LEVEL == 1:
        return max(cals)
    else:
        cals.sort()
        return sum(cals[-3:])


def main():
    with open("sample.txt") as sample_file:
        sample_input = sample_file.read()
    sample_answer = solve(sample_input)
    print("Answer for sample:", sample_answer)
    assert solve(sample_input) == SAMPLE_ANSWER, f"Got {sample_answer} instead of {SAMPLE_ANSWER}"

    with open("input.txt") as input_file:
        input = input_file.read()
    answer = solve(input)
    print("Answer:", answer)
    assert submit_answer(2022, 1, LEVEL, answer) is True


if __name__ == '__main__':
    main()
