# from collections import *
# from itertools import *
# from math import *
import itertools
from typing import Tuple

from submit_answer import submit_answer

#      N   E   S   W
chr = [-1, 0, 1, 0, -1, -1, 1, 1]
chc = [0, 1, 0, -1, -1, 1, -1, 1]

LEVEL = 2
SAMPLE_ANSWERS = [33, 56 * 62]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]

# blueprint = namedtuple("blueprint", "ore_rb clay_rb obs_rb_ore obs_rb_clay geo_rb_ore geo_rb_obs")
# conditions = namedtuple("conditions", "time ore_rb clay_rb obs_rb geo_rb ore clay obs geode")
initial = (0, 1, 0, 0, 0, 0, 0, 0, 0)

dp = dict()
T = 24 if LEVEL == 1 else 32


def solve_blueprint(cnd: Tuple[int, int, int, int, int, int, int, int, int], bp: Tuple[int, int, int, int, int, int]) -> int:
    if cnd[0] == T - 1:
        return cnd[8] + cnd[4]
    if cnd in dp:
        return dp[cnd]
    for x in itertools.product(range((T - cnd[0] >= 5) + (T - cnd[0] >= 10) + (T - cnd[0] >= 16)), repeat=8):
        if (cnd[0], cnd[1] + x[0], cnd[2] + x[1], cnd[3] + x[2], cnd[4] + x[3],
                cnd[5] + x[4], cnd[6] + x[5], cnd[7] + x[6], cnd[8] + x[7]) in dp:
            dp[cnd] = -1
            return -1

    skip = (cnd[0] + 1, cnd[1], cnd[2], cnd[3], cnd[4], cnd[5] + cnd[1], cnd[6] + cnd[2], cnd[7] + cnd[3], cnd[8] + cnd[4])
    value = -1

    if cnd[5] >= bp[0] and cnd[0] + 3 < T:
        value = max(value,
                    solve_blueprint(
                        (skip[0], skip[1] + 1, skip[2], skip[3], skip[4], skip[5] - bp[0], skip[6], skip[7], skip[8]),
                        bp))

    if cnd[5] >= bp[1] and cnd[0] + 3 < T:
        value = max(value,
                    solve_blueprint(
                        (skip[0], skip[1], skip[2] + 1, skip[3], skip[4], skip[5] - bp[1], skip[6], skip[7], skip[8]),
                        bp))

    if cnd[5] >= bp[2] and cnd[6] >= bp[3] and cnd[0] + 3 < T:
        value = max(value,
                    solve_blueprint(
                        (skip[0], skip[1], skip[2], skip[3] + 1, skip[4], skip[5] - bp[2], skip[6] - bp[3], skip[7], skip[8]),
                        bp))

    if cnd[5] >= bp[4] and cnd[7] >= bp[5] and cnd[0] + 1 < T:
        value = max(value,
                    solve_blueprint(
                        (skip[0], skip[1], skip[2], skip[3], skip[4] + 1, skip[5] - bp[4], skip[6], skip[7] - bp[5], skip[8]),
                        bp))

    value = max(value, solve_blueprint(skip, bp))

    dp[cnd] = value
    if cnd[0] <= T - 17:
        print(cnd, value)
    return value


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    A = [line for line in input_string.split('\n')]
    # A = [line for line in input_string.split('\n')]
    # A = [list(map(int, line)) for line in input_string.split('\n')]

    N = len(A)
    print("N =", N)

    n = N if LEVEL == 1 or N == 2 else 3

    ans = 0 if LEVEL == 1 else 1
    for i in range(n):
        s = A[i].split()
        bp = tuple(map(int, [s[6], s[12], s[18], s[21], s[27], s[30]]))

        dp.clear()
        value = solve_blueprint(initial, bp)
        print(i, value)
        if LEVEL == 1:
            ans += (i + 1) * value
        else:
            ans *= value

    return ans


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
    assert submit_answer(2022, 19, LEVEL, answer) is True


if __name__ == '__main__':
    main()
