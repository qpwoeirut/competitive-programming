import collections
from copy import deepcopy

from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [19114, 167409079868000]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def evaluate(conditions, x, m, a, s):
    vals = {
        "x": x, "m": m, "a": a, "s": s
    }
    parts = conditions.split(',')
    for part in parts:
        if ':' not in part:
            return part
        lhs = part[0]
        comp = part[1]
        rhs = int(part[2:].split(':')[0])
        if_true = part.split(':')[1]
        if comp == '<':
            result = vals[lhs] < rhs
        else:
            assert comp == '>'
            result = vals[lhs] > rhs
        if result:
            return if_true
    assert False


def eval_list(conditions, vals: dict):
    parts = conditions.split(',')
    conds = collections.defaultdict(lambda: [])
    for i, part in enumerate(parts):
        if ':' not in part:
            conds[part].append(vals)
            break

        lhs = part[0]
        comp = part[1]
        rhs = int(part[2:].split(':')[0])
        if_true = part.split(':')[1]

        good_vals = {deepcopy(k): deepcopy(v) for k, v in deepcopy(vals).items()}
        lvals = deepcopy(vals[lhs])
        if comp == '<':
            good_vals[lhs] = [x for x in lvals if x < rhs]
            vals[lhs] = [x for x in lvals if x >= rhs]
        else:
            assert comp == '>'
            good_vals[lhs] = [x for x in lvals if x > rhs]
            vals[lhs] = [x for x in lvals if x <= rhs]

        conds[if_true].append(deepcopy(good_vals))
    return conds


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    A = [line for line in input_string.split('\n')]
    # A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line.split())) for line in input_string.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    # M = len(A[0])

    ans1 = 0
    ans2 = 0

    flows = dict()
    objs = []
    section = 0
    for i in range(N):
        if not A[i]:
            section = 1
            continue

        if section == 0:
            name, conditions = A[i].strip('}').split('{')
            flows[name] = conditions
        else:
            exec(A[i].strip('{}').replace(',', '\n') + "\nobjs.append((x, m, a, s))")

    for x, m, a, s in objs:
        cur_flow = "in"
        while cur_flow not in ("A", "R"):
            cur_flow = evaluate(flows[cur_flow], x, m, a, s)
        if cur_flow == 'A':
            ans1 += sum([x, m, a, s])

    possible = dict()
    possible["in"] = [{"x": list(range(1, 4001)), "m": list(range(1, 4001)), "a": list(range(1, 4001)), "s": list(range(1, 4001))}]
    q = collections.deque()
    q.append("in")
    while q:
        u = q.popleft()
        # for p in possible[u]:
        #     print(u)
        #     for k, val in p.items():
        #         print(k, min(val), max(val))
        if not possible[u] or u in ('A', 'R'):
            continue

        for poss in possible[u]:
            conds = eval_list(flows[u], deepcopy(poss))
            for v, ranges_list in conds.items():
                for ranges in ranges_list:
                    if v not in possible:
                        possible[v] = []
                    possible[v].append(deepcopy(ranges))
                    q.append(v)

        possible[u].clear()

    for poss in possible['A']:
        print(len(poss['x']) * len(poss['m']) * len(poss['a']) * len(poss['s']))
        ans2 += len(poss['x']) * len(poss['m']) * len(poss['a']) * len(poss['s'])

    # reject = 0
    # for poss in possible['R']:
    #     reject += len(poss['x']) * len(poss['m']) * len(poss['a']) * len(poss['s'])
    # print(ans2, reject, ans2 + reject)
    # print([k for k, v in possible.items() if not v])
    # print([k for k, v in possible.items() if v])

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
    assert submit_answer(2023, 19, LEVEL, answer) is True


if __name__ == '__main__':
    main()
