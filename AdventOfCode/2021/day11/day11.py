# from collections import *
# from itertools import *
# from math import *

ans = 0
ans2 = 0

with open("input.txt") as file:
    # A = list(map(int, file.readline().split(',')))
    # A = [int(line.strip()) for line in file]
    # A = [line.strip() for line in file]
    A = [list(map(int, line.strip())) for line in file]

N = len(A)
print("N =", N)
print(A[:10])
M = len(A[0])

step = 0
while step < 1e100:
    flashed = [[False for _ in range(M)] for _ in range(N)]
    change = True

    while change:
        change = False
        for r in range(N):
            for c in range(M):
                if A[r][c] >= 9 and not flashed[r][c]:
                    flashed[r][c] = True
                    if 0 < r and 0 < c:
                        A[r-1][c-1] += 1
                    if 0 < r:
                        A[r-1][c] += 1
                    if 0 < r and c+1 < M:
                        A[r-1][c+1] += 1
                    if 0 < c:
                        A[r][c-1] += 1
                    if c+1 < M:
                        A[r][c+1] += 1
                    if r+1 < N and 0 < c:
                        A[r+1][c-1] += 1
                    if r+1 < N:
                        A[r+1][c] += 1
                    if r+1 < N and c + 1 < M:
                        A[r+1][c+1] += 1
                    change = True
    ans += sum([r.count(True) for r in flashed])
    for r in range(N):
        for c in range(M):
            if flashed[r][c]:
                A[r][c] = 0
            else:
                A[r][c] += 1
    for r in A:
        print(r)
    print()
    step += 1
    if sum([r.count(True) for r in flashed]) == N*M:
        ans2 = step
        break

# for i in range(N):


print("ans1:", ans)
print("ans2:", ans2)
