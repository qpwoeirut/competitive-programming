from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [3749, 11387]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    A = [line for line in input_string.split('\n')]
    # A = [int(line) for line in input_string.split('\n')]
    A = [list(map(int, line.replace(':', '').split())) for line in input_string.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    # M = len(A[0])

    ans1 = 0
    ans2 = 0
    for i in range(N):
        arr = A[i].copy()
        x, a = arr[0], arr[1]
        arr = arr[2:]

        possible = {a}
        for y in arr:
            pos = {z + y for z in possible} | {z * y for z in possible}
            if LEVEL == 2:
                pos |= {int(str(z) + str(y)) for z in possible}
            possible = pos

        if x in possible:
            ans1 += x
            ans2 += x



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
    assert submit_answer(2024, 7, LEVEL, answer) is True


if __name__ == '__main__':
    main()
