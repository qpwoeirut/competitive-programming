# from collections import *
# from itertools import *
# from math import *

ans = 0
ans2 = 0

with open("input.txt") as file:
    # A = list(map(int, file.readline().split(',')))
    # A = [int(line.strip()) for line in file]
    A = [line.strip() for line in file]
    # A = [list(map(int, line.strip())) for line in file]

N = len(A)
print("N =", N)
print(A[:10])
M = len(A[0])

closer = {
    '(': ')',
    '[': ']',
    '{': '}',
    '<': '>'
}
opener = {
    v: k for k, v in closer.items()
}
score = {
    ')': 3,
    ']': 57,
    '}': 1197,
    '>': 25137
}

corrupted = set()

for i in range(N):
    st = []
    s = A[i]
    for c in s:
        if c in '([{<':
            st.append(c)
        else:
            if len(st) == 0 or st[-1] != opener[c]:
                ans += score[c]
                corrupted.add(i)
                break
            st.pop()

t = ".)]}>"

scores = []
for i in range(N):
    if i in corrupted:
        continue
    st = []
    s = A[i]
    for c in s:
        if c in '([{<':
            st.append(c)
        else:
            assert st[-1] == opener[c]
            st.pop()

    cur = 0
    for c in reversed(st):
        cur *= 5
        cur += t.index(closer[c])
    scores.append(cur)

scores.sort()
print(scores)
ans2 = scores[len(scores) // 2]

print("ans1:", ans)
print("ans2:", ans2)
