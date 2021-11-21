import sys
sys.setrecursionlimit(20005)


def unbeatable(N, A, adj):
    adj = [x - 1 for x in adj]
    dp = [x for x in A]
    vis = [False for _ in range(N)]

    def dfs(u):
        if vis:
            return
        vis[u] = True
        dfs(adj[u])
        dp[u][0] = max(dp[u][0], dp[adj[u]][0])
        dp[u][1] = max(dp[u][1], dp[adj[u]][1])

    for i in range(N):
        dfs(i)
    vis = [False for _ in range(N)]
    for i in range(N):
        dfs(i)

    ans = 0
    for i in range(N):
        if A[i][0] >= dp[adj[i]][0] and A[i][1] >= dp[adj[i]][1]:
            ans += 1
    print(dp)
    return ans


# Do not modify below this line
line1 = input()
testCases = int(line1.split()[0])
for i in range(0, testCases):
    n = int(input())
    vals = []
    out = [0] * n
    for i in range(n):
        inp = input().split()
        vals.append([int(inp[0]), int(inp[1])])
    for i in range(n):
        inp = input().split()
        u = i
        v = int(inp[0])
        out[u] = v
    print(unbeatable(n, vals, out))


"""
3
3
1 2
3 4
5 6
2
3
1
4
1 1
3 3
4 2
2 2
2
3
1
2
7
4 5
2 9
2 0
8 4
1 7
2 3
6 9
4
1
1
2
2
3
3
"""