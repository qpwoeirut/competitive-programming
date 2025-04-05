import itertools
from collections import defaultdict

from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 1
SAMPLE_ANSWERS = [126384, None]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    A = [line for line in input_string.split('\n')]
    # A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line.split())) for line in input_string.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    # M = len(A[0])

    def numeric(pos):
        return [
            "789",
            "456",
            "123",
            ".0A"
        ][pos[0]][pos[1]]
    def directional(pos):
        return [
            ".^A",
            "<v>"
        ][pos[0]][pos[1]]
    def move_s(p0, s):
        d = '^>v<'.index(s)
        return p0[0] + chr[d], p0[1] + chc[d]

    def move(p0, p1):
        return move_s(p0, directional(p1))

    def valid_numeric(p):
        return 0 <= p[0] < 4 and 0 <= p[1] < 3 and p != (3, 0)

    def valid_directional(p):
        return 0 <= p[0] < 2 and 0 <= p[1] < 3 and p != (0, 0)

    ans1 = 0
    ans2 = 0
    for i in range(N):
        length = None

        # [idx][(r0, c0)][(r1, c1)][(r2, c2)]
        cost = [defaultdict(lambda: defaultdict(lambda: defaultdict(lambda: 10**9))) for _ in range(len(A[i]) + 1)]
        cost[0][(3, 2)][(0, 2)][(0, 2)] = 0
        q = [(0, (3, 2), (0, 2), (0, 2), 0)]
        while q:
            j, pos0, pos1, pos2, c = q.pop(0)
            if j == len(A[i]):
                length = c
                break
            if directional(pos1) == 'A' and directional(pos2) == 'A':
                if numeric(pos0) == A[i][j] and cost[j + 1][pos0][pos1][pos2] > c + 1:
                    cost[j + 1][pos0][pos1][pos2] = c + 1
                    # print(j + 1, pos0, pos1, pos2, c + 1, cost[j + 1][pos0][pos1][pos2])
                    q.append((j + 1, pos0, pos1, pos2, c + 1))
            elif directional(pos2) == 'A':
                np0 = move(pos0, pos1)
                if valid_numeric(np0) and cost[j][np0][pos1][pos2] > c + 1:
                    cost[j][np0][pos1][pos2] = c + 1
                    # print(j, np0, pos1, pos2, c + 1, cost[j][np0][pos1][pos2])
                    q.append((j, np0, pos1, pos2, c + 1))
            else:
                np1 = move(pos1, pos2)
                if valid_directional(np1) and cost[j][pos0][np1][pos2] > c + 1:
                    cost[j][pos0][np1][pos2] = c + 1
                    # print(j, pos0, np1, pos2, c + 1, cost[j][pos0][np1][pos2])
                    q.append((j, pos0, np1, pos2, c + 1))

            for ds in '^>v<':
                np2 = move_s(pos2, ds)
                if valid_directional(np2) and cost[j][pos0][pos1][np2] > c + 1:
                    cost[j][pos0][pos1][np2] = c + 1
                    # print(j, pos0, pos1, np2, c + 1, cost[j][pos0][pos1][np2])
                    q.append((j, pos0, pos1, np2, c + 1))

        assert length is not None
        print(length)
        num = int(A[i].removesuffix('A'))
        ans1 += length * num

        ans2 += length * num * 3



    if LEVEL == 1:
        return ans1
    else:
        return ans2


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
    assert submit_answer(2024, 21, LEVEL, answer) is True


if __name__ == '__main__':
    main()
