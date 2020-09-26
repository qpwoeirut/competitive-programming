from math import ceil

n = 2e4

def f(x):
    return 2*x + ceil((n-x) / (x-1))


print(min([(f(i), i) for i in range(2, 100000)]))
