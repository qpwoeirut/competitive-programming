problem = 'D'

if problem == 'A':
    pass
if problem == 'B':
    pass
if problem == 'C':
    T = 100
    A = 200
    B = 199
    Q = 500
    print(T)
    for t in range(T):
        print(A, B, Q)
        for q in range(Q):
            # ch = (q*t + t) % 9997
            ch = 0
            print(20603 - ch, int(1e18) - ch)
if problem == 'D':
    N = 200000
    K = 200000

    print(N, K)
    print(' '.join([str(n+1) for n in range(N)]))
    print(' '.join(['1' for _ in range(K)]))