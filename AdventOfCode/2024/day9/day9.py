from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [1928, 2858]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(input_string: str) -> int or str:
    A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    # A = [line for line in input_string.split('\n')]
    # A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line.split())) for line in input_string.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    # M = len(A[0])

    ans1 = 0
    ans2 = 0
    arr = []
    cur_id = 0
    for i in range(N):
        if i % 2 == 0:
            arr.extend([cur_id for _ in range(int(A[i]))])
            cur_id += 1
        else:
            arr.extend([-1 for _ in range(int(A[i]))])

    i = 0
    while i < len(arr):
        while i < len(arr) and arr[i] == -1:
            arr[i] = arr.pop()
        i += 1

    for i, v in enumerate(arr):
        ans1 += i * v

    arr = [[int(v), i >> 1 if i % 2 == 0 else -1] for i, v in enumerate(A)]
    i = len(arr) - 1
    while i > 0:
        if arr[i][1] == -1:
            i -= 1
            continue
        for j, t in enumerate(arr):
            if j >= i:
                break
            if t[0] >= arr[i][0] and t[1] == -1:
                t[0] -= arr[i][0]
                assert arr[i - 1][1] == -1
                arr[i - 1][0] += arr[i][0]

                if i + 1 < len(arr) and arr[i + 1][1] == -1:
                    arr[i - 1][0] += arr[i + 1][0]
                    arr.pop(i + 1)

                arr.insert(j, arr.pop(i))
                break
        i -= 1

    idx = 0
    for sz, id_ in arr:
        for _ in range(sz):
            ans2 += idx * max(0, id_)
            idx += 1

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
    assert submit_answer(2024, 9, LEVEL, answer) is True


if __name__ == '__main__':
    main()
