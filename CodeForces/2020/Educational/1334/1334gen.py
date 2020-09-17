
# T = 1
# MN = int(1e5)
# MA = int(1e9)
# L = 1
# R = MN
# # R = MN*(MN-1) + 1
# # L = R - (MN - 1)
#
# print(T)
# for test in range(T):
#     print(MN, L, R)
# print(' '.join([str(MA - i) for i in range(MN)]))



from sympy import nextprime

D = 1
cur = 1
while D <= int(1e15):
    cur = nextprime(cur)
    D *= cur

print(D//cur)