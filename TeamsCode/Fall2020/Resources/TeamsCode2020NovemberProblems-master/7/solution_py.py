
N, M = [int(x) for x in input().split()]
arr = [0]*N

for i in range(M):
    x, v = [int(x) for x in input().split()]
    arr[x-1] += v

for i in range(N):
    print(arr[i], end=' ')
print()

