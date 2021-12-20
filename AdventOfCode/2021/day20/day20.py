# from collections import *
# from itertools import *
# from math import *

ans = 0
ans2 = 0

chr = [-1, -1, -1, 0, 0, 0, 1, 1, 1]
chc = [-1, 0, 1, -1, 0, 1, -1, 0, 1]

with open("input.txt") as file:
    # A = list(map(int, file.readline().split(',')))
    # A = [int(line.strip()) for line in file]
    A = [line.strip() for line in file]
    # A = [list(map(int, line.strip())) for line in file]

alg = A[0]
A = A[2:]
N = len(A)
print("N =", N)
print(A[:10])


# M = len(A[0])

# for i in range(N):

def get_cell(inp, r, c, default):
    r -= 2
    c -= 2
    if r < 0 or c < 0 or r >= len(inp) or c >= len(inp[0]):
        return default
    if inp[r][c] == '.':
        return '0'
    else:
        return '1'


def transform(inp, default):
    B = [['.' for _ in range(len(inp[0]) + 4)] for _ in range(len(inp) + 4)]
    for r in range(len(B)):
        for c in range(len(B[r])):
            s = ""
            for dr, dc in zip(chr, chc):
                s += get_cell(inp, r + dr, c + dc, default)
            B[r][c] = alg[int(s, 2)]
    return [''.join(r) for r in B]


# for i in range(N):

out = transform(A, '0')
for row in out:
    print(row)
out = transform(out, '1')
for row in out:
    print(row)
    ans += row.count('#')

for i in range(50):
    A = transform(A, str(i % 2))
for row in A:
    ans2 += row.count('#')

print("ans1:", ans)
print("ans2:", ans2)
