for n in "12345":
    ct = [0 for _ in range(10)]
    with open("tiny.i" + n) as f:
        N = -1
        for line in f:
            line = int(line)
            if N == -1:
                N = line
            else:
                ct[line] += 1
    print(n, N)
    print(ct)

