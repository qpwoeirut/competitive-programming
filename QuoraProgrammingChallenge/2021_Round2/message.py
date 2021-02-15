from collections import Counter

n = int(input())
sentences = [list(map(int, input().split())) for _ in range(n)]

MX = 1000


def to_int(arr):
    x = 0
    for a in arr:
        x *= MX
        x += a
    return x


SZ = 32
chains = [dict() for _ in range(SZ)]
for s in range(1, SZ):
    for sentence in sentences:
        for i in range(s, len(sentence)):
            if -1 in sentence[i-s:i + 1]:
                continue

            x = to_int(sentence[i-s: i])
            if x not in chains:
                chains[s][x] = Counter()
            chains[s][x][sentence[i]] += 1

for sentence in sentences:
    idx = sentence.index(-1)
    ct = Counter()
    for s in range(1, SZ):
        arr = to_int(sentence[max(0, idx - s):idx])
        if arr in chains[s]:
            for k, v in chains[s][arr].items():
                ct[k] += v * s / len(chains[s][arr])

    if len(ct) == 0:
        print(0)
    else:
        print(ct.most_common(1)[0][0], flush=False)

"""
2
1 2 -1 5 4
1 3 2 6 5 -1

2
1 1 1 1 1 1 -1
0 1 1 1 0 1 -1 1
"""
