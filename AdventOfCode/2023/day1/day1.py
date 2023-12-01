# from collections import *
# from itertools import *
# from math import *
from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [142, 281]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]

nums = ["zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"]
def to_num(s):
    if s.isdigit():
        return int(s)
    if s in nums:
        return nums.index(s)
    return None


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

    ans = 0
    for i in range(N):
        s = []
        for j in range(len(A[i])):
            for k in range(j + 1, len(A[i]) + 1):
                # print(A[i][j:k])
                if to_num(A[i][j:k]) is not None:
                    s.append(to_num(A[i][j:k]))
        print(s)
        x = s[0] * 10 + s[-1]
        ans += x

    # for i in range(N):

    if LEVEL == 1:
        return ans
    else:
        return ans


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
    assert submit_answer(2023, 1, LEVEL, answer) is True


if __name__ == '__main__':
    main()
