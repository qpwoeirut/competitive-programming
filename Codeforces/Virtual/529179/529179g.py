import operator

equation = input().split()

a, op_s, b, eq, c = equation

assert eq == '='
op = operator.mul if op_s == '*' else operator.add

for i in range(1, len(a)):
    for j in range(1, len(b)):
        ia = int(b[:j] + a[i:])
        ib = int(a[:i] + b[j:])

        if op(ia, ib) == int(c):
            print(ia, op_s, ib, '=', c)
            exit(0)

for i in range(1, len(a)):
    for k in range(1, len(c)):
        ia = int(c[:k] + a[i:])
        ic = int(a[:i] + c[k:])

        if op(ia, int(b)) == ic:
            print(ia, op_s, b, '=', ic)
            exit(0)

for j in range(1, len(b)):
    for k in range(1, len(c)):
        ib = int(c[:k] + b[j:])
        ic = int(b[:j] + c[k:])

        if op(int(a), ib) == ic:
            print(a, op_s, ib, '=', ic)
            exit(0)

