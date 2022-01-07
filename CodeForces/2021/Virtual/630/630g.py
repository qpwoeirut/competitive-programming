from math import comb

N = int(input())
print(comb(N+4, 5) * comb(N+2, 3))
