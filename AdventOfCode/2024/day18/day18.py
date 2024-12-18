from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [22, "6,1"]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    # A = [line for line in input_string.split('\n')]
    # A = [int(line) for line in input_string.split('\n')]
    A = [list(map(int, line.split(','))) for line in input_string.split('\n')]

    N = 7 if len(A) == 25 else 71
    print("N =", N)
    print(A[:10])

    def run(blocked: set):
        dist = [[10**9 for _ in range(N)] for _ in range(N)]
        q = [(0, 0)]
        dist[0][0] = 0
        while q:
            # print(q)
            r, c = q.pop(0)
            if r == N - 1 and c == N - 1:
                return dist[r][c]
            for d in range(4):
                nr = r + chr[d]
                nc = c + chc[d]
                if 0 <= nr < N and 0 <= nc < N and (nr, nc) not in blocked and dist[nr][nc] > dist[r][c] + 1:
                    dist[nr][nc] = dist[r][c] + 1
                    q.append((nr, nc))

    if LEVEL == 1:
        return run({(t[1], t[0]) for t in A[:12 if len(A) == 25 else 1024]})
    else:
        for i in range(len(A)):
            res = run({(t[1], t[0]) for t in A[:i]})
            if res is None:
                return f"{A[i-1][0]},{A[i-1][1]}"
        exit(1)


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
    assert submit_answer(2024, 18, LEVEL, answer) is True


if __name__ == '__main__':
    main()
