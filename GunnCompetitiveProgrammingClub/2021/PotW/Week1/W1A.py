N, M = map(int, input().split())
S = list(input())
for _ in range(M):
    lo, hi, c1, c2 = input().split()
    lo = int(lo)
    hi = int(hi)
    for i in range(lo-1, hi):
        if S[i] == c1:
            S[i] = c2
print(''.join(S))

