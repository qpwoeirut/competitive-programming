from collections import defaultdict

from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [36, 81]
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


    def score(row, col):
        ways = defaultdict(lambda: 0)
        ways[(row, col)] = 1
        q = [(row, col)]
        while q:
            r, c = q.pop(0)
            for dr, dc in zip(chr[:4], chc[:4]):
                nr = r + dr
                nc = c + dc
                if 0 <= nr < N and 0 <= nc < M:
                    if A[r][c] + 1 == A[nr][nc]:
                        ways[(nr, nc)] += ways[(r, c)]
                        if (nr, nc) not in q:
                            q.append((nr, nc))
        if LEVEL == 1:
            return sum(A[r][c] == 9 for r, c in ways.keys())
        else:
            return sum(val if A[k[0]][k[1]] == 9 else 0 for k, val in ways.items())

    for i in range(N):
        for j in range(M):
            if A[i][j] == 0:
                ans1 += score(i, j)
                ans2 += score(i, j)

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
    assert submit_answer(2024, 10, LEVEL, answer) is True


if __name__ == '__main__':
    main()
