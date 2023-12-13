from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [374, 82000210]
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

    rows = []
    cols = []
    for i in range(N):
        if all([x == '.' for x in A[i]]):
            rows.append(i)
    for c in range(M):
        if all([row[c] == '.' for row in A]):
            cols.append(c)

    positions = []
    for i in range(N):
        for j in range(M):
            if A[i][j] == '#':
                positions.append((i, j))

    adds = 0
    for i, v1 in enumerate(positions):
        for j in range(i + 1, len(positions)):
            v2 = positions[j]
            for r in range(min(v1[0], v2[0]), max(v1[0], v2[0])):
                if r in rows:
                    adds += 1

            for c in range(min(v1[1], v2[1]), max(v1[1], v2[1])):
                if c in cols:
                    adds += 1
            ans1 += abs(v1[0] - v2[0]) + abs(v1[1] - v2[1])

    # for i in range(N):

    if LEVEL == 1:
        return ans1 + adds
    else:
        return ans1 + adds * (1000000 - 1)


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
    assert submit_answer(2023, 11, LEVEL, answer) is True


if __name__ == '__main__':
    main()
