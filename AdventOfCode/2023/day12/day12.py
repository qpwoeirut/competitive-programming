from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [21, 525152]
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


    ans = 0
    for i in range(N):
        springs, sizes = A[i].split()
        sizes = list(map(int, sizes.split(',')))

        if LEVEL == 2:
            springs = '?'.join([springs for _ in range(5)])
            sizes = sizes * 5

        springs = '.' + springs + '.'
        M = len(springs)

        dp = [[0 for _ in range(len(sizes) + 1)] for _ in range(M + 1)]
        dp[0][0] = 1
        for idx in range(M):
            for s_i, sz in enumerate(sizes):
                if not springs[idx] in ".?":
                    continue
                if idx + sz + 1 < M and set(springs[idx + 1: idx + sz + 1]) <= {'#', '?'} and springs[idx + sz + 1] in ".?":
                    dp[idx + sz + 1][s_i + 1] += dp[idx][s_i]
            for s_i in range(len(sizes) + 1):
                if not springs[idx] in ".?":
                    continue
                dp[idx + 1][s_i] += dp[idx][s_i]
        ans += dp[M][len(sizes)]

    # for i in range(N):

    return ans


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
    assert submit_answer(2023, 12, LEVEL, answer) is True


if __name__ == '__main__':
    main()
