def area(rectangles):
    pass


# Do not modify below this line
tests = int(input().strip())
for test in range(tests):
  n = int(input().strip())
  rectList = []
  for _ in range(n):
    currRect = input().strip().split(' ')
    newRect = []
    for pos in currRect:
      newRect.append(int(pos))
    rectList.append(newRect)
  print(area(rectList))
