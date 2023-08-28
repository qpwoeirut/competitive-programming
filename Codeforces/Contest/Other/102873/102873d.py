inp = input()
A, S = inp.split()
A = int(A)
S = int(S)
B = str(S - A)
A = str(A)

A = ''.join(sorted(A))
B = ''.join(sorted(B))

if A == B:
    print("YES")
else:
    print("NO")

