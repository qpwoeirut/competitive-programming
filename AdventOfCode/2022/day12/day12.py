# from collections import *
# from itertools import *
# from math import *
from collections import deque

from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [31, 29]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(s: str) -> int or str:
    # A = list(s)
    # A = list(map(int, s.split(',')))
    A = [list(line) for line in s.split('\n')]
    # A = [line for line in s.split('\n')]
    # A = [list(map(int, line)) for line in s.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    M = len(A[0])

    start = 0, 0, 0
    er, ec = 0, 0
    for i in range(N):
        for j in range(M):
            if LEVEL == 1:
                if A[i][j] == 'S':
                    start = i, j, 0
                    A[i][j] = 'a'
                if A[i][j] == 'E':
                    er = i
                    ec = j
                    A[i][j] = 'z'
            elif LEVEL == 2:
                if A[i][j] == 'E':
                    start = i, j, 0
                    A[i][j] = 'z'
                if A[i][j] == 'S':
                    A[i][j] = 'a'

    vis = set()
    vis.add((start[0], start[1]))
    q = deque(maxlen=N*M)
    q.append(start)
    while q:
        r, c, dist = q.popleft()
        print(r, c, dist, A[r][c])

        if LEVEL == 1 and r == er and c == ec:
            return dist

        if LEVEL == 2 and A[r][c] == 'a':
            return dist

        for d in range(4):
            nr = r + chr[d]
            nc = c + chc[d]
            if nr < 0 or nr >= N or nc < 0 or nc >= M or (nr, nc) in vis:
                continue
            if LEVEL == 1 and ord(A[nr][nc]) - ord(A[r][c]) > 1:
                continue
            if LEVEL == 2 and ord(A[nr][nc]) - ord(A[r][c]) < -1:
                continue
            vis.add((nr, nc))
            q.append((nr, nc, dist + 1))


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
    assert submit_answer(2022, 12, LEVEL, answer) is True


if __name__ == '__main__':
    main()
