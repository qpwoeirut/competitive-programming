from sys import stdin

input = stdin.readline

n = int(input())
A = list(map(int, input().split()))
A.sort()
print(*A)
