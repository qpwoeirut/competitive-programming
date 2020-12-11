# from math import *


ans = 0
ans2 = 0

with open("input.txt") as file:
    # A = [line.strip() for line in file]
    A = [int(line.strip()) for line in file]
print("N =", len(A))
print(A[:10])

A.append(0)
A.sort()
ct = [0,0,0,0]
for i in range(1,len(A)):
    ct[A[i] - A[i-1]] += 1

print(ct)
ct[3] += 1
ans = ct[1] * ct[3]
print("ans1:", ans)
print("ans2:", ans2)

A.append(A[-1] + 3)

dp = [0 for _ in A]
dp[0] = 1
for i in range(1, len(A)):
    for j in range(1, 4):
        if A[i] <= A[i-j] + 3:
            dp[i] += dp[i-j]
print(dp[-1])