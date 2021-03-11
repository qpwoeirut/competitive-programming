params = [(1e5, 1e9), (1e6, 100), (1e6, 1e9), (1e7, 100), (1e7, 1e5 - 1)]
params = [(int(t[0]), int(t[1])) for t in params]

RANDS = 10

for param in params:
    for test in range(RANDS):
        print(f"array_gen 0 {param[0]} {-param[1]} {param[1]} {test} > $")
    print(f"array_gen 1 {param[0]} {-param[1]} {param[1]} > $")
    print(f"array_gen 2 {param[0]} {-param[1]} {param[1]} > $")
