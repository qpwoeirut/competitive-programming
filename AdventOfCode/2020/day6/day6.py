# from math import *


ans = 0
ans2 = 0

with open("input.txt") as file:
    A = [line.strip() for line in file]

cur = set("abcdefghijklmnopqrstuvwxyz")
ct = 0
for x in A:
    if len(x) == 0:
        ans += len(cur)
        cur= set("abcdefghijklmnopqrstuvwxyz")
        ct = 0
    else:
        s = set(x)
        print(s)
        cur = cur.intersection(s)
ans += len(cur)

print("ans1:", ans)
print("ans2:", ans2)
