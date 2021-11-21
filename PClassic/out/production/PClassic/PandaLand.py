def pandaLand(n, m, s):
    return 0

# Do not modify below this line
line1 = input()
testCases = int(line1.split()[0])
for i in range(0, testCases):
    inp = input().strip().split()
    n = int(inp[0])
    m = int(inp[1])
    path = input().strip()
    print(pandaLand(n, m, path))

