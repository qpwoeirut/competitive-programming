# from math import *


ans = 0
ans2 = 0

with open("input.txt") as file:
    A = [line.strip() for line in file]
    # A = [int(line.strip()) for line in file]
print("N =", int(A[0]))
print(A[:10])
N = int(A[0])
# M = len(A[0])

A = A[1].split(',')
x, y = 0, 0

earliest = (1e100, 0)
for i in range(0, len(A)):
    a = A[i]
    if a == 'x':
        continue
    a = int(a)
    earliest = min(earliest, (N + a - (N % a), a))

ans = ( earliest[0] - N)* earliest[1]

from functools import reduce


def chinese_remainder(n, a):
    sum = 0
    prod = reduce(lambda a, b: a * b, n)
    for n_i, a_i in zip(n, a):
        p = prod // n_i
        sum += a_i * mul_inv(p, n_i) * p
    return sum % prod


def mul_inv(a, b):
    b0 = b
    x0, x1 = 0, 1
    if b == 1: return 1
    while a > 1:
        q = a // b
        a, b = b, a % b
        x0, x1 = x1 - q * x0, x0
    if x1 < 0: x1 += b0
    return x1

# A = "17,x,13,19".split(',')
x = []
m = []
for i in range(len(A)):
    if A[i] == 'x':
        continue
    x.append((int(A[i]) - i) % (int(A[i])))
    m.append(int(A[i]))

ans2 = chinese_remainder(m, x)

print("ans1:", ans)
print("ans2:", ans2)