from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [14, 34]
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
    for i in range(N):
        print(i)
        for j in range(M):
            anti = False
            for r in range(-N, N):
                for c in range(-M, M):
                    if r == 0 and c == 0:
                        continue

                    for y in range(max(N, M)) if LEVEL == 2 else [-1]:
                        if not (0 <= i - y * r < N and 0 <= j - y * c < M):
                            break
                        for x in range(max(N, M)) if LEVEL == 2 else [2]:
                            if x == y:
                                continue
                            if 0 <= i - y * r < N and 0 <= j - y * c < M and 0 <= i + x * r < N and 0 <= j + x * c < M:
                                anti |= A[i - y * r][j - y * c] == A[i + x * r][j + x * c] and A[i - y * r][j - y * c] != '.'
                            if 0 <= i - y * r < N and 0 <= j - y * c < M and 0 <= i - x * r < N and 0 <= j - x * c < M:
                                anti |= A[i - y * r][j - y * c] == A[i - x * r][j - x * c] and A[i - y * r][j - y * c] != '.'
            ans1 += anti
            ans2 += anti

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
    assert submit_answer(2024, 8, LEVEL, answer) is True


if __name__ == '__main__':
    main()
