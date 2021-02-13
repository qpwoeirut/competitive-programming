N = int(input())

for i in range(N):
    s = input()
    if s.startswith("Simon says"):
        print(s[11:])

