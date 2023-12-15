from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [136, 64]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    A = [['#'] + [c for c in line] + ['#'] for line in input_string.split('\n')]
    A = [list('#' * len(A[0]))] + A + [list('#' * len(A[-1]))]
    # A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line.split())) for line in input_string.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    M = len(A[0])

    ans = 0

    seen = dict()
    TOTAL = 10**9
    R = 0
    while R < TOTAL:
        if R % 1000 == 0:
            print(R)
        for d in [0, 3, 2, 1]:
            for r in range(N):
                for c in range(M):
                    if A[r][c] != '#':
                        continue
                    n = 1
                    ct = 0
                    while 0 <= r - n * chr[d] < N and 0 <= c - n * chc[d] < M and A[r - n * chr[d]][c - n * chc[d]] != '#':
                        if A[r - n * chr[d]][c - n * chc[d]] == 'O':
                            ct += 1
                        A[r - n * chr[d]][c - n * chc[d]] = '.'
                        n += 1

                    for i in range(1, ct + 1):
                        A[r - i * chr[d]][c - i * chc[d]] = 'O'
            if LEVEL == 1:
                break
        if LEVEL == 1:
            break

        cur = ''.join([''.join(r) for r in A])
        if cur in seen:
            period = R - seen[cur]
            TOTAL = min(TOTAL, R + period + ((TOTAL - R) % period))
            print(R, seen[cur], TOTAL)
        else:
            seen[cur] = R
        R += 1
    print(TOTAL)

    for r in range(N):
        for c in range(M):
            if A[r][c] == 'O':
                ans += N - r - 1

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
    assert submit_answer(2023, 14, LEVEL, answer) is True


if __name__ == '__main__':
    main()
