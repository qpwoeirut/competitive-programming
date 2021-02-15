s = input()

for letter in "abcdefghijklmnopqrstuvwxyz":
    s = s.replace(letter, ' ')

nums = [int(x) for x in s.split() if len(x) > 0]
print(len(set(nums)))
