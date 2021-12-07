# from itertools import *
# from math import *

ans = 0
ans2 = 0

with open("input.txt") as file:
    # A = [line.strip() for line in file]
    # A = [int(line.strip()) for line in file]
    A = list(map(int, file.readline().split(',')))

N = len(A)
print("N =", N)
print(A[:10])
# M = len(A[0])

A.sort()

med = A[N//2]
for i in range(N):
    ans += abs(A[i] - med)

ans2 = 1e100
for mid in range(min(A), max(A) + 1):
# mid = round(sum(A) / N)
    cur = 0
    for i in range(N):
        n = abs(A[i] - mid)
        cur += n * (n + 1) // 2
    ans2 = min(ans2, cur)

print("ans1:", ans)
print("ans2:", ans2)
