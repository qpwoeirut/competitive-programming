N = int(input())
adj = [[] for _ in range(N)]

for _ in range(N - 1):
    u, v = map(int, input().split())
    u -= 1
    v -= 1

    adj[u].append(v)
    adj[v].append(u)

def centrality(root):
    xp = []
    def dfs(u, par, val):
        val *= len(adj[u])
        xp.append(1 / val)
        for v in adj[u]:
            if v != par:
                dfs(v, u, val)

    for u in adj[root]:
        dfs(u, root, 1)

    return 1 + sum(xp)


vals = [centrality(u) for u in range(N)]
print(sum(vals) / N)

