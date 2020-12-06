lo = 123257
hi = 647015
nums = []


def to_int(lst: list):
    num = 0
    mult = 1
    for d in reversed(lst):
        num += mult * d
        mult *= 10
    return num


def adj1(num: list):
    for i in range(1, len(num)):
        if num[i - 1] == num[i]:
            return True
    return False


def adj2(num: list):
    for i in range(1, len(num)):
        if num[i-1] == num[i] and (i == 1 or num[i-2] != num[i]) and (i+1 == len(num) or num[i] != num[i+1]):
            return True
    return False


def gen(num: list):
    print(num)
    if len(num) == 6:
        n = to_int(num)
        # print(n)
        if n < lo or n > hi:
            return

        # if adj1(num) is True:
        if adj2(num) is True:
            print(n)
            nums.append(n)

        return

    for d in range(10):
        if num[-1] > d:
            continue

        gen(num + [d])


for digit in range(1, 10):
    gen([digit])

nums = sorted(nums)
print(nums)
print(len(nums))