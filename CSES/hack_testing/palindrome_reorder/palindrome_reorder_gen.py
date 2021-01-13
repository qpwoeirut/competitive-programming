chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
chars2 = ''.join([c+c for c in chars])

assert len(chars) == 26
assert len(chars2) == 52

N = int(1e6)
s = chars + ''.join([chars2 for _ in range(1, N // len(chars2))]) + chars
print(len(s))

s = s.ljust(N, 'Z')

with open("palindrome_reorder_all_chars.txt", 'w') as f:
    f.write(s + '\n')

print(len(s))
