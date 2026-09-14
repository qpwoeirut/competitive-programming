import collections
import sys

N, Q = map(int, sys.stdin.readline().split())
G = [sys.stdin.readline() for _ in range(N)]
A = [tuple(map(int, sys.stdin.readline().split())) for _ in range(Q)]


def calculate(r1, c1, r2, c2):
    r1 -= 1; c1 -= 1; r2 -= 1; c2 -= 1
    q = collections.deque([(r1, c1, 0)])
    seen = {(r1, c1)}

    while q:
        r, c, dist = q.popleft()
        if r == r2 and c == c2:
            return dist

        for cr, cc in zip((1, 0, -1, 0), (0, 1, 0, -1)):
            nr = r + cr
            nc = c + cc
            if G[nr][nc] == '#' and (nr, nc) not in seen:
                seen.add((nr, nc))
                q.append((nr, nc, dist + 1))

    assert False


if N <= 200 and Q <= 200:
    for query in A:
        print(calculate(*query))
else:
    for r1, c1, r2, c2 in A:
        print(abs(r1 - r2) + abs(c1 - c2))
