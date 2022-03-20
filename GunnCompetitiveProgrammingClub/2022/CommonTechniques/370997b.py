T = int(input())

MOD = 998244353

for _ in range(T):
    a, b = map(int, input().split())

    print(pow(a, b, MOD))
