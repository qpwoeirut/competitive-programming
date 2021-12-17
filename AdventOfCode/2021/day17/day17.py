# from collections import *
# from itertools import *
# from math import *

ans = 0
ans2 = 0

#      N   E   S   W
chr = [-1, 0, 1, 0, -1, -1, 1, 1]
chc = [0, 1, 0, -1, -1, 1, -1, 1]

# with open("input.txt") as file:
#     # A = list(map(int, file.readline().split(',')))
#     A = [int(line.strip()) for line in file]
#     # A = [line.strip() for line in file]
#     # A = [list(map(int, line.strip())) for line in file]
#
# N = len(A)
# print("N =", N)
# print(A[:10])
# M = len(A[0])

x_range = (287, 310)  # missed out on top 10 for part 2 because I copied the input wrong >:(
y_range = (-76, -47)


# x_range = (20, 31)
# y_range = (-10, -4)

def check(vx, vy):
    x, y = 0, 0
    hi = -10 ** 9
    while (vy < 0 and y >= y_range[0]) or vy >= 0:
        x += vx
        y += vy
        if vx > 0:
            vx -= 1
        elif vx < 0:
            vx += 1
        vy -= 1

        hi = max(hi, y)
        if x_range[0] <= x < x_range[1] and y_range[0] <= y < y_range[1]:
            return hi

    return None


ans = -10 ** 9
for i in range(350):
    for j in range(-80, 1000):
        cur = check(i, j)
        if cur is not None:
            ans2 += 1
            print(i, j)
            ans = max(ans, cur)

# for i in range(N):


print("ans1:", ans)
print("ans2:", ans2)
