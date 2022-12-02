# from collections import *
# from itertools import *
# from math import *
from submit_answer import submit_answer


LEVEL = 2
SAMPLE_ANSWERS = [15, 12]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]

val = {
    "X": 1,
    "Y": 2,
    "Z": 3
}
shape = {
    "A": {"X": 3, "Y": 6, "Z": 0},
    "B": {"X": 0, "Y": 3, "Z": 6},
    "C": {"X": 6, "Y": 0, "Z": 3}
}
result = {
    "A": {"X": 'Z', 'Y': 'X', 'Z': 'Y'},
    'B': {'X': 'X', 'Y': 'Y', 'Z': 'Z'},
    'C': {'X': 'Y', 'Y': 'Z', 'Z': 'X'}
}


def solve(s: str):
    # A = list(map(int, file.readline().split(',')))
    A = [line.strip().split() for line in s.split('\n')]
    # A = [line.strip() for line in file]
    # A = [list(map(int, line.strip())) for line in file]

    N = len(A)
    print("N =", N)
    print(A[:10])
    # M = len(A[0])

    score = 0
    score2 = 0
    for i in range(N):
        print(A[i])
        score += val[A[i][1]]
        score += shape[A[i][0]][A[i][1]]

        mv = result[A[i][0]][A[i][1]]
        score2 += (ord(A[i][1]) - ord('X')) * 3
        score2 += val[mv]


    # for i in range(N):

    if LEVEL == 1:
        return score
    else:
        return score2

def main():
    with open("sample.txt") as sample_file:
        sample_input = sample_file.read().strip()
    sample_answer = solve(sample_input)
    print("Answer for sample:", sample_answer)
    assert solve(sample_input) == SAMPLE_ANSWER or SAMPLE_ANSWER is None, f"Got {sample_answer} instead of {SAMPLE_ANSWER}"

    with open("input.txt") as input_file:
        inp = input_file.read().strip()
    answer = solve(inp)
    print("Answer:", answer)
    assert submit_answer(2022, 2, LEVEL, answer) is True


if __name__ == '__main__':
    main()
