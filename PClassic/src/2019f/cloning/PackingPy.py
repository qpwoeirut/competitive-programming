def solve (n, m, x, c):
    x.sort()
    dp = [c[1]]
    for i in range (m - 1, 0, -1):
        c[i] = min(c[i], c[i + 1])
    for i in range(1, n):
        mini = c[x[i] - x[0] + 1]
        for j in range(0, i):
            if dp[j] + c[x[i] - x[j + 1] + 1] < mini:
                mini = dp[j] + c[x[i] - x[j + 1] + 1]
        dp.append(mini)
    return dp[n - 1]

if __name__ == '__main__':
    with open('PackingIN.txt', 'r') as f:
        t = int(f.readline().strip())
        l = []
        while t > 0:
            st = f.readline().strip().split()
            n = int(st[0])
            m = int(st[1])
            x = []
            c = []
            st = f.readline().strip().split()
            for i in range(0, n):
                x.append(int(st[i]))
            st = f.readline().strip().split()
            for i in range (0, m + 1):
                c.append(int(st[i]))
            print(solve(n, m, x, c))
            t = t - 1