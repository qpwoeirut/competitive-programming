# from collections import *
# from itertools import *
# from math import *
from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = ["CMZ", "MCD"]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(s: str) -> str:
    # A = list(map(int, s.split(',')))
    A = [line for line in s.split('\n')]
    # A = [line.strip() for line in s.split('\n')]
    # A = [list(map(int, line.strip())) for line in s.split('\n')]

    N = len(A)
    M = (len(A[0]) + 3) // 4
    print("N,M =", N, M)

    stacks = [[] for _ in range(M)]
    instructions = -1

    for i in range(N):
        if A[i].strip().startswith("1"):
            continue
        if len(A[i].strip()) == 0:
            continue
        if A[i].startswith("move"):
            instructions = i
            break
        for j in range((len(A[i]) + 3) // 4):
            c = A[i][j * 4 + 1]
            if c != ' ':
                stacks[j] = [c] + stacks[j]

    print(stacks)
    print(instructions)

    assert instructions != -1

    for i in range(instructions, N):
        _, n, _, a, _, b = A[i].split()
        n = int(n)
        a = int(a) - 1
        b = int(b) - 1
        if LEVEL == 1:
            for _ in range(n):
                stacks[b].append(stacks[a].pop())
        else:
            print(stacks[a], stacks[b], n)
            stacks[b].extend(stacks[a][-n:])
            stacks[a] = stacks[a][:-n]
            print(stacks[a], stacks[b], n)
            print()

    ans = ''.join([stack[-1] for stack in stacks])
    assert len(ans) == M

    # for i in range(N):

    return ans


def main():
    with open("sample.txt") as sample_file:
        sample_input = sample_file.read().strip('\n')
    sample_answer = solve(sample_input)
    print("Answer for sample:", sample_answer)
    assert sample_answer == SAMPLE_ANSWER,\
        f"Got {sample_answer} instead of {SAMPLE_ANSWER}"

    with open("input.txt") as input_file:
        inp = input_file.read().strip('\n')
    answer = solve(inp)
    print("Answer:", answer)
    assert submit_answer(2022, 5, LEVEL, answer) is True


if __name__ == '__main__':
    main()
