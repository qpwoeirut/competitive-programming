from math import prod


n = int(input())
MOD = 10**9 + 7

# https://oeis.org/A051193
factors = dict()

d = 2
x = n
while d*d <= x:
    while x % d == 0:
        factors[d] = factors.get(d, 0) + 1
        x //= d
    d += 1
if x > 1:
    factors[x] = factors.get(x, 0) + 1

ans = 1
for p, e in factors.items():
    ans = (ans * (pow(p, (e << 1) + 1, MOD) + 1) * pow(p + 1, -1, MOD)) % MOD
ans = (n * (ans + 1) * pow(2, -1, MOD)) % MOD
print(ans)

