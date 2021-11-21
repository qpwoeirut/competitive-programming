# -*- coding: utf-8 -*-
def solve(n):
    ret = ""
    while n > 0:
        if n >= 1000:
            ret = ret + 'M'
            n = n - 1000
            continue
        if (n // 100) % 10 == 9:
            ret = ret + 'CM'
            n = n - 900
            continue
        if n >= 500:
            ret = ret + 'D'
            n = n - 500
            continue
        if (n // 100) % 10 == 4:
            ret = ret + 'CD'
            n = n - 400
            continue
        if n >= 100:
            ret = ret + 'C'
            n = n - 100
            continue
        if (n // 10) % 10 == 9:
            ret = ret + 'XC'
            n = n - 90
            continue
        if n >= 50:
            ret = ret + 'L'
            n = n - 50
            continue
        if (n // 10) % 10 == 4:
            ret = ret + 'XL'
            n = n - 40
            continue
        if n >= 10:
            ret = ret + 'X'
            n = n - 10
            continue
        if n % 10 == 9:
            ret = ret + 'IX'
            n = n - 9
            continue
        if n >= 5:
            ret = ret + 'V'
            n = n - 5
            continue
        if n % 5 == 4:
            ret = ret + 'IV'
            n = n - 4
            continue
        if n >= 1:
            ret = ret + 'I'
            n = n - 1
            continue
    return ret


# Do not modify below this line
if __name__ == '__main__':
    with open('RomanIN.txt', 'r') as f:
        tests = int(f.readline())
        for i in range(tests):
            s = int(f.readline())
            print(solve(s))
