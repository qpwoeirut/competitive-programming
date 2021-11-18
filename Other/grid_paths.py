dp = [[0 for _ in range(10)] for _ in range(10)]

dp[1][1] = 1

for r in range(1, 10):
    for c in range(1, 10):
        if r == 1 and c == 1:
            dp[r][c] = 1
        elif 3 < r < 7 and 3 < c < 7:
            dp[r][c] = 0
        else:
            dp[r][c] = dp[r-1][c] + dp[r][c-1]

for r in dp:
    print(r)
print(dp[9][9])
