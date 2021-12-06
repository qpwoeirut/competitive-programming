# from itertools import *
# from math import *

ans = 0
ans2 = 0

with open("input.txt") as file:
    # A = [line.strip() for line in file]
    # A = [int(line.strip()) for line in file]
    A = list(map(int, file.readline().split(',')))
    # A = list(map(int, "3,4,3,1,2".split(',')))

ct = [A.count(i) for i in range(10)]

N = len(A)
print("N =", N)
print(A[:10])
# M = len(A[0])

for _ in range(256):
    print(_, sum(ct))
    print("ct", ct)
    ct[9] += ct[0]
    ct[7] += ct[0]
    for i in range(1, 10):
        ct[i-1] = ct[i]
        ct[i] = 0
    if _ == 79:
        ans = sum(ct)
ans2 = sum(ct)

# for i in range(N):


print("ans1:", ans)
print("ans2:", ans2)
