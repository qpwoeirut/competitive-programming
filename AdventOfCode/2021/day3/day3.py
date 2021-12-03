# from itertools import *
# from math import *

ans = 0
ans2 = 0

with open("input.txt") as file:
    A = [line.strip() for line in file]
    # A = [int(line.strip()) for line in file]

N = len(A)
print("N =", N)
print(A[:10])
M = len(A[0])

ct = [0 for _ in range(M)]
for i in range(N):
    for j, c in enumerate(A[i]):
        if c == '1':
            ct[j] += 1
        else:
            ct[j] -= 1

eps = 0
gam = 0
for j in range(M):
    eps <<= 1
    gam <<= 1
    if ct[j] < 0:
        eps += 1
    elif ct[j] > 0:
        gam += 1
    else:
        assert False


oxy = ""
co2 = ""
for j in range(M):
    if len([x for x in A if x.startswith(oxy)]) == 1:
        oxy = [x for x in A if x.startswith(oxy)][0]
        break
    ct2 = 0
    for a in A:
        if not a.startswith(oxy):
            continue
        if a[j] == '1':
            ct2 += 1
        else:
            ct2 -= 1
    if ct2 >= 0:
        oxy += '1'
    else:
        oxy += '0'

for j in range(M):
    if len([x for x in A if x.startswith(co2)]) == 1:
        co2 = [x for x in A if x.startswith(co2)][0]
        break
    ct2 = 0
    for a in A:
        if not a.startswith(co2):
            continue
        if a[j] == '1':
            ct2 += 1
        else:
            ct2 -= 1
    if ct2 < 0:
        co2 += '1'
    else:
        co2 += '0'



print(eps, gam)
ans = eps * gam

ans2 = int(co2,2 ) * int(oxy,2)
print(int(co2, 2), int(oxy, 2))
print(co2)
print("ans1:", ans)
print("ans2:", ans2)
