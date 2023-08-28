N = int(5e5)
MX = int(1e7)
DIV = 12
start = MX - (N*DIV)
assert start > 0, start

print(N)
nums = [str(((n-1) // DIV) * DIV) for n in range(start, MX, DIV)]
# nums = ['0'] * N

assert len(nums) == N, len(nums)
print(' '.join(nums))
