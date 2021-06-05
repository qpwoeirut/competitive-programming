N = int(input())
A = list(map(int, input().split()))
op = input().split()

best_val = -1e100
used = [False] * N

def dfs(k, val):
    global best_val, A, op, used
    if k == N - 1:
        best_val = max(best_val, val)
    else:
        for i in range(N):
            if used[i]: continue
            used[i] = True
            cur = val
            if op[k] == '+': cur += A[i]
            elif op[k] == '-': cur -= A[i]
            elif op[k] == '*': cur *= A[i]
            elif op[k] == '/': cur /= A[i]
            dfs(k + 1, cur)
            used[i] = False

for i in range(N):
    used[i] = True
    dfs(0, A[i])
    used[i] = False

print(best_val)
