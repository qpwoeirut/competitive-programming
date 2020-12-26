# from math import *
# from itertools import *
# from math import *
from collections import deque

ans = 0
ans2 = 0

with open("input.txt") as file:
    A = [line.strip() for line in file]
    # A = [int(line.strip()) for line in file]

N = len(A)
print("N =", N)
# print(A[:10])

# M = len(A[0])

cards = [deque(maxlen=51), deque(maxlen=51)]

m = 0
for i in range(0, N):
    a = A[i]

    if a.startswith('Player'):
        continue
    if len(a) == 0:
        m = 1
        continue

    cards[m].append(int(a))


def pack(d: deque) -> int:
    x = 0
    for c in d:
        x *= 52
        x += c
    return x


def play(c1: deque, c2: deque):
    seen = set()
    while len(c1) > 0 and len(c2) > 0:
        p = pack(c1)
        if p in seen:
            return 0, c1
        seen.add(p)
        x = c1.popleft()
        y = c2.popleft()

        if x <= len(c1) and y <= len(c2):
            w, _ = play(deque([c1[i] for i in range(x)], maxlen=51), deque([c2[i] for i in range(y)], maxlen=51))
        else:
            w = x < y

        if w:
            c2.extend([y, x])
        else:
            c1.extend([x, y])
    if len(c1) == 0:
        return 1, c2
    else:
        return 0, c1


win, cards = play(cards[0], cards[1])
print(win)
for i, x in enumerate(reversed(cards)):
    ans += (i + 1) * x

print("ans1:", ans)
print("ans2:", ans2)
