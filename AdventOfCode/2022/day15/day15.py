# from collections import *
# from itertools import *
# from math import *
from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [26, 56000011]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    A = [line for line in input_string.split('\n')]
    # A = [line for line in input_string.split('\n')]
    # A = [list(map(int, line)) for line in input_string.split('\n')]

    N = len(A)
    print("N =", N)
    # M = len(A[0])

    sensors = dict()

    dists = []
    bound_sx = [1e9, -1e9]
    for i in range(N):
        sensor, beacon = A[i].split(": ")
        sx, sy = map(lambda s: int(s.split('=')[1].strip(',')), sensor.split()[2:])
        bx, by = map(lambda s: int(s.split('=')[1].strip(',')), beacon.split()[4:])
        sensors[(sx, sy)] = (bx, by)
        dists.append(abs(sx - bx) + abs(sy - by))

        bound_sx[0] = min(bound_sx[0], sx)
        bound_sx[1] = max(bound_sx[1], sx)
    dists.sort()
    print(dists)

    ans = 0
    y = 2000000 if N != 14 else 10
    for x in range(bound_sx[0] - max(dists), bound_sx[1] + max(dists)):
        ok = False
        for sensor, beacon in sensors.items():
            sb_dist = abs(sensor[0] - beacon[0]) + abs(sensor[1] - beacon[1])
            dist = abs(sensor[0] - x) + abs(sensor[1] - y)
            if dist <= sb_dist:
                ok = True
                break
        if ok and (x, y) not in sensors.values():
            ans += 1

    # for i in range(N):

    if LEVEL == 1:
        return ans
    else:
        MAX = 4000000 if N != 14 else 20
        for y in range(MAX + 1):
            x = 0
            while x < MAX:
                for sensor, beacon in sensors.items():
                    sb_dist = abs(sensor[0] - beacon[0]) + abs(sensor[1] - beacon[1])
                    # sb_dist = |sensor[0] - x| + |sensor[1] - y|
                    # |sensor[0] - x| = sb_dist - |sensor[1] - y|
                    x1 = sensor[0] - (sb_dist - abs(sensor[1] - y))
                    x2 = sensor[0] + (sb_dist - abs(sensor[1] - y))
                    if x1 <= x <= x2:
                        x = x2 + 1
                        break
                else:
                    return x * 4000000 + y


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
    assert submit_answer(2022, 15, LEVEL, answer) is True


if __name__ == '__main__':
    main()
