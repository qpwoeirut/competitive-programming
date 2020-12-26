from random import randint, seed

seed(8)

N = int(2e5)
A = [i * 5000 + randint(-5000, 5000) for i in range(1, N+1)]
A = [str(max(1, min(x, int(1e9)))) for x in A]
A.reverse()

print(N)
print(' '.join(A))
