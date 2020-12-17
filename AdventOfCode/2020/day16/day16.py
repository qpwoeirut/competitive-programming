# from math import *
# from itertools import *
# from math import *

ans = 0
ans2 = 0

with open("input.txt") as file:
    A = [line.strip() for line in file]
    # A = [int(line.strip()) for line in file]

N = len(A)
print("N =", N)
print(A[:10])
# M = len(A[0])

ranges = [((0, 0), (0, 0)) for _ in range(20)]
cur = 0
mine = list()
valid = []
for i in range(0, N):
    a = A[i]
    if a == '':
        cur += 1
    elif cur == 0:
        k, v = a.split(':')
        a, b = v.strip().split(' or ')
        ranges[i] = (int(a.split('-')[0]), int(a.split('-')[1])), (int(b.split('-')[0]), int(b.split('-')[1]))
    elif cur == 1:
        if a.startswith("your"):
            continue
        mine = [int(q) for q in A[i].split(',')]
    else:
        if a.startswith("nearby"):
            continue
        all_ok = True
        for x in a.split(','):
            x = int(x)
            ok = False
            for r1, r2 in ranges:
                if r1[0] <= x <= r1[1]:
                    ok = True
                    break
                if r2[0] <= x <= r2[1]:
                    ok = True
                    break

            if not ok:
                ans += x
                all_ok = False

        if all_ok:
            valid.append([int(q) for q in A[i].split(',')])

cols = len(mine)
possible = [[] for _ in range(cols)]
for i, r in enumerate(ranges):
    for c in range(cols):
        ok = True
        for t in valid + [mine]:
            if not (r[0][0] <= t[c] <= r[0][1] or r[1][0] <= t[c] <= r[1][1]):
                ok = False
        if ok:
            possible[c].append(i)

print(possible)
used = [False for _ in range(cols)]
perm = [-1 for _ in range(cols)]


def gen(col):
    if col <= 1:
        print(col)
    if col >= cols:
        print(perm)
        ans2 = 1
        for i in range(6):
            ans2 *= mine[perm[i]]
        print(ans2)
        return

    for i in possible[col]:
        if used[i] is True:
            continue
        used[i] = True
        perm[col] = i
        gen(col + 1)
        perm[col] = -1
        used[i] = False


print(mine)
correct_perm = [12, 0, 16, 11, 10, 5, 19, 18, 14, 6, 8, 4, 3, 9, 17, 7, 2, 1, 13, 15]
rperm = [correct_perm.index(i) for i in range(cols)]
ans2 = 1
for i in range(6):
    ans2 *= mine[rperm[i]]
print(ans2)
# gen(0)


print("ans1:", ans)
print("ans2:", ans2)
