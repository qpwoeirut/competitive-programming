from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [1320, 145]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def hash(s):
    h = 0
    for c in s:
        h = (h + ord(c)) * 17
    h %= 256
    return h


def solve(input_string: str) -> int or str:
    A = input_string.split(',')
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    # A = [line for line in input_string.split('\n')]
    # A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line.split())) for line in input_string.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    # M = len(A[0])

    boxes = [[] for _ in range(256)]
    ans1 = 0
    ans2 = 0
    for i in range(N):
        ans1 += hash(A[i])

        if A[i][-1] == '-':
            h = hash(A[i][:-1])
            boxes[h] = [b for b in boxes[h] if b[0] != A[i][:-1]]
        else:
            label, val = A[i].split('=')
            h = hash(label)
            ok = False
            for box in boxes:
                for i in range(len(box)):
                    if box[i][0] == label:
                        box[i] = (label, int(val))
                        ok = True
            if not ok:
                boxes[h].append((label, int(val)))

    # for i in range(N):
    for b_i, box in enumerate(boxes):
        for i in range(len(box)):
            val = (b_i + 1) * (i + 1) * box[i][1]
            print(b_i, i, box[i], val)
            ans2 += val

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
    assert submit_answer(2023, 15, LEVEL, answer) is True


if __name__ == '__main__':
    main()
