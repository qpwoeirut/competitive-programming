# from collections import *
# from itertools import *
# from math import *
from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]
dirs = "URDL"


LEVEL = 2
SAMPLE_ANSWERS = [13, 36]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(s: str) -> int or str:
    # A = list(s)
    # A = list(map(int, s.split(',')))
    A = [line for line in s.split('\n')]
    # A = [line for line in s.split('\n')]
    # A = [list(map(int, line)) for line in s.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    # M = len(A[0])

    visited = set()
    snake = [(0, 0) for _ in range(2 if LEVEL == 1 else 10)]

    visited.add((0, 0))

    def move_tail(x_h, y_h, x_t, y_t):
        if abs(x_h - x_t) > 1 or abs(y_h - y_t) > 1:
            if x_h == x_t:
                y_t = (y_h + y_t) // 2
            elif y_h == y_t:
                x_t = (x_h + x_t) // 2
            else:
                if abs(x_h - x_t) == 1:
                    x_t = x_h
                else:
                    x_t = (x_h + x_t) // 2
                if abs(y_h - y_t) == 1:
                    y_t = y_h
                else:
                    y_t = (y_h + y_t) // 2
        return x_t, y_t

    for i in range(N):
        dir, n = A[i].split()
        dir = dirs.index(dir)
        n = int(n)
        for _ in range(n):
            nc = snake[0][0] + chc[dir]
            nr = snake[0][1] + chr[dir]
            snake[0] = (nc, nr)

            for j in range(1, 10):
                snake[j] = move_tail(*snake[j-1], *snake[j])

            visited.add(snake[9])
        print(snake[0], snake[9])



    # for i in range(N):

    return len(visited)


def main():
    with open("sample.txt") as sample_file:
        sample_input = sample_file.read().strip('\n')
    sample_answer = solve(sample_input)
    print("Answer for sample:", sample_answer)
    assert sample_answer == SAMPLE_ANSWER, f"Got {sample_answer} instead of {SAMPLE_ANSWER}"

    with open("input.txt") as input_file:
        inp = input_file.read().strip('\n')
    answer = solve(inp)
    print("Answer:", answer)
    assert submit_answer(2022, 9, LEVEL, answer) is True


if __name__ == '__main__':
    main()
