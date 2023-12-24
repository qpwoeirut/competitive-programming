# had to look at AoC Reddit
# found https://www.reddit.com/r/adventofcode/comments/18pnycy/comment/keqf8uq very helpful
import itertools
from fractions import Fraction

from submit_answer import submit_answer

#      N   E   S   W
chr = [-1, 0, 1, 0, -1, -1, 1, 1]
chc = [0, 1, 0, -1, -1, 1, -1, 1]

LEVEL = 2
SAMPLE_ANSWERS = [2, 47]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]

EPS = 1e-2


def find_t(
        spd_i: list[int], spd_j: list[int], pos_i: list[int], pos_j: list[int]
) -> tuple[Fraction, Fraction]:
    a1 = spd_i[0]
    b1 = -spd_j[0]
    c1 = pos_i[0] - pos_j[0]
    a2 = spd_i[1]
    b2 = -spd_j[1]
    c2 = pos_i[1] - pos_j[1]

    denom = a1 * b2 - a2 * b1
    if denom != 0:
        t1 = Fraction(-(c1 * b2 - c2 * b1), denom)
        t2 = Fraction(-(a1 * c2 - a2 * c1), denom)
    else:
        t1 = None
        t2 = None
    return t1, t2


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

    TEST_LOW = 7 if N == 5 else 200000000000000
    TEST_HIGH = 27 if N == 5 else 400000000000000
    pos = [list(map(int, row.replace(',', '').split()[:3])) for row in A]
    spd = [list(map(int, row.replace(',', '').split()[4:])) for row in A]

    constraints = [set(), set(), set()]

    for i in range(N):
        for j in range(i + 1, N):
            t1, t2 = find_t(spd[i], spd[j], pos[i], pos[j])
            if t1 is not None and t2 is not None:
                px1 = spd[i][0] * t1 + pos[i][0]
                px2 = spd[j][0] * t2 + pos[j][0]
                assert px1 == px2, f"{px1} {px2}"

                py1 = spd[i][1] * t1 + pos[i][1]
                py2 = spd[j][1] * t2 + pos[j][1]
                assert py1 == py2, f"{py1} {py2}"

                # print(i, j, t1, t2, px1, py1)
                if t1 >= 0 and t2 >= 0 and TEST_LOW <= px1 <= TEST_HIGH and TEST_LOW <= py1 <= TEST_HIGH:
                    ans1 += 1

            for dim in range(3):
                if spd[i][dim] == spd[j][dim]:
                    constraints[dim].add((spd[i][dim], abs(pos[i][dim] - pos[j][dim])))

    print(constraints)
    velocities = [[], [], []]
    for dim in range(3):
        for v in range(-1000, 1001):
            if all([v != s and d % (v - s) == 0 for s, d in constraints[dim]]):
                velocities[dim].append(v)
    print(velocities)

    for v_x, v_y, v_z in itertools.product(*velocities):
        v_x1 = spd[0][0] - v_x
        v_y1 = spd[0][1] - v_y
        v_z1 = spd[0][2] - v_z

        v_x2 = spd[1][0] - v_x
        v_y2 = spd[1][1] - v_y
        v_z2 = spd[1][2] - v_z

        spd1 = [v_x1, v_y1, v_z1]
        spd2 = [v_x2, v_y2, v_z2]

        t1, t2 = find_t(spd1, spd2, pos[0], pos[1])
        print(t1, t2)

        if t1 is None or t2 is None:
            continue
        pos1 = [spd1[dim] * t1 + pos[0][dim] for dim in range(3)]
        pos2 = [spd2[dim] * t2 + pos[1][dim] for dim in range(3)]
        assert pos1[0] == pos2[0]
        assert pos1[1] == pos2[1]
        if pos1[2] == pos2[2]:
            spd3 = [spd[2][0] - v_x, spd[2][1] - v_y, spd[2][2] - v_z]
            t1_, t3 = find_t(spd1, spd3, pos[0], pos[2])
            pos3 = [spd3[dim] * t3 + pos[2][dim] for dim in range(3)]

            if t1 == t1_ and all([a == b for a, b in zip(pos1, pos3)]):  # add extra check
                ans2 = sum(pos1)

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
    assert submit_answer(2023, 24, LEVEL, answer) is True


if __name__ == '__main__':
    main()
