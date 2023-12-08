# from collections import *
# from itertools import *
# from math import *
import collections
import itertools
import math

from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [2, 6]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    A = [line.split() for line in input_string.split('\n')]
    # A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line)) for line in input_string.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])

    dirs = A[0][0]
    A = A[2:]
    nodes = {
        t[0]: (t[2].replace('(', '').replace(',', ''), t[3].replace(')', '')) for t in A
    }
    print(nodes)

    states = [node for node in nodes.keys() if node.endswith('A')] if LEVEL == 2 else ["AAA"]
    time_taken = [collections.defaultdict(lambda: []) for _ in states]
    for s_i, state in enumerate(states):
        cur = state
        for t, d in enumerate(itertools.cycle(dirs)):
            cur = nodes[cur]["LR".index(d)]
            if (LEVEL == 1 and cur == "ZZZ") or (LEVEL == 2 and cur.endswith('Z')):
                time_taken[s_i][cur].append(t + 1)
                if len(time_taken[s_i][cur]) > 2 * len(dirs):
                    break


    ans1 = time_taken[0]["ZZZ"][0] if LEVEL == 1 else 0

    print("Done finding time_taken.")
    ans2 = float('inf')
    end_states = [node for node in nodes.keys() if node.endswith('Z')] if LEVEL == 2 else ["ZZZ"]
    for ends in itertools.product(end_states, repeat=len(states)):
        times = [time_taken[i][ends[i]] for i in range(len(states))]
        if any([len(t) < 2 for t in times]):
            single = [t for t in times if len(t) < 2]
            for t in single:
                if t and all([t[0] in tms for tms in times]):
                    ans2 = min(ans2, t[0])
            continue
        periods = [t[-1] - t[-2] for t in times]
        values = [t[-1] % p for t, p in zip(times, periods)]

        # conveniently constructed input!
        assert all([v == 0 for v in values])
        ans2 = min(ans2, math.lcm(*periods))

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
    assert submit_answer(2023, 8, LEVEL, answer) is True


if __name__ == '__main__':
    main()
