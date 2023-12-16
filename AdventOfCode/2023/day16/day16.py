from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 1
SAMPLE_ANSWERS = [46, 51]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def energize(A, N, M, sr, sc, d):
    visited = [[[False for _ in range(4)] for c in row] for row in A]
    beams = [(sr, sc, d)]
    first = True
    while beams:
        r, c, d = beams.pop()
        if not first:
            if not (0 <= r < N and 0 <= c < M) or visited[r][c][d]:
                continue
            visited[r][c][d] = True
        first = False

        nr = r + chr[d]
        nc = c + chc[d]
        if 0 <= nr < N and 0 <= nc < M:
            if A[nr][nc] == '\\':
                d ^= 3
                beams.append((nr, nc, d))
            elif A[nr][nc] == '/':
                d ^= 1
                beams.append((nr, nc, d))
            elif A[nr][nc] == '-' and d in (0, 2):
                beams.append((nr, nc, 1))
                beams.append((nr, nc, 3))
            elif A[nr][nc] == '|' and d in (1, 3):
                beams.append((nr, nc, 0))
                beams.append((nr, nc, 2))
            else:
                beams.append((nr, nc, d))

    return sum([[any(x) for x in row].count(True) for row in visited])


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
    for r in range(N):
        ans2 = max(ans2, energize(A, N, M, r, -1, 1), energize(A, N, M, r, M, 3))
    for c in range(N):
        ans2 = max(ans2, energize(A, N, M, -1, c, 2), energize(A, N, M, c, N, 0))

    if LEVEL == 1:
        return energize(A, N, M, 0, -1, 1)
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
    assert submit_answer(2023, 16, LEVEL, answer) is True


if __name__ == '__main__':
    main()
