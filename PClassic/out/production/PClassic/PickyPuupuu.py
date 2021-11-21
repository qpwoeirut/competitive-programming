def magicSquare(grid):
    pass

tests = int(input().strip())
for test in range(tests):
    grid = []
    while True:
        s = input().strip()
        if s == '':
            break
        row = s.split(" ")
        row = list(map(int, row))
        grid.append(row)
    if magicSquare(grid):
        print("true")
    else:
        print("false")
