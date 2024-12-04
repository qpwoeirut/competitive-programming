from submit_answer import submit_answer

#      N   E   S   W
chr = [-1, 0, 1, 0, -1, -1, 1, 1]
chc = [0, 1, 0, -1, -1, 1, -1, 1]

LEVEL = 2
SAMPLE_ANSWERS = [18, 9]
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
        ans1 += A[i].count('XMAS') + A[i][::-1].count('XMAS')
        for j in range(M):
            try:
                s = ""
                for x in range(4):
                    s += A[i + x][j + x]
                ans1 += s == 'XMAS' or s == 'SAMX'
            except IndexError:
                pass

            try:
                s = ""
                for x in range(4):
                    if j - x < 0:
                        raise IndexError
                    s += A[i + x][j - x]
                ans1 += s == 'XMAS' or s == 'SAMX'
            except IndexError:
                pass

            try:
                s = ""
                for x in range(4):
                    s += A[i + x][j]
                ans1 += s == 'XMAS' or s == 'SAMX'
            except IndexError:
                pass

            if 1 <= i < N - 1 and 1 <= j < M - 1 and A[i][j] == 'A':
                # st1 = {A[i - 1][j], A[i + 1][j]}
                # st2 = {A[i][j - 1], A[i][j + 1]}
                # if st1 == {'M', 'S'} and st2 == {'M', 'S'}:
                #     ans2 += 1
                st1 = {A[i - 1][j - 1], A[i + 1][j + 1]}
                st2 = {A[i - 1][j + 1], A[i + 1][j - 1]}
                if st1 == {'M', 'S'} and st2 == {'M', 'S'}:
                    ans2 += 1

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
    assert submit_answer(2024, 4, LEVEL, answer) is True


if __name__ == '__main__':
    main()
