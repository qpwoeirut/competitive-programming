import collections

from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [55312, None]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    A = list(map(int, input_string.split()))
    # A = [line for line in input_string.split('\n')]
    # A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line.split())) for line in input_string]

    N = len(A)
    print("N =", N)
    print(A[:10])
    # M = len(A[0])

    A = collections.Counter(A)

    ans1 = 0
    ans2 = 0
    for i in range(75 if LEVEL == 2 else 25):
        B = collections.Counter()
        print(i, len(A))
        for val, ct in A.items():
            s = str(val)
            if val == 0:
                B[1] += ct
            elif len(s) % 2 == 0:
                n = len(s)
                B[int(s[:n//2])] += ct
                B[int(s[n//2:])] += ct
            else:
                B[val * 2024] += ct
        A = B.copy()
    ans1 = sum(A.values())
    ans2 = sum(A.values())

    # for i in range(N):


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
    if LEVEL == 1:
        assert sample_answer == SAMPLE_ANSWER and sample_answer is not None, f"Got {sample_answer} instead of {SAMPLE_ANSWER}"

    with open("input.txt") as input_file:
        inp = input_file.read().strip('\n')
    answer = solve(inp)
    print("Answer:", answer)
    assert submit_answer(2024, 11, LEVEL, answer) is True


if __name__ == '__main__':
    main()