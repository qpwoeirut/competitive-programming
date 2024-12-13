from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [1930, 1206]
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

    def get(r, c):
        return A[r][c] if 0 <= r < N and 0 <= c < M else '!'

    vis = set()
    def dfs(r, c, val, pd):
        if not (0 <= r < N and 0 <= c < M) or A[r][c] != val:
            if pd == -1:
                s = 0
            elif pd % 2 == 0:
                pr = r - chr[pd]
                s = c == 0 or get(pr, c - 1) != val or get(r, c - 1) == val
            else:
                pc = c - chc[pd]
                s = r == 0 or get(r - 1, pc) != val or get(r - 1, c) == val
            return 0, 1, s
        if (r, c) in vis:
            return 0, 0, 0
        vis.add((r, c))
        aa = 1
        pp = 0
        si = 0
        for d in range(4):
            a, p, s = dfs(r + chr[d], c + chc[d], val, d)
            aa += a
            pp += p
            si += s
        return aa, pp, si

    for i in range(N):
        for j in range(M):
            a, p, s = dfs(i, j, A[i][j], -1)
            ans1 += a * p
            ans2 += a * s
            if a:
                print(a, p, s, A[i][j])

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
    assert submit_answer(2024, 12, LEVEL, answer) is True


if __name__ == '__main__':
    main()
