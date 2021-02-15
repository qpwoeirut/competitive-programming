from scipy.stats import linregress


def solve(filename):
    with open(filename) as file:
        X = []
        Y = []
        for idx, line in enumerate(file):
            if idx == 0:
                N = int(line)
            else:
                line = line.strip()
                x, y = line.split()
                X.append(float(x))
                Y.append(float(y))

    ans = linregress(X, Y)
    print(ans.slope, ans.intercept, sep=',')


solve("test1.in")
solve("test2.in")
solve("test3.in")
