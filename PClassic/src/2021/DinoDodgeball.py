def netTemperature(n, temperatures):
    pass

line1 = input()
t = int(line1.split()[0])
for case in range(t):
    line = input()
    args = line.split()
    n = int(args[0])
    k = int(args[1])
    
    temperatures = []
    for i in range(0, k):
        triple = input()
        tripleargs = triple.split()
        ballThrown = [int(tripleargs[0]), int(tripleargs[1]), int(tripleargs[2])]
        temperatures.append(ballThrown)
    
    res = netTemperature(n, temperatures)
    print(res)

