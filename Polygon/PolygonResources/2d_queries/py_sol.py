from sys import stdin

input = stdin.readline

N, M, Q = map(int, input().split())
G = [list(map(int, input().split())) for row in range(N)]

ans = []

for q in range(Q):
    query = list(map(int, input().split()))
    query[1] -= 1
    query[2] -= 1
    if query[0] == 1:
        G[query[1]][query[2]] = query[3]
    elif query[0] == 2:
        ans.append(str(G[query[1]][query[2]]))
    else:
        raise ValueError("unexpected query type")

print('\n'.join(ans))

