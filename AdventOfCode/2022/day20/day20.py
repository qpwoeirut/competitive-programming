# from collections import *
# from itertools import *
# from math import *
from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [3, 1623178306]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    # A = [line for line in input_string.split('\n')]
    A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line)) for line in input_string.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    # M = len(A[0])

    if LEVEL == 2:
        KEY = 811589153
        A = [x * KEY for x in A]

    M = 1 if LEVEL == 1 else 10

    values = [(A[i], i) for i in range(N)]
    for _ in range(M):
        for i in range(N):
            cur = values.index((A[i], i))
            val = values.pop(cur)
            cur = (cur + val[0]) % len(values)
            if cur == 0:
                cur = N
            values.insert(cur, val)
            # for a in values:
            #     print(a[0], end=' ')
            # print()

    zero = values.index((0, A.index(0)))
    ans = 0
    for i in range(0, 3000, 1000):
        ans += values[(1000 + i + zero) % N][0]
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
    assert submit_answer(2022, 20, LEVEL, answer) is True


if __name__ == '__main__':
    main()
