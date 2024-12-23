import itertools
from collections import defaultdict

from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [7, 'co,de,ka,ta']
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    A = [line.split('-') for line in input_string.split('\n')]
    # A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line.split())) for line in input_string.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    # M = len(A[0])

    ans1 = 0
    ans2 = 0

    nodes = set()
    adj = dict()
    for a, b in A:
        nodes.add(a)
        nodes.add(b)
        if a not in adj:
            adj[a] = []
        if b not in adj:
            adj[b] = []
        adj[a].append(b)
        adj[b].append(a)

    edges = set(tuple(a) for a in A)
    for a, b, c in itertools.combinations(nodes, r=3):
        if all((x, y) in edges or (y, x) in edges for x, y in itertools.combinations((a, b, c), r=2)):
            ans1 += a.startswith('t') or b.startswith('t') or c.startswith('t')

    ans2 = ''
    largest = max(len(adj[u]) for u in nodes)
    print(largest)
    full = [{u} for u in nodes]
    start = 0
    change = True
    while change:
        change = False

        n = len(full)
        print(n, start)
        for i in range(start, n):
            for u in nodes:
                if u not in full[i] and all((u, v) in edges or (v, u) in edges for v in full[i]) and max(full[i]) < u:
                    full.append(full[i] | {u})
                    change = True

                    val = ','.join(sorted(full[-1]))
                    if len(ans2) < len(val):
                        ans2 = val
        start = n


    # for i in range(N):

    if LEVEL == 1:
        return ans1
    else:
        return ans2


def main():
    with open("sample.txt") as sample_file:
        sample_input = sample_file.read().strip('\n')
    sample_answer = solve(sample_input)
    print("Answer for sample:", sample_answer)
    assert sample_answer == SAMPLE_ANSWER and sample_answer is not None, f"Got {sample_answer} instead of {SAMPLE_ANSWER}"

    with open("input.txt") as input_file:
        inp = input_file.read().strip('\n')
    answer = solve(inp)
    print("Answer:", answer)
    assert submit_answer(2024, 23, LEVEL, answer) is True


if __name__ == '__main__':
    main()
