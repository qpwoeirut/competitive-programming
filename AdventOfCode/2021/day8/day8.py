from itertools import *
# from math import *

ans = 0
ans2 = 0

with open("input.txt") as file:
    A = [line.strip().split(' | ') for line in file]
    # A = [int(line.strip()) for line in file]
    # A = list(map(int, file.readline().split(',')))

N = len(A)
print("N =", N)
print(A[:10])
# M = len(A[0])

ct = [0 for _ in range(10)]
for i in range(N):
    a = A[i][1]
    for x in a.split():
        ct[len(x)] += 1

nums = [
    "abcefg",
    "cf",
    "acdeg",
    "acdfg",
    "bcdf",
    "abdfg",
    "abdefg",
    "acf",
    "abcdefg",
    "abcdfg"
]
valid = set([num.upper() for num in nums])


def ok(s: str, t: str, p: tuple) -> int:
    for a, b in zip("abcdefg", p):
        s = s.replace(a, b)
        t = t.replace(a, b)

    s = ' '.join([''.join(sorted(x)) for x in s.split()])
    t = ' '.join([''.join(sorted(x)) for x in t.split()])
    # print(s, t, p)

    for n in s.split():
        if n not in valid:
            return -1
    sm = 0
    for n in t.split():
        if n not in valid:
            return -1
        sm *= 10
        sm += nums.index(n.lower())
    return sm


for i in range(N):
    done = False
    for perm in permutations("abcdefg".upper()):
        val = ok(A[i][0], A[i][1], perm)
        if val >= 0:
            # print(perm)
            assert done is False
            ans2 += val
            done = True
    assert done is True
    # break


ans = ct[2] + ct[3] + ct[4] + ct[7]
print("ans1:", ans)
print("ans2:", ans2)
