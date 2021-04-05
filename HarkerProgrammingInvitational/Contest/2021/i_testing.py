from random import randint
from subprocess import Popen, PIPE


for N in range(1, 10):
    for M in range(1, 10):
        print(N, M)
        K = 10
        for Q in range(1, 100):
            for t in range(100):
                proc = Popen(["./i.out"], stdin=PIPE, stdout=PIPE)
                brute = Popen(["./i_brute.out"], stdin=PIPE, stdout=PIPE)

                G = [[str(randint(1, K)) for c in range(M)] for r in range(N)]
                queries = []
                for q in range(Q):
                    typ = randint(0, 1)
                    if typ == 0:
                        queries.append(f"0 {randint(1, N)} {randint(1, M)} {randint(1, K)}")
                    else:
                        r1 = randint(1, N)
                        r2 = randint(r1, N)
                        c1 = randint(1, M)
                        c2 = randint(c1, M)
                        queries.append(f"1 {r1} {c1} {r2} {c2}")

                inp = f"{N} {M} {K}\n{Q}\n" + '\n'.join([' '.join(row) for row in G]) + '\n' + '\n'.join(queries)
                # print(inp)
                out = proc.communicate(inp.encode())
                ans = brute.communicate(inp.encode())

                if out != ans:
                    print(N, M, K)
