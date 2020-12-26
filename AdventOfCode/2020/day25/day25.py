# from math import *
# from itertools import *
# from math import *

ans = 0
ans2 = 0

with open("input.txt") as file:
    # A = [line.strip() for line in file]
    A = [int(line.strip()) for line in file]

# N = len(A)
# print("N =", N)
print(A[:10])
# M = len(A[0])

mod = 20201227
sub = 7
x, y = A
ex = 7731677
ans = pow(y, ex, mod)


print("ans1:", ans)
print("ans2:", ans2)
