def testing(bears, testtime, totaltime):
    pass

while True:
    s = input().strip()
    if s == '':
        break
    for i in range(int(s)):
        sa = input().strip().split(" ")
        print(testing(int(sa[0]), int(sa[1]), int(sa[2])))
    break
