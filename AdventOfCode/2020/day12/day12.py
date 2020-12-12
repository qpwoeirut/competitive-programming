# from math import *


ans = 0
ans2 = 0

with open("input.txt") as file:
    # A = [line.strip() for line in file]
    A = [int(line.strip()) for line in file]
print("N =", len(A))
print(A[:10])
N = len(A)
# M = len(A[0])





for i in range(0, N):
    x = A[i]



print("ans1:", ans)
print("ans2:", ans2)