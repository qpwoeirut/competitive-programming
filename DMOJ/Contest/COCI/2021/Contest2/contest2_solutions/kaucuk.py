n = int(input())
c = [0]*3
for i in range(n):
    level, label = input().split()
    level = level.count('sub')
    c[level] += 1
    for i in range(level+1):
        if i != 0:
            print(".", end='')
        print(c[i], end='')
    print(" " + label)
    for i in range(level+1, 3):
        c[i] = 0
