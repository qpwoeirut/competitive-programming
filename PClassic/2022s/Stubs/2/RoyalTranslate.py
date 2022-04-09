# Implement the following method
def translate(message, map):
  pass


# Do not modify below this line
if __name__ == '__main__':
  tests = int(input().strip())
  for _ in range(tests):
    # Parse string
    message = input().strip()
    # Parse map
    map = {}
    mappingCount = int(input().strip())
    for _ in range(mappingCount):
      mapping = input().strip().split(' ')
      map[mapping[0]] = mapping[1]
    print(translate(message, map))
