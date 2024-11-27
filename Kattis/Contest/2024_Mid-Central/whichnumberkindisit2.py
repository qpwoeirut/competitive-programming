import sys

input = sys.stdin.readline

T = int(input())
A = [int(input()) for _ in range(T)]

def solve(n):
    s = ""
    if n % 2 == 1:
        s += 'O'
    if round(n ** 0.5) ** 2 == n:
        s += 'S'
    if s == '':
        s = "EMPTY"
    return s

ans = [solve(x) for x in A]
print('\n'.join(ans))

