import itertools


win = {"": None}
lose = set()


def solve(s):
    s = s.lstrip('0').rstrip('1')
    if s in win:
        return True
    elif s in lose:
        return False

    min_len = len(s) + 1
    for r in range(2, len(s) + 1):
        for combo in itertools.combinations(range(len(s)), r):
            t = list(s)
            for i, v in zip(combo, sorted(s[i] for i in combo)):
                t[i] = v
            t = ''.join(t)
            if s != t and solve(t) is False:
                t = t.lstrip('0').rstrip('1')
                if len(t) < min_len:
                    min_len = len(t)
                    win[s] = t
    if s in win:
        return True

    lose.add(s)
    return False



for i in range(1 << 10):
    s = bin(i)[2:]
    if s[0] == '1' and s[-1] == '0':
        res = solve(s)
        print(s, res)

# for s in sorted(win.items()): print('W', s)
# for s in sorted(lose): print('L', s)

print(len(set(win.values())), len(lose))

