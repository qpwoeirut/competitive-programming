# from collections import *
from itertools import *

# from math import *

ans = 0
ans2 = 0

#      N   E   S   W
chr = [-1, 0, 1, 0, -1, -1, 1, 1]
chc = [0, 1, 0, -1, -1, 1, -1, 1]

with open("input.txt") as file:
    # A = list(map(int, file.readline().split(',')))
    # A = [int(line.strip()) for line in file]
    A = [line.strip() for line in file]
    # A = [list(map(int, line.strip())) for line in file]

N = len(A)
print("N =", N)
print(A[:10])
# M = len(A[0])

# for i in range(N):


# for i in range(N):


constants = [
    (1, 13, 8),
    (1, 12, 13),
    (1, 12, 8),
    (1, 10, 10),
    (26, -11, 12),
    (26, -13, 1),
    (1, 15, 13),
    (1, 10, 5),
    (26, -2, 10),
    (26, -6, 3),
    (1, 14, 2),
    (26, 0, 2),  #
    (26, -15, 12),  # z = 0 or (x = 0 and 15 < z < 26*26)
    (26, -4, 7)  # (x = 0 and 4 < z < 26)
]
assert len(constants) == 14


def run_prog(digits: list):
    z = 0
    for i in range(14):
        z = run_step(i, digits[i], z)
    return z


def run_step(step, d, z):
    var = constants[step]
    x = (z % 26 + var[1]) != d
    z //= var[0]
    z *= 25 * x + 1
    z += (d + var[2]) * x
    return z


# z -> highest digits
big = [dict() for _ in range(15)]
big[0][0] = 0

# z -> lowest digits
small = [dict() for _ in range(15)]
small[0][0] = 0
for step in range(14):
    print(step, len(big[step]))
    max_z = 26**(14 - step)
    for z0, digits in big[step].items():
        for d in range(1, 10):
            z = run_step(step, d, z0)
            if z >= max_z:
                continue

            if z not in big[step + 1]:
                big[step + 1][z] = digits * 10 + d
            else:
                big[step + 1][z] = max(big[step + 1][z], digits * 10 + d)
    for z0, digits in small[step].items():
        for d in range(1, 10):
            z = run_step(step, d, z0)
            if z >= max_z:
                continue

            if z not in small[step + 1]:
                small[step + 1][z] = digits * 10 + d
            else:
                small[step + 1][z] = min(small[step + 1][z], digits * 10 + d)
ans = big[14][0]
ans2 = small[14][0]

print("ans1:", ans)
print("ans2:", ans2)
