ans = 0
ans2 = 0
with open("day2.txt") as f:
    for line in f:
        line = line.split()
        lo, hi = line[0].split('-')
        lo = int(lo)
        hi = int(hi)
        c = line[1].strip(':')
        if lo <= line[2].count(c) <= hi:
            ans += 1

        ct = 0
        if line[2][lo - 1] == c:
            ct += 1
        if line[2][hi - 1] == c:
            ct += 1
        if ct == 1:
            ans2 += 1

print(ans)
print(ans2)