# from math import *
# from itertools import *
# from math import *

ans = 0
ans2 = 0

A = [int(x) for x in "614752839"] + [x for x in range(10, 1000000+1)]

N = len(A)
print("N =", N)
# print(A[:10])

# M = len(A[0])

cur = 0
for i in range(10000000):
    r = []
    for j in range(3):
        r.append(A.pop(1))

    dest = A[cur] - 1
    while dest in r:
        dest = dest - 1
        if dest < 1:
            dest = max(A)

    dest = A.index(dest)
    for x in reversed(r):
        A.insert(dest+1, x)

    A = A[1:] + [A[0]]

# A += A
# ans = ''.join([str(x) for x in A[A.index(1) + 1:]])
# ans = ans[:N-1]

ans2 = A[A.index(1) + 1] * A[A.index(1) + 2]

print("ans1:", ans)
print("ans2:", ans2)
