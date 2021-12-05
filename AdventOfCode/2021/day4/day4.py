# from itertools import *
# from math import *

ans = 0
ans2 = 0

with open("input.txt") as file:
    nums = list(map(int, file.readline().split(',')))
    file.readline()
    A = [[list(map(int, file.readline().strip().split())) for _ in range(6)][:-1] for _ in range(100)]
    # A = [line.strip() for line in file]
    # A = [int(line.strip()) for line in file]

N = len(A)
print("N =", N)
print(A[:10])


# M = len(A[0])

def wins(board):
    s = sum([sum([c for c in r if c != -1]) for r in board])
    for r in board:
        if set(r) == {-1}:
            return s
    for c in range(len(board[0])):
        if set([board[r][c] for r in range(len(board))]) == {-1}:
            return s
    return -1


done = [False for _ in A]

for num in nums:
    print(num)
    for a in A:
        for row in a:
            for i in range(len(row)):
                if row[i] == num:
                    row[i] = -1

    scores = [num * wins(a) for a in A]
    for i in range(len(scores)):
        if scores[i] > 0:
            done[i] = True
    if done.count(False) == 1 and ans2 == 0:
        ans2 = -done.index(False)
    if done.count(False) == 0 and ans2 <= 0:
        assert ans2 != 0
        ans2 = num * wins(A[-ans2])
    score = max(scores)
    if score > 0 and ans == 0:
        ans = score

print("ans1:", ans)
print("ans2:", ans2)
