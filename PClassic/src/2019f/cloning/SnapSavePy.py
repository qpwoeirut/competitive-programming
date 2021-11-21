def find_peak(a):

    for i in range(len(a) - 1):
        if a[i] >= a[i+1] and a[i] >= a[0]:
            return i

    return len(a) - 1


# Do not modify below this line
if __name__ == '__main__':

    with open('SnapSaveIN.txt', 'r') as f:

        for line in f:
            if line == '':
                break

            a = [int(x) for x in line.split(' ')]
            print(find_peak(a))
