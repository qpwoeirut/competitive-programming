def terrifyingTetra(ps):
    pass

# Do not modify below this line
if __name__ == '__main__':
    tests = int(input())
    for test in range(tests):
        points = [[0, 0, 0] for _ in range(4)]
        for i in range(4):
            point = input()
            split = point.split()
            for j in range(3):
                points[i][j] = float(split[j])
        output = terrifyingTetra(points)
        s = ""
        for i in range(len(output)):
            s += str(round(output[i] * 10.0) / 10.0) + " "
        print(s[:-1])