from functools import reduce
from itertools import combinations

N = int(input())
A = [2, 3, 5, 7]
ans = N
for ct in range(1, len(A) + 1):
    for comb in combinations(A, r=ct):
        p = reduce(lambda x, y: x*y, comb, 1)
        if ct % 2 == 0:
            ans += N // p
        else:
            ans -= N // p
print(ans)


#ans = 0
#for i in range(1, N+1) :
#    div = True
#    for a in A:
#        if i % a == 0:
#            div = False
#            break
#    if div:
#        ans += 1
#print(ans)

