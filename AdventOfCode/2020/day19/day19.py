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

rules = []
size = []


def check(s, r):
    if len(s) == 0:
        return -1
    if r == 8:
        ok = True
        idx = 0
        while idx < len(s):
            L = check(s[idx:], 42)
            if L > 0:
                idx += L
            else:
                ok = False
                break
        if not ok or idx > len(s):
            return -1
        return idx

    if r == 11:
        for i in range(0, len(s)):
            if i * size[31] != (len(s) - i) * size[42]:
                continue
            if check(s[:i], 8) == i:
                ok = True
                idx = i
                while idx < len(s):
                    L = check(s[idx:], 31)
                    if L > 0:
                        idx += L
                    else:
                        ok = False
                        break
                if ok and idx == len(s):
                    return idx
        return -1

    for x in rules[r].split(' | '):
        ok = True
        idx = 0
        for rule in x.split():
            if idx >= len(s):
                ok = False
                break
            if rule in ('a', 'b'):
                if s[idx] == rule:
                    idx += 1
                else:
                    ok = False
                    break
            else:
                L = check(s[idx:], int(rule))
                if L > 0:
                    idx += L
                else:
                    ok = False
                    break

        if ok:
            return idx
    return -1


mode = 0
for i in range(0, N):
    a = A[i]
    if len(a) == 0:
        mode = 1
        rules.sort(key=lambda s: int(s.split()[0].strip(':')))
        rules = [x.split(': ')[1].replace('"', '') for x in rules]

        while 0 in size:
            for r in range(len(rules)):
                if size[r] != 0:
                    continue
                if rules[r] in ('a', 'b'):
                    size[r] = 1
                    continue
                parts = [int(x) for x in rules[r].split('|')[0].split()]
                print(parts)
                s = [size[p] for p in parts]
                if 0 not in s:
                    size[r] = sum(s)

        continue

    if mode == 0:
        rules.append(a)
        size.append(0)
    else:
        print(N-i)
        for j in range(len(a)):
            if check(a[:j], 8) + check(a[j:], 11) == len(a):
                ans += 1
                break

print("ans1:", ans)
print("ans2:", ans2)
