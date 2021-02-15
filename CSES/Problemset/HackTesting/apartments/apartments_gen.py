# https://cses.fi/problemset/hack/1084/entry/101274/

N, M = int(2e5), int(2e5)
K = 0

A = [str(int(1e9) - i) for i in range(N)]
B = [str(int(1e9) - N - i) for i in range(N)]

print(N, M, K)
print(' '.join(A))
print(' '.join(B))

