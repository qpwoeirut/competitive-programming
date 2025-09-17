H, W = map(int, input().split())
G = [input() for _ in range(H)]
ok = True
for i, r in enumerate(G):
    for j, v in enumerate(r):
        ct = 0
        for d in range(4):
            ni = i + [1, 0, -1, 0][d]
            nj = j + [0, 1, 0, -1][d]
            if 0 <= ni < H and 0 <= nj < W: ct += G[ni][nj] == '#'
        if v == '#' and ct not in (2, 4):
            ok = False
print("Yes" if ok else "No")
