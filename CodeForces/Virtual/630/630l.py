N = input()
N = int(N[0] + N[2] + N[4] + N[3] + N[1])
N = pow(N, 5, 100000)
print(str(N).rjust(5, '0'))

