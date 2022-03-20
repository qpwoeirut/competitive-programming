T = int(input())

MOD = 998244353

for _ in range(T):
    a, b = map(int, input().split())

    print((a * pow(a+b, MOD-2, MOD)) % MOD, flush=False)

