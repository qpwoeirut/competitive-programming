import collections
import heapq

from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [102, 94]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    # A = [line for line in input_string.split('\n')]
    # A = [int(line) for line in input_string.split('\n')]
    A = [list(map(int, line)) for line in input_string.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    M = len(A[0])

    ans1 = 0
    ans2 = 0
    # for i in range(N):

    inf = 10**5
    cost = [[[[inf, inf, inf, inf] for _ in range(4)] for _ in row] for row in A]

    q = []
    for d in range(4):
        cost[0][0][d][0] = 0
        heapq.heappush(q, (0, 0, 0, d, 0))

    while q:
        co, r, c, d, n = heapq.heappop(q)
        if r == N - 1 and c == M - 1:
            ans1 = co
            break
        if cost[r][c][d][n] < co:
            continue

        for i in range(4):
            nr = r + chr[i]
            nc = c + chc[i]
            nn = 1 if i != d else n + 1
            if not (0 <= nr < N and 0 <= nc < M) or nn > 3 or abs(d - i) == 2:
                continue

            if cost[nr][nc][i][nn] > co + A[nr][nc]:
                cost[nr][nc][i][nn] = co + A[nr][nc]
                heapq.heappush(q, (cost[nr][nc][i][nn], nr, nc, i, nn))

    cost = [[[[inf for _ in range(11)] for _ in range(4)] for _ in row] for row in A]

    q = []
    for d in range(4):
        cost[0][0][d][0] = 0
        heapq.heappush(q, (0, 0, 0, d, 0))

    while q:
        co, r, c, d, n = heapq.heappop(q)
        if r == N - 1 and c == M - 1 and n >= 4:
            ans2 = co
            break
        if cost[r][c][d][n] < co:
            continue

        for i in range(4):
            nr = r + chr[i]
            nc = c + chc[i]
            nn = 1 if i != d else n + 1
            if not (0 <= nr < N and 0 <= nc < M) or (n < 4 and i != d) or nn > 10 or abs(d - i) == 2:
                continue

            if cost[nr][nc][i][nn] > co + A[nr][nc]:
                cost[nr][nc][i][nn] = co + A[nr][nc]
                heapq.heappush(q, (cost[nr][nc][i][nn], nr, nc, i, nn))

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
    assert submit_answer(2023, 17, LEVEL, answer) is True


if __name__ == '__main__':
    main()
