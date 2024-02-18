T = int(input())

for c in range(1, T):
    ans = 0
    for a in range(1, 1001):
        for b in range(1, 1001):
            if (a + b) * c == a * b:
                ans += 1
                #print(a, b, c)
    print(ans)
