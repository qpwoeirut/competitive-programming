from math import log, floor


n = int(input())
#n = 6 ** 642548 - 1

if n == 0:
    print(1)
else:
    x = floor(log(n, 6)) - 1
    a = 6 ** x
    b = a * 6
    c = b * 6
    if n < a:
        print(x)
    elif n < b:
        print(x + 1)
    elif n < c:
        print(x + 2)
    else:
        print(x + 3)

