nums = []

with open("day1.txt", 'r') as f:
    for line in f:
        nums.append(int(line))

for a in nums:
    for b in nums:
        for c in nums:
            if a + b + c == 2020:
                print(a * b * c)
