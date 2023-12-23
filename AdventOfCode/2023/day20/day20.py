import collections

from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 1
SAMPLE_ANSWERS = [32000000, None]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


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

    modules = dict()
    mtype = dict()
    state = dict()
    for i in range(N):
        name, dests = A[i].split(' -> ')
        if name not in ("broadcaster", "output"):
            mtype[name[1:]] = name[0]
            name = name[1:]
            if mtype[name] == '%':
                state[name] = 0
            else:
                assert mtype[name] == '&'
                state[name] = dict()
        else:
            mtype[name] = name
            state[name] = None
        dests = dests.split(', ')
        modules[name] = dests
        for dest in dests:
            if dest not in modules:
                modules[dest] = []
            if dest not in mtype:
                mtype[dest] = dest
            if dest not in state:
                state[dest] = None

    for name, dests in modules.items():
        for dest in dests:
            if mtype[dest] == '&':
                state[dest][name] = 0

    instances = {  # hardcoding go brrr
        "mh": [], "jt": [], "pz": [], "rn": []
    }
    ct = [0, 0]
    for i in range(100000 if LEVEL == 2 else 1000):
        special_ct = {
            "mh": 0, "jt": 0, "pz": 0, "rn": 0
        }
        q = collections.deque()
        q.append(("broadcaster", 0, "button"))
        while q:
            name, pulse, par = q.popleft()
            ct[pulse] += 1
            if pulse == 0 and par in special_ct:
                special_ct[par] += 1
            if mtype[name] == "broadcaster":
                to_send = pulse
            elif mtype[name] == '%':
                if pulse == 0:
                    state[name] ^= 1
                    to_send = state[name]
                else:
                    continue
            elif mtype[name] == '&':
                state[name][par] = pulse
                if all([x == 1 for x in state[name].values()]):
                    to_send = 0
                else:
                    to_send = 1
            else:
                assert state[name] is None, state[name]
                continue

            for dest in modules[name]:
                q.append((dest, to_send, name))

        for k, v in special_ct.items():
            if v > 0:
                instances[k].append(i)

    ans2 = 1
    if LEVEL == 2:
        for k, v in instances.items():
            period = v[-1] - v[-2]
            assert period == v[-2] - v[-3]
            ans2 *= period

    ans1 = ct[0] * ct[1]

    # for i in range(N):

    if LEVEL == 1:
        return ans1
    else:
        return ans2


def main():
    # with open("sample.txt") as sample_file:
    #     sample_input = sample_file.read().strip('\n')
    # sample_answer = solve(sample_input)
    # print("Answer for sample:", sample_answer)
    # assert sample_answer == SAMPLE_ANSWER and sample_answer is not None, f"Got {sample_answer} instead of {SAMPLE_ANSWER}"

    with open("input.txt") as input_file:
        inp = input_file.read().strip('\n')
    answer = solve(inp)
    print("Answer:", answer)
    assert submit_answer(2023, 20, LEVEL, answer) is True


if __name__ == '__main__':
    main()
