# from math import *


ans = 0
ans2 = 0

with open("input.txt") as file:
    A = [line.strip() for line in file]

def test(skip):
    n = 0
    i = 0
    seen = set()
    while i < len(A):
        if i in seen:
            return False
        seen.add(i)
        x = A[i].split()
        if x[0] == 'acc':
            n += int(x[1])
        elif (x[0] == 'jmp' and skip != i) or (x[0] == 'nop' and skip == i):
            i += int(x[1])
            continue
        i += 1
    return n


for i in range(len(A)):
    ans = test(i)
    if ans is not False:
        break
print("ans1:", ans)
print("ans2:", ans2)
