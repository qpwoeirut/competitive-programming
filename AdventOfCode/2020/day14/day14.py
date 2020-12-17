# from math import *
from itertools import combinations

ans = 0
ans2 = 0

with open("input.txt") as file:
    A = [line.strip() for line in file]
    # A = [int(line.strip()) for line in file]

N = len(A)
print("N =", N)
print(A[:10])
# M = len(A[0])

mask = ""
def gen(v):
    f = []
    for i in range(len(mask)):
        if mask[i] == '1':
            v |= (1 << i)
        elif mask[i] == 'X':
            f.append(i)
            v |= (1 << i)
            v -= (1 << i)
    ret =[]
    for L in range(len(f) + 1):
        for c in combinations(f, L):
            x = v
            for a in c:
                x += (1 << a)
            ret.append(x)
    ret.sort()
    print(ret)
    return ret


mem = dict()
x, y = 0, 0
for i in range(0, N):
    k, _, v = A[i].split()
    if k.startswith("mask"):
        mask = v[::-1]
    else:
        x = int(k.strip("mem[").strip(']'))
        v = int(v)
        # for i in range(len(mask)):
        #     if mask[i] == '1':
        #         v |= (1 << i)
        #     elif mask[i] == '0':
        #         v |= (1 << i)
        #         v -= (1 << i)
        for addr in gen(x):
            mem[addr] = v

print(mem)
ans = sum(mem.values())


print("ans1:", ans)
print("ans2:", ans2)