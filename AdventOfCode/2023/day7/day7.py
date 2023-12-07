# from collections import *
# from itertools import *
# from math import *
from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [6440, 5905]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def score(s):
    st = set(s)
    if 'J' in st and LEVEL == 2:
        st.remove('J')
    counts = [s.count(a) for a in st]
    jokers = s.count('J') if LEVEL == 2 else 0

    if jokers == 5:
        return 6

    if max(counts) + jokers == 5:
        return 6
    if max(counts) + jokers == 4:
        return 5
    if max(counts) + jokers == 3:
        if len(counts) == 2:
            return 4
        return 3
    if max(counts) + jokers == 2:
        if jokers == 0:
            if counts.count(2) == 2:
                return 2
            if counts.count(2) == 1:
                return 1
        else:
            assert jokers == 1
            assert counts.count(2) == 0
            return 1
    return 0


card = {
    "A": 14,
    "K": 13,
    "Q": 12,
    "T": 11,
    "J": 1
}
for d in range(10):
    card[str(d)] = d
def cards(s):
    return [card[x] for x in s]


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    A = [line for line in input_string.split('\n')]
    # A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line)) for line in input_string.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    # M = len(A[0])

    ans1 = 0
    ans2 = 0
    things = []
    for i in range(N):
        hand, bid = A[i].split()
        bid = int(bid)
        things.append((hand, bid))
    things.sort(key = lambda t: (score(t[0]), cards(t[0])), reverse=True)
    print(things)

    i = len(things)
    for hand, bid in things:
        ans1 += i * bid
        print(hand, i)
        i -= 1

    # for i in range(N):

    return ans1


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
    assert submit_answer(2023, 7, LEVEL, answer) is True


if __name__ == '__main__':
    main()
