def checkMessages(s, t):
  pass


# Do not modify below this line
tests = int(input().strip())
for tests in range(tests):
    s = input().strip()
    t = input().strip()
    if checkMessages(s, t):
        print("yes")
    else:
        print("no")
