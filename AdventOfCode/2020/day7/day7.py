# from math import *


ans = 0
ans2 = 0

adj = dict()
radj = dict()

with open("input.txt") as file:
    A = [line.strip() for line in file]

for x in A:
    x = x.split()
    name = x[0] + x[1]
    x = x[4:]
    adj[name] = []
    if x[0] == "no":
        continue
    for i in range(0, len(x), 4):
        adj[name].append((int(x[i]), x[i+1] + x[i+2]))
        assert x[i+3].startswith('bag'), x[i+3]

for k, v in adj.items():
    radj[k] = []
    for x in v:
        radj[x[1]] = []

for k, v in adj.items():
    for x in v:
        radj[x[1]].append(k)

seen = set()

def dfs(cur):
    if cur in seen:
        return
    seen.add(cur)
    for x in radj[cur]:
        dfs(x)

dfs("shinygold")

def dfs2(cur):
    ret = 0
    for a in adj[cur]:
        ret += dfs2(a[1]) * a[0]
        ret += a[0]
    return ret
print("ans1:", len(seen))
print("ans2:", dfs2("shinygold"))
