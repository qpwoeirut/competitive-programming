import sys
input = sys.stdin.readline

Q, X = map(int, input().split())

cur_ans = 0
ans_mod_x = 0
extras = [0 for _ in range(X)]

for q in range(Q):
    extras[int(input()) % X] += 1
    while extras[ans_mod_x] > 0:
        extras[ans_mod_x] -= 1
        cur_ans += 1
        ans_mod_x += 1
        if ans_mod_x == X:
            ans_mod_x = 0
    print(cur_ans, flush=False)

