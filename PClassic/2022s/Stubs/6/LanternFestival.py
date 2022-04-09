def lanternFestival(n, prefs):
    return -1;

if __name__ == '__main__':
    tests = int(input())
    for test in range(tests):
        n = int(input())
        numEdges = int(input())
        prefs = []
        for e in range(numEdges):
            line = input().split()
            prefs.append([int(line[0]), int(line[1])])
        res = lanternFestival(n, prefs)
        for v in res:
            print(v)
