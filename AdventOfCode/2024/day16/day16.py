import queue

from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [11048, 64]
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
    M = len(A[0])

    ans1 = None
    ans2 = 0

    sr, sc = None, None
    er, ec = None, None
    for i in range(N):
        for j in range(M):
            if A[i][j] == 'S':
                sr = i
                sc = j
            if A[i][j] == 'E':
                er = i
                ec = j

    assert sr is not None and sc is not None
    assert er is not None and ec is not None

    def calc_cost(r0, c0, end):
        cost = [[[10**8 for _ in range(4)] for _ in range(M)] for _ in range(N)]
        q = queue.PriorityQueue()
        if end:
            for d in range(4):
                q.put_nowait((0, r0, c0, d))
                cost[r0][c0][d] = 0
        else:
            q.put_nowait((0, r0, c0, 1))
            cost[r0][c0][1] = 0
        while not q.empty():
            c, row, col, d = q.get_nowait()

            if cost[row][col][(d + 1) % 4] > c + 1000:
                cost[row][col][(d + 1) % 4] = c + 1000
                q.put_nowait((c + 1000, row, col, (d + 1) % 4))
            if cost[row][col][(d + 3) % 4] > c + 1000:
                cost[row][col][(d + 3) % 4] = c + 1000
                q.put_nowait((c + 1000, row, col, (d + 3) % 4))

            nr = row + chr[d]
            nc = col + chc[d]
            if 0 <= nr < N and 0 <= nc < M and A[nr][nc] != '#' and cost[nr][nc][d] > c + 1:
                cost[nr][nc][d] = c + 1
                q.put_nowait((c + 1, nr, nc, d))
        return cost


    # for i in range(N):
    ans1 = min(calc_cost(sr, sc, end=False)[er][ec])
    if LEVEL == 1:
        return ans1
    else:
        scost = calc_cost(sr, sc, end=False)
        ecost = calc_cost(er, ec, end=True)
        for r in range(N):
            for c in range(M):
                ans2 += min(scost[r][c][d] + ecost[r][c][(d + 2) % 4] for d in range(4)) == ans1
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
    assert submit_answer(2024, 16, LEVEL, answer) is True


if __name__ == '__main__':
    main()
