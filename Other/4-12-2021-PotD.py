from itertools import product
from string import ascii_lowercase as alphabet


# using file i/o since multi-line standard input is impossible to test i think
with open("in.txt", "r") as f:
    s = f.read()


res = ""
idx = 0
num = 0
capital = False
for char in s:
    if char in "BESIbesi":
        if idx == 0:
            capital = char.isupper()
        else:
            num *= 2
            if char.isupper():
                num += 1

        idx += 1
        if idx == 6:
            c = alphabet[num - 1]
            if capital:
                c = c.upper()
            res += c
            idx = 0
            num = 0
    else:
        res += char

with open("out.txt", "w") as f:
    f.write(res + '\n')

