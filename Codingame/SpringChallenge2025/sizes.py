with open("sizes.txt") as f:
    s = f.read().strip().split('\n\n')

assert len(s) == 6, len(s)

nums = [list(map(int, lines.split('Compiled!\n')[1].strip().split()[1:])) for lines in s]
print(nums)

assert all(len(x) == 41 for x in nums), [len(x) for x in nums]

sizes = [max(t) for t in zip(*nums)]
print(*sizes, sep='\n')

print(sum(sizes))
