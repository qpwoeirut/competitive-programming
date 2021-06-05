
n=int(input())
edges={}
verts=[]
for i in range(26):
    for j in range(26):
        verts.append(chr(97+i)+chr(97+j))
asd=input().split()
x=int(asd[0])

for i in range(x):
    bigram=input()
    verts.remove(bigram)
for x in verts:
    edges[x]=[]
    for y in verts:
        if x[1]==y[0]:
            edges[x].append(y)
y=int(asd[1])
for i in range(y):
    trigram=input()
    if trigram[:2] in verts and trigram[1:] in verts:
        edges[trigram[0:2]].remove(trigram[1:])

edges['s']=list(edges)
inStack,vis,par={},{},{}
for k in edges:
    inStack[k]=False
    vis[k]=False

cycle=""

def dfs(now):
    inStack[now]=True
    vis[now]=True
    for nex in edges[now]:
        if inStack[nex]:
            asd=now
            global cycle
            cycle=asd
            while asd!=nex:
                asd=par[asd]
                cycle=asd[0]+cycle
            return True
        elif not vis[nex]:
            par[nex]=now
            if dfs(nex):
                return True
    inStack[now]=False
    return False

mem={}
trans={}
def DP(now):
    if now in mem:
        return mem[now]
    ans=0
    trans[now]=now
    for nex in edges[now]:
        if DP(nex)>ans:
            trans[now]=nex
            ans=DP(nex)
    mem[now]=ans+1
    return ans+1
if dfs('s'):
    cycle=cycle[:-1]
    print(1)
    for i in range(n):
        print(cycle*(n//len(cycle))+cycle[:n%len(cycle)])
        cycle=cycle[1:]+cycle[0]
else:
    ans=DP('s')
    if ans>=2*n-1:
        asd=trans['s']
        path=asd
        while trans[asd]!=asd:
            asd=trans[asd]
            path+=asd[1]
        path=path[:2*n-1]
        print(1)
        for i in range(n):
            print(path[i:i+n])
    else:
        print(0)
              
