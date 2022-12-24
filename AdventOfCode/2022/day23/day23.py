# from collections import *
# from itertools import *
# from math import *
from submit_answer import submit_answer



#      N   S   W   E
chr = [-1, 1,  0,  0, -1, -1,  1,  1]
chc = [0,  0, -1,  1, -1,  1, -1,  1]

achr = [
    [-1, -1, -1],
    [1, 1, 1],
    [-1, 0, 1],
    [-1, 0, 1]
]
achc = [
    [-1, 0, 1],
    [-1, 0, 1],
    [-1, -1, -1],
    [1, 1, 1]
]


LEVEL = 2
SAMPLE_ANSWERS = [110, 20]
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
    M = len(A[0])

    T = 10
    elves = [[]]
    for r in range(N):
        for c in range(M):
            if A[r][c] == '#':
                elves[0].append((r, c))

    t = 0
    while (LEVEL == 1 and T < 10) or (LEVEL == 2 and (len(elves) == 1 or elves[-1] != elves[-2])):
        print(t)
        current_elves = set(elves[-1])
        elves.append([e for e in elves[-1]])

        for elf_idx, elf in enumerate(elves[-1]):
            elf_r, elf_c = elf
            move = False
            for d in range(8):
                r = elf_r + chr[d]
                c = elf_c + chc[d]
                if (r, c) in current_elves:
                    move = True
                    break
            if move:
                for d in range(4):
                    direction = (d + t) % 4
                    ok = True
                    for d2 in range(3):
                        r = elf_r + achr[direction][d2]
                        c = elf_c + achc[direction][d2]
                        if (r, c) in elves[-2]:
                            ok = False
                            break
                    if ok:
                        # print("moving", elf_idx, direction)
                        elves[-1][elf_idx] = (elf_r + chr[direction], elf_c + chc[direction])
                        break

        bad_positions = set()
        for i in range(len(elves[-1])):
            for j in range(i + 1, len(elves[-1])):
                if elves[-1][i] == elves[-1][j]:
                    bad_positions.add(elves[-1][i])
        # print(bad_positions)

        for i in range(len(elves[-1])):
            if elves[-1][i] in bad_positions:
                elves[-1][i] = elves[-2][i]

        t += 1

    r_coords = [elf[0] for elf in elves[-1]]
    c_coords = [elf[1] for elf in elves[-1]]
    rows = max(r_coords) - min(r_coords) + 1
    cols = max(c_coords) - min(c_coords) + 1
    print(rows, cols)

    # for i in range(N):

    if LEVEL == 1:
        return rows * cols - len(elves[-1])
    else:
        return t


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
    assert submit_answer(2022, 23, LEVEL, answer) is True


if __name__ == '__main__':
    main()
