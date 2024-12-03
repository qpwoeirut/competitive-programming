from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [161, 48]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def parse(s:str):
    print(s)
    s = s.removeprefix('mul')
    s = s.removeprefix('(').removesuffix(')')
    a, b = s.split(',')
    return int(a) * int(b)


def okay(s: str):
    if not s.startswith('mul('[:len(s)]):
        return False
    if len(s) <= 4:
        return True

    # print(f'{s = }')

    s = s.removeprefix('mul(')
    a = ""
    x = 0
    for i, c in enumerate(s):
        if c.isdigit():
            x = i + 1
            a += c
        else:
            break
    s = s[x:]
    # print(f'{s = } {a = }')
    if s and s[0] != ',':
        return False

    s = s[1:]

    b = ""
    i = 0
    for i, c in enumerate(s):
        if c.isdigit():
            b += c
        else:
            break
    s = s[i+1:]
    # print(f'{s = } {a = } {b = }')
    if s and s[0] != ')':
        return False

    return True


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    # A = [line for line in input_string.split('\n')]
    # A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line.split())) for line in input_string.split('\n')]
    A = input_string

    N = len(A)
    print("N =", N)
    print(A[:10])
    # M = len(A[0])

    ans1 = 0
    ans2 = 0
    cur = ""
    mode = True
    for i in range(N):
        cur += A[i]
        if not okay(cur):
            cur = ""
        if cur and cur[-1] == ')':
            ans1 += parse(cur)
            if mode:
                ans2 += parse(cur)

            cur = ""
        print(A[i:])
        if A[i:].startswith('do()'):
            mode = True
        if A[i:].startswith("don't()"):
            print(mode)
            mode = False

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
    assert submit_answer(2024, 3, LEVEL, answer) is True


if __name__ == '__main__':
    main()
