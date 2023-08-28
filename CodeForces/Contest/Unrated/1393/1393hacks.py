import random
random.seed(8)

N = int(1e5)
Q = int(1e5)
MX = int(1e5)

nums = random.choices(range(1, MX + 1), k=N >> 1)

A = nums + nums
random.shuffle(A)

assert len(A) == N
print(N)
print(' '.join([str(x) for x in A]))

print(Q)
for i in nums:
    print(f'+ {i}')
for i in nums:
    print(f'+ {i}')