# from math import *


ans = 0
ans2 = 0

with open("input.txt") as file:
    A = [int(line.strip()) for line in file]
print("N =", len(A))


for i in range(25, len(A)):
    ok = False
    for j in range(i - 25, i):
        for k in range(j+1, i):
            if A[j] + A[k] == A[i]:
                ok = True
    if not ok:
        ans = A[i]


for i in range(len(A)):
    x = 0
    for j in range(i, len(A)):
        x += A[j]
        if x == ans and i < j:
            ans2 = min(A[i:j+1]) + max(A[i:j+1])

print("ans1:", ans)
print("ans2:", ans2)
