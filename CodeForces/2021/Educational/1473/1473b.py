T = int(input())

ans = []
for _ in range(T):
    s = input()
    t = input()

    best = 1001001
    for i in range(1, 21):
        x = s*i
        for j in range(1, 21):
            if x == t*j:
                best = min(best, len(s) * i)

    if best == 1001001:
        ans.append("-1")
    else:
        ans.append(s * (best // len(s)))

print('\n'.join(ans))
