from collections import *
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
    A = [line.strip() for line in file]
    # A = [list(map(int, line.strip())) for line in file]

N = len(A)
print("N =", N)
print(A[:10])
# M = len(A[0])

state = set()

clist = [[], [], []]

for i in range(N):
    target, A[i] = A[i].split()
    coords = [list(map(int, x[2:].split('..'))) for x in A[i].split(',')]

    for j in range(3):
        coords[j][1] += 1
        clist[j].append((coords[j][0], (i + 1)))
        clist[j].append((coords[j][1], -(i + 1)))
    A[i] = (target, coords)

    x, y, z = [(max(-50, c[0]), min(c[1], 51)) for c in coords]
    for xx in range(x[0], x[1]):
        for yy in range(y[0], y[1]):
            for zz in range(z[0], z[1]):
                if target == "off":
                    if (xx,yy,zz) in state:
                        state.remove((xx,yy,zz))
                else:
                    state.add((xx,yy,zz))


# for i in range(N):

ans = len(state)

for i in range(3):
    print(min(clist[i]), max(clist[i]))


def sweepline_xyz():
    ret = 0
    active = set()
    prev = -10**9
    for x in sorted(clist[0]):
        print("x:", x)
        ret += (x[0] - prev) * sweepline_yz(active)
        prev = x[0]
        if x[1] < 0:
            active.remove(-x[1])
        else:
            active.add(x[1])
    return ret


def sweepline_yz(active):
    ret = 0
    prev = -10**9
    active_yz = set()
    coords = [y for y in clist[1] if abs(y[1]) in active]
    for y in sorted(coords):
        print("y:", y)
        ret += (y[0] - prev) * sweepline_z(active_yz)
        prev = y[0]
        if y[1] < 0:
            active_yz.remove(-y[1])
        else:
            active_yz.add(y[1])
    return ret


def sweepline_z(active):
    ret = 0
    prev = -10**9
    active_z = set()
    coords = [z for z in clist[2] if abs(z[1]) in active]
    for z in sorted(coords):
        print("z:", z)
        if len(active_z) > 0 and A[max(active_z) - 1][0] == "on":
            ret += z[0] - prev
        prev = z[0]
        if z[1] < 0:
            active_z.remove(-z[1])
        else:
            active_z.add(z[1])
    return ret


ans2 = sweepline_xyz()


print("ans1:", ans)
print("ans2:", ans2)
