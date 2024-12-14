import time

from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [12, None]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    A = [line.replace(',', ' ').replace('=', ' ') for line in input_string.split('\n')]
    # A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line.split())) for line in input_string.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    # M = len(A[0])

    robots = []
    ans1 = 0
    ans2 = 0
    for i in range(N):
        _, pc, pr, _, vc, vr = A[i].split()
        pc, pr, vc, vr = map(int, (pc, pr, vc, vr))
        robots.append((pr, pc, vr, vc))

    if len(robots) < 20:
        N = 7
        M = 11
    else:
        N = 103
        M = 101


    def dfs(r, c, vis: set, G: list[list[str]]):
        if not (0 <= r < N and 0 <= c < M) or (r, c) in vis or G[r][c] != '#':
            return
        vis.add((r, c))
        for d in range(8):
            dfs(r + chr[d], c + chc[d], vis, G)

    for t in range(100 if LEVEL == 1 else 100000):
        for i in range(len(robots)):
            row, col, vr, vc = robots[i]
            robots[i] = ((row + vr) % N, (col + vc) % M, vr, vc)

        if LEVEL == 2:
            G = [['.' for _ in range(M)] for _ in range(N)]
            for row, col, _, _ in robots:
                G[row][col] = '#'
            vis = set()

            components = 0
            for r in range(N):
                for c in range(M):
                    if (r, c) not in vis and G[r][c] == '#':
                        components += 1
                        dfs(r, c, vis, G)
            if components < 200 or t % 1000 == 0:
                print(t, components)
            if components < 200:
                print('\n'.join([''.join(r) for r in G]))
                ans2 = t + 1
                break

    q = [0, 0, 0, 0]
    for row, col, _, _ in robots:
        qrt = 0
        if row == N // 2 or col == M // 2:
            continue
        if row > N // 2:
            qrt += 1
        if col > M // 2:
            qrt += 2
        q[qrt] += 1

    ans1 = q[0] * q[1] * q[2] * q[3]
    # for i in range(N):

    if LEVEL == 1:
        return ans1
    else:
        return ans2


def main():
    if LEVEL == 1:
        with open("sample.txt") as sample_file:
            sample_input = sample_file.read().strip('\n')
        sample_answer = solve(sample_input)
        print("Answer for sample:", sample_answer)
        assert sample_answer == SAMPLE_ANSWER and sample_answer is not None, f"Got {sample_answer} instead of {SAMPLE_ANSWER}"

    with open("input.txt") as input_file:
        inp = input_file.read().strip('\n')
    answer = solve(inp)
    print("Answer:", answer)
    assert submit_answer(2024, 14, LEVEL, answer) is True


if __name__ == '__main__':
    main()
