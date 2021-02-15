# https://cses.fi/problemset/hack/1713/entry/384627/
from math import sqrt
from sympy import primerange

N = int(1e5)
X = int(1e6)

primes = list(primerange(sqrt(X), X))
A = primes.copy()
for i, p1 in enumerate(primes):
    print(i)
    for j, p2 in enumerate(primes[i:]):
        if p1 * p2 > X:
            break
        A.extend([p1 * p2 * primes[k] for k in range(j, len(primes)) if p1 * p2 * primes[k] <= X])

A = set(A)
for i in reversed(range(0, X)):
    A.add(i)
    if len(A) == N:
        break


nums = '\n'.join([str(x) for x in A])
with open("counting_divisors_prime_semiprime.txt", 'w+') as f:
    f.write(f"{N}\n{nums}\n")
