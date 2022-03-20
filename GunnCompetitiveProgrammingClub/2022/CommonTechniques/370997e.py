N, B = map(int, input().split())

MOD = 998244353

numer = 1
denom = 1
for i in range(B):
    numer = (numer * (N + i)) % MOD
    denom = (denom * (i + 1)) % MOD

print((numer * pow(denom, MOD-2, MOD)) % MOD)

