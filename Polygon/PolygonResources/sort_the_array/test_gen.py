from random import randint, seed

seed(8)

SMALL = (1, 1000)
BIG = (499000, 500000)

for t in range(10):
    print(f"gen 0 {randint(*SMALL)} > $")

for t in range(10):
    print(f"gen 0 {randint(*BIG)} > $")

for t in range(5):
    print(f"gen 0 {BIG[1]} {t} > $")
    print(f"gen 1 {BIG[1]} {t} > $")
    print(f"gen 2 {BIG[1]} {t} > $")
    print(f"gen 3 {BIG[1]} {t} > $")

