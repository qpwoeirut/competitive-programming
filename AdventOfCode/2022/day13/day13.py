# from collections import *
# from itertools import *
# from math import *
import functools

from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [13, 140]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(s: str) -> int or str:
    # A = list(s)
    # A = list(map(int, s.split(',')))
    A = [line for line in s.split('\n')]
    # A = [line for line in s.split('\n')]
    # A = [list(map(int, line)) for line in s.split('\n')]

    N = len(A)
    print("N =", N)
    # M = len(A[0])

    good = []

    def is_good(a: list or int, b: list or int):
        if type(a) == int and type(b) == int:
            if a < b:
                return -1
            elif a > b:
                return 1
            else:
                return 0
        else:
            if type(a) == int:
                a = [a]
            if type(b) == int:
                b = [b]
            while a and b:
                val = is_good(a[0], b[0])
                if val != 0:
                    return val
                a.pop(0)
                b.pop(0)
            if len(a) == 0 and len(b) == 0:
                return 0
            elif len(a) == 0:
                return -1
            elif len(b) == 0:
                return 1
            else:
                assert False

    for i in range(0, N, 3):
        # print()
        # print(i // 3)
        if is_good(eval(A[i]), eval(A[i+1])) == -1:
            print("Good!")
            good.append((i + 3) // 3)

    # for i in range(N):

    A = [r for r in A if r]
    A.append("[[2]]")
    A.append("[[6]]")
    A.sort(key=functools.cmp_to_key(lambda s1, s2: is_good(eval(s1), eval(s2))))

    if LEVEL == 1:
        return sum(good)
    else:
        a = A.index("[[2]]") + 1
        b = A.index("[[6]]") + 1
        return a * b


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
    assert answer != 5544, "prev ans"
    assert submit_answer(2022, 13, LEVEL, answer) is True


if __name__ == '__main__':
    main()
