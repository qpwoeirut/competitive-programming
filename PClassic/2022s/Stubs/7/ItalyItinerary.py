# Implement the following method
def maximizeFun(itinerary):
  pass


# Do not modify below this line
if __name__ == '__main__':
  tests = int(input().strip())
  for _ in range(tests):
    numLocations = int(input().strip())
    arr = [[0 for _ in range(2)] for _ in range(numLocations)]
    for i in range(numLocations):
        pair = input().strip().split(" ")
        arr[i] = [int(pair[0]), int(pair[1])]
    print(maximizeFun(arr))
