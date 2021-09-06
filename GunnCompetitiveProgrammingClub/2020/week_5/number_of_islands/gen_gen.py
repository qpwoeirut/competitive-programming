from random import randint, seed

seed(8)

MX = 1000

T = 60
for t in range(T):
    t *= t * 2
    mx = min(MX, t+5)
    mn = min(t >> 1, mx - 10)
    mn = max(1, mn)
    print(f"gen {randint(1, 100) + 3} {randint(mn, mx)} {randint(mn, mx)} > $")

for n in range(3):
    print(f"gen {n} {MX-1} {MX} > $")
    print(f"gen {n} {MX} {MX-1} > $")
    print(f"gen {n} {MX} {MX} > $")
