# from collections import *
# from itertools import *
# from math import *

ans = 0
ans2 = 0

#      N   E   S   W
chr = [-1, 0, 1, 0, -1, -1, 1, 1]
chc = [0, 1, 0, -1, -1, 1, -1, 1]

with open("input.txt") as file:
    # A = list(map(int, file.readline().split(',')))
    # A = [int(line.strip()) for line in file]
    A = [line.strip().split('-') for line in file]
    # A = [list(map(int, line.strip())) for line in file]

N = len(A)
print("N =", N)
print(A[:10])
# M = len(A[0])

adj = dict()
for a, b in A:
    if a not in adj:
        adj[a] = []
    adj[a].append(b)

    if b not in adj:
        adj[b] = []
    adj[b].append(a)

visited = {"start"}

path = ["start"]


def dfs(u: str, doubled: bool):
    if u == "end":
        # print(path)
        return 1
    ret = 0
    for v in adj[u]:
        if v.isupper() or v not in visited:
            if v.islower():
                visited.add(v)
            # path.append(v)
            ret += dfs(v, doubled)
            # path.pop()
            if v.islower():
                visited.remove(v)
        elif not doubled and v != "start" and v in visited:
            # path.append(v)
            ret += dfs(v, True)
            # path.pop()
    return ret


# for i in range(N):


# for i in range(N):

ans = dfs("start", True)
ans2 = dfs("start", False)
print("ans1:", ans)
print("ans2:", ans2)
