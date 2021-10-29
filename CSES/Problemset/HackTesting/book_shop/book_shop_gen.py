# https://cses.fi/problemset/hack/1158/entry/1692100/

N = 1000
X = 100000
H0 = 1
H1 = 200
S = 1000

print(N, X)
print(" ".join([str(H0 if i % 2 else H1) for i in range(N)]))
print(" ".join([str(S) for _ in range(N)]))

