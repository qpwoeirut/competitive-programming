from random import randint, seed

seed(8)

BOUNDS = ((1, 20, 1, 20), (480, 500, 499900, 500000))

for i in range(2):
    for t in range(20):
        n = randint(BOUNDS[i][0], BOUNDS[i][1])
        m = randint(BOUNDS[i][0], BOUNDS[i][1])
        q = randint(BOUNDS[i][2], BOUNDS[i][3])

        print(f"gen {n} {m} {q} > $")

for t in range(10):
    print(f"gen {BOUNDS[1][1]} {BOUNDS[1][1]} {BOUNDS[1][3]} {t} > $")

