# from math import *
# from itertools import *

ans = 0
ans2 = 0

A = [8,0,17,4,1,12]
# A = [0,3,6]
N = 30000000
print("N =", N)
print(A[:10])
# M = len(A[0])

last = dict()
x = []
for i in range(0, N):
    if i < len(A):
        x.append(A[i])
    else:
        if x[-1] in last:
            d = i - last[x[-1]]
        else:
            d = 0
        x.append(d)

    if len(x) >= 2:
        last[x[-2]] = i

print(x[:11])
ans = x[N-1]

print("ans1:", ans)
print("ans2:", ans2)