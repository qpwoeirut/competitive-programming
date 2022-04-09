def fillMosaic(gridWidth, gridHeight):
    grid = [['.']]
    return grid

# Do not modify below this line
def printMosaic(grid):
    for i in range(len(grid)):
        for j in range(len(grid[0])):
            print(grid[i][j], end="")
        print()
    return

if __name__ == '__main__':
    tests = int(input())
    for test in range(tests):
        line = input().split()
        printMosaic(fillMosaic(int(line[0]), int(line[1])))