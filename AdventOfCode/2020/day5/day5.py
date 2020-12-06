def fun(s):
    row = s[:7]
    r = (0, 128)
    for c in row:
        if c == 'F':
            r = (r[0], (r[0] + r[1]) // 2)
        else:
            r = ((r[0] + r[1]) // 2, r[1])

    col = s[7:]
    c = (0, 8)
    for ch in col:
        if ch == 'L':
            c = (c[0], (c[0] + c[1]) // 2)
        else:
            c = ((c[0] + c[1]) // 2, c[1])
    # print(r, c)
    return r[0] * 8 + c[0]

ans = 0
ans2 = 0

with open("day5.txt") as f:
    s = [x.strip() for x in f]

ids = []
for p in s:
    ids.append(fun(p))
    ans = max(ans, fun(p))

ids.sort()
for i in range(1, len(ids)):
    if ids[i-1] + 2 == ids[i]:
        print(ids[i-1])
print(ans)
print(ans2)