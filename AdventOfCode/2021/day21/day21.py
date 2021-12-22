# from collections import *
from itertools import *
# from math import *

ans = 0
ans2 = 0

#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]

# with open("input.txt") as file:
    # A = list(map(int, file.readline().split(',')))
    # A = [int(line.strip()) for line in file]
    # A = [line.strip() for line in file]
    # A = [list(map(int, line.strip())) for line in file]

# N = len(A)
# print("N =", N)
# print(A[:10])
# M = len(A[0])

p = [6, 2]
y = 0
s = [0, 0]
ct = 0

for i in cycle(range(1, 101)):
    ct += 1
    p[y] = (p[y] + i - 1) % 10 + 1
    if ct % 3 == 0:
        s[y] += p[y]

        if s[y] >= 1000:
            ans = (s[y^1] * ct)
            break

        y ^= 1


POSITION = 10
SCORE = 40
dp = [[[[[0, 0] for _ in range(SCORE)] for _ in range(SCORE)] for _ in range(POSITION)] for _ in range(POSITION)]
dp[6-1][2-1][0][0][0] = 1
for score in product(range(21), range(21)):
    for pos in product(range(POSITION), range(POSITION)):
        for i in range(2):
            for x in product([1,2,3], repeat=3):
                tpos = list(pos)
                tpos[i] = (tpos[i] + sum(x)) % 10
                tscore = list(score)
                tscore[i] += tpos[i] + 1
                dp[tpos[0]][tpos[1]][tscore[0]][tscore[1]][i^1] += dp[pos[0]][pos[1]][score[0]][score[1]][i]
        if max(dp[pos[0]][pos[1]][score[0]][score[1]]) > 0:
            print(pos, score, dp[pos[0]][pos[1]][score[0]][score[1]][0], dp[pos[0]][pos[1]][score[0]][score[1]][1])


win1 = 0
win2 = 0
for score in product(range(21), range(21, SCORE)):
    for pos in product(range(POSITION), range(POSITION)):
        if max(dp[pos[0]][pos[1]][score[0]][score[1]]) > 0 or True:
            print(pos, score, dp[pos[0]][pos[1]][score[0]][score[1]][0], dp[pos[0]][pos[1]][score[0]][score[1]][1])
        win2 += sum(dp[pos[0]][pos[1]][score[0]][score[1]])
        win1 += sum(dp[pos[0]][pos[1]][score[1]][score[0]])
ans2 = max(win1, win2)
print("ans1:", ans)
print("ans2:", ans2)
