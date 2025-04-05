a, b = input().split()

a = int(a, 2)
b = int(b, 2)

ans = 0
for x in range(a, b + 1):
    for y in range(x):
        if bin(x).count('1') < bin(y).count('1'):
            ans += 1

print(ans)

