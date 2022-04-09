import math

def efficientTrip(mountainList):
    return True


if __name__ == '__main__':
    tests = int(input())
    for test in range(tests):
        length = int(input())
        line = input().split()
        mountainList = []
        for e in line:
            mountainList.append(int(e))
        res = efficientTrip(mountainList)
        if res:
            print(1)
        else:
            print(0)

