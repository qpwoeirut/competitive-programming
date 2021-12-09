# from itertools import *
# from math import *
from collections import deque

ans = 0
ans2 = 0

with open("input.txt") as file:
    A = [list(map(int, line.strip())) for line in file]
    # A = [int(line.strip()) for line in file]
    # A = list(map(int, file.readline().split(',')))

N = len(A)
print("N =", N)
print(A[:10])
M = len(A[0])

low = []
for i in range(N):
    for j in range(M):
        ok = True

        if i > 0 and A[i - 1][j] <= A[i][j]:
            ok = False
        if j > 0 and A[i][j - 1] <= A[i][j]:
            ok = False
        if i + 1 < N and A[i + 1][j] <= A[i][j]:
            ok = False
        if j + 1 < M and A[i][j + 1] <= A[i][j]:
            ok = False
        if ok:
            ans += 1 + A[i][j]
            low.append((i, j))


def fill(sr, sc):
    V = [[False for _ in r] for r in A]
    d = deque()
    d.append((sr, sc))
    while d:
        r, c = d.popleft()
        V[r][c] = True
        for (dr, dc) in zip([1, 0, -1, 0], [0, 1, 0, -1]):
            rr = dr + r
            cc = dc + c
            if 0 <= rr < N and 0 <= cc < M and A[rr][cc] != 9 and V[rr][cc] is False:
                V[rr][cc] = True
                d.append((rr, cc))
    return sum([row.count(True) for row in V])


sizes = [fill(*t) for t in low]
sizes.sort(reverse=True)
ans2 = sizes[0] * sizes[1] * sizes[2]
print(sizes)

# for i in range(N):


print("ans1:", ans)
print("ans2:", ans2)
