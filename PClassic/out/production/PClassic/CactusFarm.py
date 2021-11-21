def matchable(initialPattern, finalPattern):
    return False

# Do not modify below this line

line1 = input()
testCases = int(line1.split()[0])
for i in range(0, testCases):
    s = input()
    t = input()
    res = matchable(s, t)
    if res:
        print('1')
    else:
        print('0')