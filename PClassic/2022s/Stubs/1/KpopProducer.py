def danceCommand(s, arr):
    pass


# Do not modify below this line
if __name__ == "__main__":
    tests = int(input())
    for test in range(tests):
        s = input()
        length = int(input().strip())
        arr = input().strip().split(' ')
        for i in range(length):
            arr[i] = int(arr[i])
        output = danceCommand(s, arr)
        print(output)
