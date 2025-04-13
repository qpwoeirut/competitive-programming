s = ["XX", "XX 90"]

while sum(len(l) for l in s) + len(s) <= 100:
    s.append("1 1")
s.pop()

W = len(s)
s[0] = str(W)
s[1] = f"{W} 99"
s.append(s.pop(1))

with open("sol/b1.out", 'w') as f:
    f.write('\n'.join(s))
