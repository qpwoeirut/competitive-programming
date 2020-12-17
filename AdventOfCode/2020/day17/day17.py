# from math import *
from itertools import *

# from math import *

ans = 0
ans2 = 0

with open("input.txt") as file:
    A = [line.strip() for line in file]
    # A = [int(line.strip()) for line in file]

N = len(A)
print("N =", N)
print(A[:10])


# M = len(A[0])

def neighbors(i, x, y, z, w):
    adj = list(product([0, 1, -1], repeat=4))
    adj.remove((0, 0, 0, 0))

    ct = 0
    for nb in adj:
        xx = x + nb[0]
        yy = y + nb[1]
        zz = z + nb[2]
        ww = w + nb[3]
        ct += G[i][xx][yy][zz][ww]
    return ct


X = N + 8
G = [[[[[False for _ in range(X + 8)] for _ in range(X + 8)] for _ in range(X + 8)] for _ in range(X + 8)] for _ in
     range(2)]

for i in range(0, N):
    a = A[i]
    for j in range(len(a)):
        G[0][i + 8][j + 8][8][8] = a[j] == '#'

CYCLES = 6

for i in range(CYCLES):
    ni = (i + 1) & 1
    print(i)
    for x in range(1, X + 8 - 1):
        for y in range(1, X + 8 - 1):
            for z in range(1, X + 8 - 1):
                for w in range(1, X + 8 - 1):
                    if G[i & 1][x][y][z][w] is True:
                        G[ni][x][y][z][w] = (2 <= neighbors(i & 1, x, y, z, w) <= 3)
                    else:
                        G[ni][x][y][z][w] = neighbors(i & 1, x, y, z, w) == 3

for x in range(X + 8):
    for y in range(X + 8):
        for z in range(X + 8):
            for w in range(X + 8):
                ans += G[CYCLES & 1][x][y][z][w]

print("ans1:", ans)
print("ans2:", ans2)
