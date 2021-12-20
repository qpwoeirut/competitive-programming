# from collections import *
from itertools import *

# from math import *
from copy import deepcopy

ans = 0
ans2 = 0

#      N   E   S   W
chr = [-1, 0, 1, 0, -1, -1, 1, 1]
chc = [0, 1, 0, -1, -1, 1, -1, 1]

A = [[] for _ in range(26)]
# A = [[] for _ in range(5)]
i = 0
with open("input.txt") as file:
    for line in file:
        line = line.strip()
        if len(line) == 0:
            continue
        if 'scanner' in line:
            i = int(line.split()[2])
        else:
            A[i].append(list(map(int, line.split(','))))
    # A = list(map(int, file.readline().split(',')))
    # A = [int(line.strip()) for line in file]
    # A = [line.strip() for line in file]
    # A = [list(map(int, line.strip())) for line in file]

N = len(A)
print("N =", N)
print(A[:10])


# M = len(A[0])

# for i in range(N):


def add_pt(pt1, pt2):
    return [pt1[i] + pt2[i] for i in range(3)]


def sub_pt(pt1, pt2):
    return [pt1[i] - pt2[i] for i in range(3)]


def matches(set1: set, list1, list2) -> list or None:
    # print("list1:", list1)
    # print("list2:", list2)
    for pt1 in list1:
        for pt2 in list2:
            pt = sub_pt(pt1, pt2)
            set2 = {str(add_pt(p, pt)) for p in list2}
            if len(set1.intersection(set2)) >= 12:
                return pt
    return None


B = [[] for _ in A]
B[0] = deepcopy(A[0])
stack = [0]
scanners = [[0, 0, 0]]
while stack:
    cur = stack[-1]
    stack.pop()

    cur_set = {str(x) for x in B[cur]}

    for i in range(N):
        if B[i]:
            continue

        print(i)
        for flip_mask in range(8):
            for perm in permutations([0, 1, 2]):
                # print(flip_mask, perm)
                transformed = [
                    [A[i][j][perm[k]] if ((flip_mask >> k) & 1) == 0 else -A[i][j][perm[k]] for k in range(3)]
                    for j in range(len(A[i]))]
                pt = matches(cur_set, B[cur], transformed)
                if pt:
                    scanners.append(pt)
                    transformed = [add_pt(pt, p) for p in transformed]
                    B[i] = deepcopy(transformed)
                    stack.append(i)
                    transformed.sort()
                    break
            if stack and stack[-1] == i:
                break

points = set()
tmp = []
for x in B:
    for p in x:
        points.add(str(p))
        tmp.append(p)
tmp.sort()
for x in tmp:
    print(x)

ans = len(points)

for scanner in scanners:
    for other_scanner in scanners:
        ans2 = max(ans2, sum([abs(x) for x in sub_pt(scanner, other_scanner)]))

print("ans1:", ans)
print("ans2:", ans2)
