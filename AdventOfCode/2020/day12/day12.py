# from math import *


ans = 0
ans2 = 0

with open("input.txt") as file:
    A = [line.strip() for line in file]
    # A = [int(line.strip()) for line in file]
print("N =", len(A))
print(A[:10])
N = len(A)
# M = len(A[0])

import math

# https://stackoverflow.com/questions/34372480/rotate-point-about-another-point-in-degrees-python
def rotate(origin, point, angle):
    """
    Rotate a point counterclockwise by a given angle around a given origin.

    The angle should be given in radians.
    """
    angle = math.radians(angle)
    ox, oy = origin
    px, py = point

    qx = ox + math.cos(angle) * (px - ox) - math.sin(angle) * (py - oy)
    qy = oy + math.sin(angle) * (px - ox) + math.cos(angle) * (py - oy)
    return qx, qy

ch = [(1, 0), (0, -1), (-1, 0), (0, 1)]
x, y = 0, 0
wx, wy = 10, 1
for i in range(0, N):
    a = A[i]
    if a[0] == 'N':
        wy += int(a[1:])
    elif a[0] == 'E':
        wx += int(a[1:])
    elif a[0] == 'S':
        wy -= int(a[1:])
    elif a[0] == 'W':
        wx -= int(a[1:])
    elif a[0] == 'L':
        deg = int(a[1:])
        wx, wy = rotate((x, y), (wx, wy), deg)
    elif a[0] == 'R':
        deg = 360 - int(a[1:]) % 360
        wx, wy = rotate((x, y), (wx, wy), deg)
    else:
        dx = wx - x
        dy = wy - y
        x += dx * int(a[1:])
        wx += dx * int(a[1:])
        y += dy * int(a[1:])
        wy += dy * int(a[1:])

ans = abs(x) + abs(y)
print(x, y)
print("ans1:", ans)
print("ans2:", ans2)