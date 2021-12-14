# from collections import *
from itertools import *

# from math import *

ans = 0
ans2 = 0

#      N   E   S   W
chr = [-1, 0, 1, 0, -1, -1, 1, 1]
chc = [0, 1, 0, -1, -1, 1, -1, 1]

with open("input.txt") as file:
    S = file.readline().strip()
    assert len(file.readline().strip()) == 0
    # A = list(map(int, file.readline().split(',')))
    # A = [int(line.strip()) for line in file]
    A = [line.strip().split(' -> ') for line in file]
    # A = [list(map(int, line.strip())) for line in file]

N = len(A)
print("N =", N)
print(A[:10])
# M = len(A[0])

for x in A:
    x[1] = x[1].lower() + x[0][1]

pairs = {k: v for k, v in A}
print(A)
s = S
for step in range(10):
    T = s[0]
    for i in range(1, len(s)):
        if s[i - 1:i + 1] in pairs:
            T += pairs[s[i - 1:i + 1]]
        else:
            T += s[i:i + 1]
    s = T.upper()
    print(s)

ct = dict()
for c in set(s):
    ct[c] = s.count(c)

# for i in range(N):
print(ct)
ans = max(ct.values()) - min(ct.values())


def merge(ret, d1):
    for k, v in d1.items():
        if k not in ret:
            ret[k] = 0
        ret[k] += v
    return ret


dp = [dict() for _ in range(41)]


def solve(cur_s, step):
    if step == 41:
        return dict()
    if cur_s in dp[step]:
        return dp[step][cur_s]
    ret = dict()
    if cur_s in pairs:
        ins = pairs[cur_s][0].upper()
        ret[ins] = 1
        d1 = solve(cur_s[0] + ins, step + 1).copy()  # python passes references
        d2 = solve(ins + cur_s[1], step + 1).copy()
        ret = merge(ret, merge(d1, d2))

    dp[step][cur_s] = ret.copy()  # python passes references
    return ret


totals = dict()
totals[S[0]] = 1
for i in range(1, len(S)):
    totals = merge(totals, solve(S[i - 1:i + 1], 1))
    if S[i] not in totals:
        totals[S[i]] = 0
    totals[S[i]] += 1
ans2 = max(totals.values()) - min(totals.values())
print(totals, sum(totals.values()))
print("ans1:", ans)
print("ans2:", ans2)
