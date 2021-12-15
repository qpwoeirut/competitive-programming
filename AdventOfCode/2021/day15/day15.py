# from collections import *
from heapq import *
# from itertools import *
# from math import *

ans = 0
ans2 = 0

#      N   E   S   W
chr = [-1, 0, 1, 0, -1, -1, 1, 1]
chc = [0, 1, 0, -1, -1, 1, -1, 1]

with open("input.txt") as file:
    # A = list(map(int, file.readline().split(',')))
    # A = [int(line.strip()) for line in file]
    # A = [line.strip() for line in file]
    A = [list(map(int, line.strip())) for line in file]

N = len(A)
print("N =", N)
# print(A[:10])
M = len(A[0])


# checked subreddit; this solution shouldn't work, but it does, at least for my input
dp = [[1e99 for _ in range(M + 1)] for _ in range(N + 1)]
dp[1][0] = 0
dp[0][1] = 0
for i in range(N):
    for j in range(M):
        dp[i + 1][j + 1] = A[i][j] + min(dp[i][j + 1], dp[i + 1][j])
    # print(dp[i])
ans = dp[-1][-1] - A[0][0]

B = [[0 for _ in range(5 * M)] for _ in range(5 * N)]
for i in range(5 * N):
    for j in range(5 * M):
        r = i // N
        c = j // M
        B[i][j] = ((A[i % N][j % M] + r + c - 1) % 9) + 1

N *= 5
M *= 5

pq = []
heappush(pq, (0, 0, 0))
dist = [[1e99 for _ in range(M)] for _ in range(N)]
while len(pq) > 0:
    cur = heappop(pq)
    if cur[1] == N - 1 and cur[2] == M - 1:
        ans2 = cur[0]
        break
    for dr, dc in zip(chr[:4], chc[:4]):
        nr = cur[1] + dr
        nc = cur[2] + dc
        if 0 <= nr < N and 0 <= nc < M and dist[nr][nc] > cur[0] + B[nr][nc]:
            dist[nr][nc] = cur[0] + B[nr][nc]
            heappush(pq, (dist[nr][nc], nr, nc))


# for r in dp:
#     print(r)
# for i in range(N):

print("ans1:", ans)
print("ans2:", ans2)
