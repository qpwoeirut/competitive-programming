from collections import Counter
import numpy as np

N = 10**6

rng = np.random.default_rng()
mu, sigma = 1, 0.25
exponents = rng.normal(mu, sigma, N)
L = np.power(np.full(N, 10), exponents).round().astype(int)

counter = Counter(L)
scale = 200 / counter.most_common(1)[0][1]
for k, v in sorted(counter.items()):
    v = round(v * scale)
    if v > 0:
        print(str(k).zfill(2), v * '*')

