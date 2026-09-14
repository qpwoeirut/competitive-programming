import collections
import sys


def calculate_triples(n):
    lo, hi = 2, n
    used = [False] * (n + 1)
    idxs = []
    while lo < hi - lo < hi:
        idxs.append((lo, hi - lo, hi))
        used[lo] = used[hi - lo] = used[hi] = True
        while lo < hi and used[lo]:
            lo += 1
        while lo < hi and used[hi]:
            hi -= 1
    for i in range(2, n):
        if used[i] is False and used[i+1] is False:
            idxs.append((1, i, i+1))
            break
    return idxs


def solve(N, K, C):
    counts = collections.Counter(C)
    ans = [None] * N
    pairs = []
    triples = []

    for val, ct in counts.items():
        if ct == 1:
            if N % 2 == 0 or ans[N // 2] is not None:
                return None
            ans[N // 2] = val
        elif ct % 2 == 0:
            pairs.extend([val] * (ct // 2))
        else:
            pairs.extend([val] * ((ct - 3) // 2))
            triples.append(val)

    if len(triples) % 2 == 1:
        if N % 2 == 0 or ans[N // 2] is not None:
            return None
        val = triples.pop()
        ans[N // 2] = val
        pairs.append(val)

    if N % 2 == 0 and triples:
        return None

    triple_idxs = calculate_triples(N // 2)
    if len(triple_idxs) < len(triples) // 2:
        return None

    for i in range(0, len(triples), 2):
        a, b, c = triple_idxs.pop()
        center = N // 2
        ans[center - a] = ans[center - b] = ans[center + c] = triples[i]
        ans[center + a] = ans[center + b] = ans[center - c] = triples[i + 1]

    for i in range(N // 2):
        if ans[i] is None:
            assert ans[-i - 1] is None
            assert pairs
            ans[i] = ans[-i - 1] = pairs.pop()

    pos = [[] for _ in range(K)]
    for i, val in enumerate(ans):
        assert val is not None, f"{N} {K}\n{C}\n{ans}"
        pos[val - 1].append(i)

    assert all(sum(p) * 2 == len(p) * (N - 1) for p in pos), pos
    assert all(len(p) == counts[i + 1] for i, p in enumerate(pos))
    
    return ans


#for i in range(50):
#    idxs = calculate_triples(i)
#    print(i, len(idxs), idxs)
#exit()

import itertools
def brute(N, K, C):
    last = None
    for perm in itertools.permutations(C):
        if perm == last:
            continue
        last = perm

        pos = [[] for _ in range(K)]
        for i, val in enumerate(perm):
            pos[val - 1].append(i)

        if all(sum(p) * 2 == len(p) * (N - 1) for p in pos):
            return perm
    return None

import random
T = 10**5
for i in range(T):
    if i % 100 == 0: print(i)
    N = random.randint(4, 11)
    K = random.randint(1, 4)
    C = list(range(1, K + 1)) + [random.randint(1, K) for _ in range(N - K)]
    random.shuffle(C)
    solve_out = solve(N, K, C)
    brute_out = brute(N, K, C)
    assert (solve_out is None) is (brute_out is None), f"{N} {K}\n{C}\n{solve_out}\n{brute_out}"
exit()

T = int(sys.stdin.readline())
for _ in range(T):
    N, K = map(int, sys.stdin.readline().split())
    C = list(map(int, sys.stdin.readline().split()))
    out = solve(N, K, C)
    if out:
        print("YES")
        print(*out)
    else:
        print("NO")


"""
12 4
1 1 1 2 2 2 3 3 3 4 4 4
15 5
1 1 1 2 2 2 3 3 3 4 4 4 5 5 5
11 4
1 1 1 2 2 2 3 3 3 4 4
14 3
1 1 1 2 2 2 2 3 3 3 3 3 3 3
15 4
1 1 1 2 2 2 2 3 3 3 3 3 3 3 4


1 + 2 = 3

1 + 6 = 7
2 + 3 = 5

2 + 5 = 7
1 + 3 = 4

2 + 8 = 10
3 + 6 = 9
1 + 4 = 5

1 + 9 = 10
2 + 6 = 8
3 + 4 = 7

4 + 6 = 10
2 + 7 = 9
3 + 5 = 8

1 + 12 = 13
2 + 9 = 11
3 + 5 = 8
4 + 6 = 10

2 + 11 = 13
3 + 9 = 12
4 + 6 = 10
1 + 7 = 8
"""
