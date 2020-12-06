

ans = 0
ans2 = 0
arr = []

with open("day3.txt") as f:
    s = [line.strip() for line in f]

def f(x, y):
    ret = 0
    c = 0
    for i in range(0, len(s), y):
        if s[i][c % len(s[i])] == '#':
            ret += 1

        c += x
    return ret

print(f(1,1) * f(3,1) * f(5,1) * f(7,1) * f(1, 2))
print(ans)