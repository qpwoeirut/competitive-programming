import random


N = 50
M = 10**4
K = 10**6

print(N, M, K)
for _ in range(M):
    a = random.randint(1, N)
    b = random.randint(1, N)
    while a == b:
        b = random.randint(1, N)
    t = random.randint(1, 5)

    print(a, b, t)

