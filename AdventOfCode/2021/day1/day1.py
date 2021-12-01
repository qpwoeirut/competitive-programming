# from itertools import *
# from math import *

ans = 0
ans2 = 0

with open("input.txt") as file:
    # A = [line.strip() for line in file]
    A = [int(line.strip()) for line in file]

N = len(A)
print("N =", N)
print(A[:10])
# M = len(A[0])

for i in range(1,N):
    if A[i-1] < A[i]:
        ans += 1

for i in range(3, N):
    if A[i-3] < A[i]:
        ans2 += 1

print("ans1:", ans)
print("ans2:", ans2)
