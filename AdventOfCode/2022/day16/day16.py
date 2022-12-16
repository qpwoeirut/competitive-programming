# from collections import *
# from itertools import *
# from math import *
from collections import defaultdict

from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [1651, 1707]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(s: str) -> int or str:
    # A = list(s)
    # A = list(map(int, s.split(',')))
    A = [line for line in s.split('\n')]
    # A = [line for line in s.split('\n')]
    # A = [list(map(int, line)) for line in s.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    # M = len(A[0])

    value = dict()
    adj = dict()

    useful = []

    for i in range(N):
        s = A[i].strip().split()
        name = s[1]
        value[name] = int(s[4].strip(';').split('=')[1])
        adj[name] = [x.strip(',') for x in s[9:]]
        if value[name] > 0:
            useful.append(name)

    useful_idx = {useful[i]: i for i in range(len(useful))}

    T = 60 if LEVEL == 1 else 52
    X = 2**len(useful)
    dp = [[defaultdict(lambda: defaultdict(lambda: -1)) for _ in range(X)] for _ in range(T+1)]
    dp[0][0]["AA"]["AA"] = 0

    total_value = sum(value.values())
    ans = 0
    for t in range(T):
        next_t = t + 2 if LEVEL == 1 else t + 1
        print(t)
        for x in range(X):
            for cur, elephant in dp[t][x].items():
                for e, val in elephant.items():
                    if total_value * ((T - t - 1) // 2) + val <= ans:
                        continue
                    ans = max(ans, val)
                    if t % 2 == 0:
                        if cur in useful_idx and ((x >> useful_idx[cur]) & 1) == 0:
                            dp[next_t][x | (1 << useful_idx[cur])][cur][e] = val + ((T - t - 1) // 2) * value[cur]
                        for nxt in adj[cur]:
                            if dp[next_t][x][nxt][e] < val:
                                dp[next_t][x][nxt][e] = val
                    elif LEVEL == 2:
                        if e in useful_idx and ((x >> useful_idx[e]) & 1) == 0:
                            dp[next_t][x | (1 << useful_idx[e])][cur][e] = val + ((T - t - 1) // 2) * value[e]
                        for nxt in adj[e]:
                            if dp[next_t][x][cur][nxt] < val:
                                dp[next_t][x][cur][nxt] = val

    return ans


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
    assert submit_answer(2022, 16, LEVEL, answer) is True


if __name__ == '__main__':
    main()
