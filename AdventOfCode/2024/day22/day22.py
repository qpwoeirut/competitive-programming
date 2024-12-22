import itertools

from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [37327623, 23]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    # A = [line for line in input_string.split('\n')]
    A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line.split())) for line in input_string.split('\n')]
    # A = [123]

    N = len(A)
    print("N =", N)
    print(A[:10])
    # M = len(A[0])

    ans1 = 0
    ans2 = 0
    history = [[x % 10] for x in A]
    for i in range(N):
        x = A[i]
        for _ in range(2000):
            x ^= x * 64
            x %= 16777216
            x ^= x >> 5
            x %= 16777216
            x ^= x * 2048
            x %= 16777216
            history[i].append(x % 10)
        ans1 += x


    val = [dict() for _ in range(N)]
    for i in range(N):
        for j in range(2000 - 4):
            ch = tuple([history[i][j + k + 1] - history[i][j + k] for k in range(4)])
            if ch not in val[i]:
                val[i][ch] = history[i][j + 4]

    print(sum(map(len, val)))

    for ch in itertools.product(range(-9, 10), repeat=4):
        cur = 0
        for i in range(N):
            cur += val[i].get(ch, 0)
        ans2 = max(ans2, cur)

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
    assert submit_answer(2024, 22, LEVEL, answer) is True


if __name__ == '__main__':
    main()
