problem = 'A'

if problem == 'A':
    T = int(5e4)
    X = int(1e9)
    Y = 1
    N = int(1e9) - 1
    print(T)
    for _ in range(T):
        print(X, Y, N)

if problem == 'B':
    T = int(2e4)
    # N = 31607 * 31607
    N = 5
    while N * 3 <= 1e9:
        N *= 3

    print(T)
    for _ in range(T):
        print(N)

if problem == 'D':
    T = 1
    N = int(2e5)
    K = 219384

    MX = int(1e9) - 1

    print(T)
    for _ in range(T):
        print(N, K)
        print(' '.join([str(MX - i) for i in range(N)]))

if problem == 'E':
    from random import randint, seed

    seed(8)
    N = int(2e5)
    K = int(2e5) - 1
    a = int(1e4)

    print(N, K)

    for i in range(N - 2):
        print(a - randint(0, 5), 1, 1)

    print(a, 1, 0)
    print(a, 0, 1)
