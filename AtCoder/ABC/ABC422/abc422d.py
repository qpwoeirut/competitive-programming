N, K = map(int, input().split())
v = K // (1 << N)
A = [v for _ in range(1 << N)]

def recurse(lo, hi, val):
    if val == 0:
        return
    if hi - lo == val:
        for i in range(lo, hi):
            A[i] += 1
        return
    recurse(lo, (lo + hi) // 2, val // 2)
    recurse((lo + hi) // 2, hi, (val + 1) // 2)

recurse(0, 1 << N, K - v * (1 << N))
print(len(set(A)) - 1)
print(*A)
