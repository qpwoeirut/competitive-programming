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

possible = dict()

ingredients = set()

for i in range(0, N):
    a = A[i].strip(')')
    ing, aller = a.split(' (contains ')
    ings = ing.split()
    allergens = aller.split(', ')

    ingredients.update(ings)
    for x in allergens:
        if x not in possible:
            possible[x] = set(ings)
        else:
            possible[x].intersection_update(ings)

print(possible)
done = False

ans2 = []
while not done:
    done = True
    rem = set()
    d = []
    for k, v in possible.items():
        assert len(v) > 0
        if len(v) == 1:
            rem.update(v)
            d.append(k)
            done = False
            ans2.append((k, v.pop()))

    for k in d:
        del possible[k]
    for k, v in possible.items():
        v.difference_update(rem)
    ingredients.difference_update(rem)
    print(rem)

print(possible)
print(ingredients)
s = ' ' + ' '.join(A) + ' '
for ing in ingredients:
    ans += s.count(' ' + ing + ' ')

ans2.sort()
ans2 = ",".join(t[1] for t in ans2)
print("ans1:", ans)
print("ans2:", ans2)
