import functools
import itertools

from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [143, 123]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    # A = [line for line in input_string.split('\n')]
    # A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line.split())) for line in input_string.split('\n')]

    edges, updates = map(lambda s: s.split('\n'), input_string.split('\n\n'))
    edges = list(map(lambda s: tuple(map(int, s.split('|'))), edges))
    updates = list(map(lambda s: list(map(int, s.split(','))), updates))

    ans1 = 0
    ans2 = 0

    nodes = set()
    for a, b in edges:
        nodes.add(a)
        nodes.add(b)
    adj = {u: set() for u in nodes}
    for a, b in edges:
        adj[a].add(b)

    for k, v in adj.items():
        print(k, list(sorted(v)))

    for update in updates:
        ok = True
        for i, j in itertools.combinations(range(len(update)), r=2):
            ok &= not update[i] in adj[update[j]]
        if ok:
            ans1 += update[len(update) // 2]
        else:
            fixed = update.copy()
            def cmp(a, b):
                if a in adj[b]:
                    return 1
                if b in adj[a]:
                    return -1
                return 0
            fixed.sort(key=functools.cmp_to_key(cmp))
            ans2 += fixed[len(fixed) // 2]


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
    assert submit_answer(2024, 5, LEVEL, answer) is True


if __name__ == '__main__':
    main()
