# from collections import *
# from itertools import *
# from math import *
from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 1
SAMPLE_ANSWERS = [8, 2286]
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

    total = {
        "red": 12,
        "green": 13,
        "blue": 14
    }

    ans = 0
    for i in range(N):
        if LEVEL == 2:
            total = {
                "red": 0,
                "green": 0,
                "blue": 0
            }
        ok = True
        games = A[i].split(': ')[1].split('; ')
        for game in games:
            counts = dict()
            parts = game.split(' ')
            for p in range(0, len(parts), 2):
                counts[parts[p + 1].strip(',')] = int(parts[p])
            for k, v in counts.items():
                if LEVEL == 1:
                    if total[k] < v:
                        ok = False
                elif LEVEL == 2:
                    total[k] = max(total[k], v)
        if ok:
            if LEVEL == 1:
                ans += i + 1
            else:
                ans += total["red"] * total["green"] * total["blue"]

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
    assert submit_answer(2023, 2, LEVEL, answer) is True


if __name__ == '__main__':
    main()
