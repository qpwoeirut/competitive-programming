# from math import *


ans = 0
ans2 = 0

with open("input.txt") as file:
    A = [line.strip() for line in file]
    # A = [int(line.strip()) for line in file]
print("N =", len(A))
print(A[:20])

for i in range(0, len(A)):


print("ans1:", ans)
print("ans2:", ans2)