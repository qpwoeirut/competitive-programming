from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [41, 6]
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

    ans1 = 0
    ans2 = 0
    # for i in range(N):

    sr, sc = -1, -1
    dd = -1
    for r in range(N):
        for c in range(M):
            if A[r][c] in '^>v<':
                dd = '^>v<'.index(A[r][c])
                sr = r
                sc = c
    assert sr != -1 and sc != -1 and dd != -1

    def check(obs_r, obs_c):
        d = dd
        row = sr
        col = sc
        vis = {(row, col)}
        moves = 0
        while 0 <= row < N and 0 <= col < M and moves <= len(vis) * 8:
            moves += 1
            nr = row + chr[d]
            nc = col + chc[d]
            if 0 <= nr < N and 0 <= nc < M and (A[nr][nc] == '#' or (nr == obs_r and nc == obs_c)):
                d = (d + 1) % 4
            else:
                row = nr
                col = nc
                vis.add((nr, nc))

        if moves > len(vis) * 8:
            return N * M + 1
        return len(vis) - 1

    ans1 = check(-1, -1)
    for r in range(N):
        print(r)
        for c in range(M):
            if check(r, c) > N * M:
                ans2 += 1
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
    assert submit_answer(2024, 6, LEVEL, answer) is True


if __name__ == '__main__':
    main()
