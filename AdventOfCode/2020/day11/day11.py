# from math import *


ans = 0
ans2 = 0

with open("input.txt") as file:
    A = [list(line.strip()) for line in file]
    # A = [int(line.strip()) for line in file]
print("N =", len(A))

def count(r, c):
    ct = 0
    for cr, cc in [(1, 1), (1, 0), (1, -1), (0, 1), (0, -1), (-1, -1), (-1, 0), (-1, 1)]:
        nr = r + cr
        nc = c + cc
        while nr >= 0 and nc >= 0 and nr < len(A) and nc < len(A[0]):
            if A[nr][nc] == '#':
                ct += 1
                break
            if A[nr][nc] == 'L':
                break
            nr += cr
            nc += cc

    return ct


change = True
while change:
    change = False
    B = [[a for a in x] for x in A]

    for i in range(len(A)):
        for j in range(len(A[i])):
            if A[i][j] == '.':
                continue
            full = count(i, j)
            if A[i][j] == 'L':
                if full == 0:
                    B[i][j] = '#'
                    change = True
            elif A[i][j] == '#' and full >= 5:
                B[i][j] = 'L'
                change = True

    A = [[a for a in x] for x in B]
    # print('\n'.join([''.join(x) for x in A]))
    # print()

for x in A:
    ans += x.count('#')

print("ans1:", ans)
print("ans2:", ans2)