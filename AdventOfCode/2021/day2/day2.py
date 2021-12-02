# from itertools import *
# from math import *

ans = 0
ans2 = 0

with open("input.txt") as file:
    A = [line.strip().split() for line in file]
    # A = [int(line.strip()) for line in file]

N = len(A)
print("N =", N)
print(A[:10])
# M = len(A[0])

h = 0
d = 0
for i in range(N):
    if A[i][0].startswith('f'):
        h += int(A[i][1])
    elif A[i][0].startswith('d'):
        d += int(A[i][1])
    else:
        d -= int(A[i][1])
ans = h * d

h = 0
d = 0
a = 0
for i in range(N):
    if A[i][0].startswith('f'):
        h += int(A[i][1])
        d += a * int(A[i][1])
    elif A[i][0].startswith('d'):
        a += int(A[i][1])
    else:
        a -= int(A[i][1])

ans2 = h * d

print("ans1:", ans)
print("ans2:", ans2)
