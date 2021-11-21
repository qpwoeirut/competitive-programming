
def find_triples(a):
    a.sort()
    f = [None] * len(a)  # frequencies of each value
    f[0] = 1

    v = a[0]  # current value whose frequency is being evaluated
    i = 0  # current index of v's count in f

    for j in range(1, len(a)):
        if a[j] == v:
            f[i] += 1
        else:
            i += 1
            v = a[j]
            f[i] = 1

    sum = [None] * (i + 1)
    square_sum = [None] * (i + 1)
    sum[i] = f[i]
    square_sum[i] = f[i]**2
    for j in range(i - 1, -1, -1):
        sum[j] = sum[j + 1] + f[j]
        square_sum[j] = square_sum[j + 1] + f[j]**2


    ans = 0.0
    for j in range(i - 1):
        ans = (ans + (f[j] * (sum[j + 1]**2 - square_sum[j + 1]) / 2)) % 1000000007

    return int(ans)


# Do not modify below this line
if __name__ == '__main__':

    with open('StudyingMagicIN.txt', 'r') as f:

        for line in f:
            if line == '':
                break

            a = [int(x) for x in line.split(' ')]
            print(find_triples(a))
