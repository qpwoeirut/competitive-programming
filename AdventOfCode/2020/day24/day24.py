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
# print(A[:10])

# M = len(A[0])

to_num = {
    "e": 0,
    "w": 1,
    "nw": 2,
    "se": 3,
    "sw": 4,
    "ne": 5
}

temp_equal = {
    "e": ("se", "ne"),
    "w": ("sw", "nw"),
    "nw": ("w", "ne"),
    "se": ("e", "sw"),
    "sw": ("w", "se"),
    "ne": ("e", "nw")
}
equal = dict()
for k, v in temp_equal.items():
    equal[to_num[k]] = (to_num[v[0]], to_num[v[1]])


def convert(arr: list) -> int:
    change = True
    while change:
        change = False
        for i in range(0, 6, 2):
            x = min(arr[i], arr[i + 1])
            arr[i] -= x
            arr[i + 1] -= x
            if x > 0:
                change = True
        for k, v in equal.items():
            x = min(arr[v[0]], arr[v[1]])
            arr[k] += x
            arr[v[0]] -= x
            arr[v[1]] -= x
            if x > 0:
                change = True

    as_num = 0
    for x in arr:
        as_num <<= 8
        as_num += x
    return as_num


def as_list(num):
    x = []
    for i in range(6):
        x.append(num & ((1 << 8) - 1))
        num >>= 8
    x.reverse()
    return x


seen = set()
for i in range(0, N):
    a = A[i]
    j = 0
    ct = [0 for _ in range(6)]
    while j < len(a):
        if a[j] in ('s', 'n'):
            ct[to_num[a[j:j + 2]]] += 1
            j += 2
        else:
            ct[to_num[a[j]]] += 1
            j += 1

    p = convert(ct)
    if p in seen:
        seen.remove(p)
    else:
        seen.add(p)

ans = len(seen)

cur = set()
nxt = seen.copy()

for rnd in range(100):
    print(rnd)
    cur = nxt.copy()
    nxt = set()
    neighbors = dict()
    for x in cur:
        for i in range(6):
            lst = as_list(x)
            lst[i] += 1
            as_num = convert(lst)
            if as_num not in neighbors:
                neighbors[as_num] = 1
            else:
                neighbors[as_num] += 1

    for k, v in neighbors.items():
        if k not in cur and v == 2:
            nxt.add(k)
        elif k in cur and 1 <= v <= 2:
            nxt.add(k)

ans2 = len(nxt)

print("ans1:", ans)
print("ans2:", ans2)
