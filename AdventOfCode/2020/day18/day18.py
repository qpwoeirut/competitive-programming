# from math import *
# from itertools import *
# from math import *

ans = 0
ans2 = 0

with open("input.txt") as file:
    A = [line.strip() for line in file]
    # A = [int(line.strip()) for line in file]

N = len(A)


# M = len(A[0])

def f(s):
    print(s)
    while '(' in s:
        p1 = s.rfind('(')
        p2 = s.find(')', p1)
        s = s[:p1] + ' ' + str(f(s[p1 + 1:p2])) + ' ' + s[p2 + 1:]

    s = s.split()

    exp = [s[0]]
    for i in range(1, len(s)):
        if s[i - 1] == '+':
            exp.pop()
            exp[-1] = str(int(exp[-1]) + int(s[i]))
        else:
            exp.append(s[i])

    return eval(' '.join(exp))


for i in range(0, N):
    a = A[i]

    ans += f(a)

print("ans1:", ans)
print("ans2:", ans2)
