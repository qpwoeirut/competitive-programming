# from collections import *
# from itertools import *
# from math import *

ans = 0
ans2 = 0

#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]

with open("input.txt") as file:
    # A = list(map(int, file.readline().split(',')))
    A = [int(line.strip()) for line in file]
    # A = [line.strip() for line in file]
    # A = [list(map(int, line.strip())) for line in file]

N = len(A)
print("N =", N)
print(A[:10])
# M = len(A[0])

# for i in range(N):


# for i in range(N):


print("ans1:", ans)
print("ans2:", ans2)