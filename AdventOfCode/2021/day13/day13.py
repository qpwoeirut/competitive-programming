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
    # A = [int(line.strip()) for line in file]
    # A = [line.strip() for line in file]
    A = []
    B = []
    for line in file:
        line = line.strip()
        if not line:
            continue
        if not line.startswith('fold'):
            A.append(list(map(int, line.strip().split(','))))
        else:
            B.append(line.split()[2].split('='))
            B[-1][1] = int(B[-1][1])

N = len(A)
print("N =", N)
print(A[:10])
print(B[:10])
M = len(B)

for fold in B:
    for i in range(N):
        if fold[0] == 'x':
            diff = A[i][0] - fold[1]
            if diff > 0:
                A[i][0] = fold[1] - diff
        if fold[0] == 'y':
            diff = A[i][1] - fold[1]
            if diff > 0:
                A[i][1] = fold[1] - diff
    if ans == 0:
        ans = len(set([str(x) for x in A]))
    # break


# for i in range(N):


G = [['X' if [c, r] in A else '.' for c in range(50)] for r in range(10)]
for r in G:
    print(r)

print("ans1:", ans)
print("ans2:", ans2)
