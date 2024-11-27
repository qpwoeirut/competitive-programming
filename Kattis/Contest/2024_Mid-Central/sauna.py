import sys

input = sys.stdin.readline

N = int(input())
A = [tuple(map(int, input().split())) for _ in range(N)]

lo = max(map(lambda t: t[0], A))
hi = min(map(lambda t: t[1], A))

if lo > hi:
    print("bad news")
else:
    print(hi - lo + 1, lo)
