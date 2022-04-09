def superhero(n, bff):
    pass
                

# Do not modify below this line
if __name__ == '__main__':
    tests = int(input())
    for test in range(tests):
        n = int(input())
        bff = []
        for i in range(n):
            bff.append(int(input()))
        print(superhero(n, bff))