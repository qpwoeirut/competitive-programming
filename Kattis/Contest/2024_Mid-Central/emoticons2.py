S = input().strip()

def emote_of(s):
    for emote in [":)", ":-)", ":-(", ";-)", "xD", "^_^", "-_-", "^o^", "^^;", "(..)"]:
        if s.endswith(emote):
            return emote
    return None

def calc(c0, c1):
    res = ""
    for c in S:
        if c == c0:
            c = c1

        res += c
        em = emote_of(res)
        if em:
            res = res[:-len(em)] + '!'
    return len(res)

lo = len(S)
hi = 0
for c0 in range(32, 127):
    for c1 in range(32, 127):
        L = calc(chr(c0), chr(c1))
        lo = min(lo, L)
        hi = max(hi, L)

print(lo, hi)
