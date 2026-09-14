import random


N = 10
D = 100000

print(N, D)
print(*range(1, N+1))
print(*range(1, N+1))
for _ in range(D-1):
    x = random.randint(1, N)
    y = random.randint(1, N)
    while x == y:
        y = random.randint(1, N)
    if x > y:
        x, y = y, x
    print(random.randint(1, 2), x, y)
