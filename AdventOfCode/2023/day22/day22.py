import copy

from submit_answer import submit_answer

#      N   E   S   W
chr = [-1, 0, 1, 0, -1, -1, 1, 1]
chc = [0, 1, 0, -1, -1, 1, -1, 1]

LEVEL = 2
SAMPLE_ANSWERS = [5, 7]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def interval_intersect(a1: int, a2: int, b1: int, b2: int):
    return a1 <= b1 <= a2 or b1 <= a1 <= b2


def xy_intersect(pos1: list[int], pos2: list[int]):
    return (interval_intersect(pos1[0], pos1[3], pos2[0], pos2[3]) and
            interval_intersect(pos1[1], pos1[4], pos2[1], pos2[4]))


def move_all(pos: list[list[int]], to_skip: int or None) -> set[int]:
    N = len(pos)
    moved = set()
    for i in range(N):
        if i == to_skip:
            continue

        limit = -1
        for j in range(N):
            if i == j or j == to_skip:
                continue
            if pos[i][2] > pos[j][5] and xy_intersect(pos[i], pos[j]):
                limit = max(limit, pos[j][5])
        shift = pos[i][2] - limit - 1
        if shift > 0:
            moved.add(i)
            pos[i][2] -= shift
            pos[i][5] -= shift

    return moved


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    A = [line for line in input_string.split('\n')]
    # A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line.split())) for line in input_string.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    # M = len(A[0])

    ans1 = 0
    ans2 = 0

    pos = [list(map(int, row.replace('~', ',').split(','))) for row in A]
    while move_all(pos, to_skip=None):
        pass

    print("Finished falling")

    # takes a few minutes but works
    for test in range(N):
        if test % 10 == 0:
            print("Testing", test)
        moved = set()
        cur = copy.deepcopy(pos)
        while moves := move_all(cur, to_skip=test):
            moved.update(moves)
        if not moved:
            ans1 += 1
        ans2 += len(moved)

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
    assert submit_answer(2023, 22, LEVEL, answer) is True


if __name__ == '__main__':
    main()
