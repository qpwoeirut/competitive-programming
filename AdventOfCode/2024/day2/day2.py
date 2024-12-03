from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [2, 4]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    # A = [line for line in input_string.split('\n')]
    # A = [int(line) for line in input_string.split('\n')]
    A = [list(map(int, line.split())) for line in input_string.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    # M = len(A[0])

    ans1 = 0
    ans2 = 0
    for i in range(N):
        incr = A[i].copy()
        incr.sort()

        ok = A[i] == incr or A[i] == incr[::-1]

        for j in range(1, len(A[i])):
            if not 1 <= abs(A[i][j-1] - A[i][j]) <= 3:
                ok = False

        ok2 = False
        for skip in range(len(A[i])):
            new = A[i][:skip] + A[i][skip + 1:]
            incr2 = new.copy()
            incr2.sort()
            ok2_i = new == incr2 or new == incr2[::-1]
            for j in range(1, len(new)):
                if not 1 <= abs(new[j-1] - new[j]) <= 3:
                    ok2_i = False
            ok2 |= ok2_i
            print(A[i], new, ok2)

        ans1 += ok
        ans2 += ok2


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
    assert submit_answer(2024, 2, LEVEL, answer) is True


if __name__ == '__main__':
    main()
