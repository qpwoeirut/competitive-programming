P = 126271

x = P >> 1
y = (P + 1) >> 1

N = 20
A = [P * (1 << (i * 2)) for i in range(6)] + [(1 << (i*2)) for i in range(14)]
assert(max(A) <= 1e9)
A = [str(x) for x in A]

print(N)
print(' '.join(A))

