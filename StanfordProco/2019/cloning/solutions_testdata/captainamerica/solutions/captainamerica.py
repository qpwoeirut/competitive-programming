q=int(input())
M={}
count=0
for i in range(1,q+1):
    asd=input().split()
    u,v=int(asd[1]),int(asd[2])
    if u>v:
        u,v=v,u
    M[(u,i)]=set()
    M[(v,i)]=set()
    if asd[0]=='0':
        if (u,v) in M:
            M[(u,v)].add(i)
            M[(u,i)].add(v)
            M[(v,i)].add(u)
            count+=1
    else:
        if (u,v) in M:
            #destroy all triangles with (u,v)
            for x in M[(u,v)]:
                M[(min(u,x),max(u,x))].remove(v)
                M[(min(v,x),max(v,x))].remove(u)
            count-=len(M[(u,v)])
            del M[(u,v)]
    #print(M)
    print(count)
