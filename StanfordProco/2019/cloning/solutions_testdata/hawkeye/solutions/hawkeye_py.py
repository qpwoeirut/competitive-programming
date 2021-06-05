n=int(raw_input())
L=list(map(int,raw_input().split()))
ans=0
while len(L)>1:
    L.sort()
    x=L[0]
    y=L[1]
    L=L[2:]
    L.append(x+y)
    ans+=x+y
print(ans)
