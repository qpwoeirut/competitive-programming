# from collections import *
# from itertools import *
# from math import *
from collections import deque
from math import gcd

from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [10605, 2713310158]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def lcm(nums):
    if len(nums) == 1:
        return nums[0]
    x = nums[0]
    y = lcm(nums[1:])
    return x*y // gcd(x, y)


def solve(s: str) -> int or str:
    # A = list(s)
    # A = list(map(int, s.split(',')))
    A = [line for line in s.split('\n')]
    # A = [line for line in s.split('\n')]
    # A = [list(map(int, line)) for line in s.split('\n')]

    N = len(A)

    items = []
    oper = []
    second = []
    test = []
    next_t = []
    next_f = []

    for i in range(N):
        s = A[i].strip()
        if s.startswith("Monkey") or s == "":
            continue
        elif s.startswith("Starting"):
            sp = s.replace(',', '').split()[2:]
            items.append(deque(map(int, sp)))
        elif s.startswith("Operation"):
            op = s.replace("old", "x").split()[3:]
            assert op[0] == "x"
            oper.append(op[1])
            second.append("x" if op[2] == "x" else int(op[2]))
        elif s.startswith("Test"):
            n = int(s.split()[-1])
            test.append(n)
        elif s.startswith("If true"):
            n = int(s.split()[-1])
            next_t.append(n)
        elif s.startswith("If false"):
            n = int(s.split()[-1])
            next_f.append(n)
        else:
            assert False

    M = len(items)
    count = [0 for _ in range(M)]

    ROUNDS = 20 if LEVEL == 1 else 10000
    MOD = lcm(test)
    print(MOD)

    for i in range(ROUNDS):
        # print(i)
        for m in range(M):
            # print("MONKE", m)
            while items[m]:
                count[m] += 1
                cur = items[m].popleft()
                x = cur if second[m] == "x" else second[m]
                # print(cur, x)
                if oper[m] == "+":
                    cur += x
                elif oper[m] == "*":
                    cur *= x
                # print(cur)
                if LEVEL == 1:
                    cur //= 3
                # print(cur, '\n')
                cur %= MOD
                if cur % test[m] == 0:
                    items[next_t[m]].append(cur)
                else:
                    items[next_f[m]].append(cur)

        # print(count)
    a, b = sorted(count)[-2:]
    return a * b


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
    assert submit_answer(2022, 11, LEVEL, answer) is True


if __name__ == '__main__':
    main()
