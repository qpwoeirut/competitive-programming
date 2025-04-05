from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 1
SAMPLE_ANSWERS = [0, None]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    A = [list(line) for line in input_string.split('\n')]
    # A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line.split())) for line in input_string.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    M = len(A[0])

    ans1 = 0
    ans2 = 0

    start = None
    for r in range(N):
        for c in range(M):
            if A[r][c] == 'S':
                start = r, c
    assert isinstance(start, tuple)

    def cost(skr, skc):
        q = [(start[0], start[1], 0)]
        vis = {start}
        while q:
            r, c, dist = q.pop(0)
            if A[r][c] == 'E':
                return dist
            for d in range(4):
                nr = r + chr[d]
                nc = c + chc[d]
                if 0 <= nr < N and 0 <= nc < M and ((nr == skr and nc == skc) or A[nr][nc] != '#') and (nr, nc) not in vis:
                    vis.add((nr, nc))
                    q.append((nr, nc, dist + 1))
        raise ValueError

    init = cost(-1, -1)
    for i in range(N):
        print(i)
        for j in range(M):
            if i == 0 or j == 0 or i + 1 == N or j + 1 == M:
                continue
            ans1 += init - cost(i, j) >= 100

    # for i in range(N):

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
    assert submit_answer(2024, 20, LEVEL, answer) is True


if __name__ == '__main__':
    main()
