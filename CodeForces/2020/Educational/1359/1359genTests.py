# T = 1
# N = 11
# M = 451
# X = 4
# Y = 191
#
# print(T)
# print(N, M, X, Y)
# for _ in range(N):
#     print('.' * M)


# B
# T = 500
# N = 100
# M = 1000
# X = 1000
# Y = 1000
#
# print(T)
# for tc in range(T):
#     print(N, M, X, Y)
#     print('\n'.join(['.'*M for _ in range(N)]))


# C
t = 30000
H = 1000000
print(t)
for tc in range(t):
    C = int('1' * ((tc % 5) + 1))
    T = int((H+C)/2) + 1
    print(H, C, T)