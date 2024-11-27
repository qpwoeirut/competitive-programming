N = int(input())
A = [int(input()) for _ in range(N)]

limit = max(A) // 2
print(max(0, min(A) - limit))

