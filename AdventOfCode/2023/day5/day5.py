# from collections import *
# from itertools import *
# from math import *
from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [35, 46]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]



def read_list(A: list):
    while not A[0] or not A[0][0].isdigit():
        A = A[1:]
    # print(A)

    mapping = []
    while A and A[0]:
        dest, src, n = map(int, A[0].split())
        mapping.append((dest, src, n))
        A = A[1:]
    return mapping, A


def convert(val, mapping: list) -> list:
    if isinstance(val, tuple):
        assert len(val) == 2
        assert val[0] <= val[1]
        assert 0 <= val[0]
        ranges = []
        for dest, src, n in mapping:
            if val[0] == val[1]:
                return ranges
            if src <= val[0] < src + n and src < val[1] <= src + n:
                ranges.append((dest + val[0] - src, dest + val[1] - src))
                return ranges
            elif src <= val[0] < src + n:
                ranges.append((dest + val[0] - src, dest + n))
                val = (src + n, val[1])
            elif src < val[1] <= src + n:
                ranges.append((dest, dest + val[1] - src))
                val = (val[0], src)
            elif val[0] <= src and src + n <= val[1]:
                return ranges + [(dest, dest + n), *convert((val[0], src), mapping), *convert((src + n, val[1]), mapping)]
        return ranges + [val]

    for dest, src, n in mapping:
        if src <= val < src + n:
            return [dest + (val - src)]
    return [val]


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    A = [line for line in input_string.split('\n')]
    # A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line)) for line in input_string.split('\n')]

    N = len(A)
    print("N =", N)
    # print(A[:10])
    # M = len(A[0])

    ans1 = 0
    ans2 = 0
    # for i in range(N):

    seeds = list(map(int, A[0].split(': ')[1].split()))

    s2s, A = read_list(A)
    s2f, A = read_list(A)
    f2w, A = read_list(A)
    w2l, A = read_list(A)
    l2t, A = read_list(A)
    t2h, A = read_list(A)
    h2l, A = read_list(A)

    if LEVEL == 2:
        seeds = [(seeds[i], seeds[i] + seeds[i + 1]) for i in range(0, len(seeds), 2)]
    print(seeds)

    soil  = [y for x in seeds for y in convert(x, s2s)]
    print("soil", soil)
    fert  = [y for x in soil for y in convert(x, s2f)]
    print("f", fert)
    water = [y for x in fert for y in convert(x, f2w)]
    print("water", water)
    light = [y for x in water for y in convert(x, w2l)]
    light.sort()
    print("light", light)
    temp  = [y for x in light for y in convert(x, l2t)]
    temp.sort()
    print("temp", temp)
    hum   = [y for x in temp for y in convert(x, t2h)]
    print("hum", hum)
    loc   = [y for x in hum for y in convert(x, h2l)]
    loc.sort()
    print("loc", loc)
    # for i in range(N):

    assert min(loc)[0] > 0
    if LEVEL == 1:
        return min(loc)
    else:
        return min(loc)[0]


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
    assert submit_answer(2023, 5, LEVEL, answer) is True


if __name__ == '__main__':
    main()
