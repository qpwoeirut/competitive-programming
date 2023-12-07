# from collections import *
# from itertools import *
# from math import *
from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [288, 71503]
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

    if LEVEL == 2:
        A[0] = A[0].replace(' ', '')
        A[1] = A[1].replace(' ', '')
    time = list(map(int, A[0].split(":")[1].split()))
    dist = list(map(int, A[1].split(":")[1].split()))
    print(time)
    print(dist)

    ans = 1
    M = len(time)
    for i in range(M):
        mn = 10**100
        mx = -10**100
        for x in range(1, time[i], 1000 if LEVEL == 2 else 1):
            if x * (time[i] - x) > dist[i]:
                mn = min(mn, x)
                mx = max(mx, x)
        for x in range(mn - 2000, mn):
            if x * (time[i] - x) > dist[i] and 0 <= x:
                mn = min(mn, x)
                mx = max(mx, x)
        for x in range(mx, mx + 2000):
            if x * (time[i] - x) > dist[i] and 0 <= x:
                mn = min(mn, x)
                mx = max(mx, x)
        ans *= mx - mn + 1

    # for i in range(N):


    # for i in range(N):

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
    assert submit_answer(2023, 6, LEVEL, answer) is True


if __name__ == '__main__':
    main()
