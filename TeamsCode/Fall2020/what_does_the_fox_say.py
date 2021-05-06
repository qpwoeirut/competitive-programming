from sys import stdin

input = stdin.readline

n = int(input())

ans = ["" for _ in range(n)]

for i in range(n):
    base, s = input().split()
    ans[i] = bin(int(s, int(base)))[2:]

print('\n'.join(ans))
