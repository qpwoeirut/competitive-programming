# from itertools import *
# from math import *

ans = 0
ans2 = 0

with open("input.txt") as file:
    # A = [line.strip() for line in file]
    A = [int(line.strip()) for line in file]
    # A = list(map(int, file.readline().split(',')))

N = len(A)
print("N =", N)
print(A[:10])
# M = len(A[0])

# for i in range(N):


# for i in range(N):


print("ans1:", ans)
print("ans2:", ans2)
