# why am i doing algos in python hlep

from sys import setrecursionlimit

N, M = [int(x) for x in input().split(' ')]
hd = {}
occ = {}
vis = set()
sparse = [[]]
for i in range(N-1):
    u, v = [int(x) for x in input().split(' ')]
    if not u in hd:
        hd[u] = []
    if not v in hd:
        hd[v] = []
    hd[u].append(v)
    hd[v].append(u)

def dfs(cur, pre, dep):
    # print(cur, pre, dep)
    if cur in vis: return;
    vis.add(cur)
    occ[cur] = len(sparse[0])
    sparse[0].append((dep, cur))
    if cur in hd:
        for nxt in hd[cur]:
            if nxt is not pre:
                dfs(nxt, cur, dep+1)
                sparse[0].append((dep, cur))
dfs(1, 0, 1)


for lay in range(0,20):
    # print(sparse[-1])
    sparse.append([])
    # print('lay', lay)
    for i in range(0, len(sparse[-2])-(2**(lay))):
        # print(i, int(i+2**(lay-1)), sparse[-2][i], sparse[-2][int(i+2**(lay-1))], "            ", min(sparse[-2][i], sparse[-2][int(i+2**(lay-1))]), sparse[-1][-1])
        # print('    ', i, i+2**lay)
        sparse[-1].append(min(sparse[-2][i], sparse[-2][int(i+2**lay)]))
    # print("\n");

# for num in occ: print(num, occ[num])
# for row in sparse: print(row)

from math import log2
def query(u, v):
    u = occ[u]
    v = occ[v]
    # if u == v: return u
    if u < v: u, v = v, u
    lay = int(log2(u-v+1))
    return min(sparse[lay][v], sparse[lay][u-2**lay+1])[1]


for i in range(M):
    u, v = [int(x) for x in input().split(' ')]
    print(query(u, v))

