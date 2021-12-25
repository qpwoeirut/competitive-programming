# from collections import *
# from itertools import *
# from math import *
from copy import deepcopy

ans = 0
ans2 = 0

#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]

with open("input.txt") as file:
    # A = list(map(int, file.readline().split(',')))
    # A = [int(line.strip()) for line in file]
    A = [line.strip() for line in file]
    # A = [list(map(int, line.strip())) for line in file]

N = len(A)
print("N =", N)
print(A[:10])
M = len(A[0])

# for i in range(N):

dir = {
    '>': 1,
    'v': 2,
}

for step in range(1000):
    print(step)
    print('\n'.join([''.join(r) for r in A]))
    print()
    change = False
    for x in ">v":
        new = [['.' for _ in range(M)] for _ in range(N)]
        for r in range(N):
            for c in range(M):
                if A[r][c] == '.':
                    continue
                new[r][c] = A[r][c]
                if A[r][c] != x:
                    continue
                nr = (r + chr[dir[x]]) % N
                nc = (c + chc[dir[x]]) % M
                if A[nr][nc] == '.':
                    new[nr][nc] = x
                    new[r][c] = '.'
                    change = True
        A = deepcopy(new)

    if not change:
        ans = step + 1
        break

print("ans1:", ans)
print("ans2:", ans2)
