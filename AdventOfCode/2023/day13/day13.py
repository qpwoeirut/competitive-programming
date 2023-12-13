from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 1
SAMPLE_ANSWERS = [405, 400]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def vert(A, n):
    ct = 0
    for row in A:
        for i in range(len(row)):
            L = n - i - 1
            R = n + i
            if 0 <= L < len(row) and 0 <= R < len(row) and row[L] != row[R]:
                ct += 1
                if ct > 1:
                    return False
    return ct == LEVEL - 1


def hori(A, n):
    ct = 0
    for col in range(len(A[0])):
        for i in range(len(A)):
            L = n - i - 1
            R = n + i
            if 0 <= L < len(A) and 0 <= R < len(A) and A[L][col] != A[R][col]:
                ct += 1
                if ct > 1:
                    return False
    return ct == LEVEL - 1



def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    inputs = input_string.split('\n\n')
    # A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line.split())) for line in input_string.split('\n')]

    ans1 = 0
    ans2 = 0
    for A in inputs:
        A = [line for line in A.split('\n')]
        N = len(A)
        print("N =", N)
        print(A[:10])
        M = len(A[0])

        for r in range(1, N):
            if hori(A, r):
                ans1 += 100 * r
        for c in range(1, M):
            if vert(A, c):
                ans1 += c
    ans2 = ans1


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
    assert submit_answer(2023, 13, LEVEL, answer) is True


if __name__ == '__main__':
    main()
