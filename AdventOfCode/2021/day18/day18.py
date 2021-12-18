# from collections import *
# from itertools import *
# from math import *
from ast import literal_eval
from copy import deepcopy

ans = 0
ans2 = 0

#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]

with open("input.txt") as file:
    # A = list(map(int, file.readline().split(',')))
    # A = [int(line.strip()) for line in file]
    A = [literal_eval(line.strip()) for line in file]
    # A = [list(map(int, line.strip())) for line in file]

N = len(A)
print("N =", N)
print(A[:10])


def add_nested(target, side, val):
    # print(target, side, val)
    if isinstance(target[side ^ 1], int):
        target[side ^ 1] += val
    else:
        target = target[side ^ 1]
        while isinstance(target[side], list):
            target = target[side]
        target[side] += val
    # print(num)


def dfs_explode(cur, idx, depth):
    if isinstance(cur[idx], int):
        # print(depth, idx, cur, [0, 0])
        return [0, 0]

    if depth == 4:
        tmp = cur[idx].copy()
        cur[idx] = 0
        global change
        change = True
        assert len(tmp) == 2
        # print(depth, idx, cur, tmp)
        return tmp

    x = dfs_explode(cur[idx], 0, depth + 1).copy()
    if x[1] > 0:
        add_nested(cur[idx], 0, x[1])

    y = dfs_explode(cur[idx], 1, depth + 1).copy()
    if y[0] > 0:
        add_nested(cur[idx], 1, y[0])

    # print(depth, idx, cur, [x[0], y[1]])
    return [x[0], y[1]]


def dfs_split(cur, idx):
    global change
    if change:
        return
    if isinstance(cur[idx], int):
        if cur[idx] >= 10:
            cur[idx] = [cur[idx] // 2, (cur[idx] + 1) // 2]
            change = True
        return
    dfs_split(cur[idx], 0)
    if change:
        return
    dfs_split(cur[idx], 1)


def magnitude(cur):
    if isinstance(cur, int):
        return cur
    return 3 * magnitude(cur[0]) + 2 * magnitude(cur[1])


num = deepcopy(A[0])
for i in range(1, N):
    print(A[:10])
    num = [deepcopy(num), deepcopy(A[i])]
    change = True
    while change:
        change = False
        right = dfs_explode(num, 0, 1)[1]
        add_nested(num, 0, right)

        left = dfs_explode(num, 1, 1)[0]
        add_nested(num, 1, left)

        if not change:
            dfs_split(num, 0)
        if not change:
            dfs_split(num, 1)
        # print(num)

ans = magnitude(num)


print(A[:10])
for i in range(N):
    for j in range(N):
        if i == j:
            continue
        num = [deepcopy(A[i]), deepcopy(A[j])]
        change = True
        while change:
            change = False
            right = dfs_explode(num, 0, 1)[1]
            add_nested(num, 0, right)

            left = dfs_explode(num, 1, 1)[0]
            add_nested(num, 1, left)

            if not change:
                dfs_split(num, 0)
            if not change:
                dfs_split(num, 1)
        ans2 = max(ans2, magnitude(num))

print(A[:10])
print("ans1:", ans)
print("ans2:", ans2)
