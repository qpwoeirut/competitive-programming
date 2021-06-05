from fractions import gcd
def lcm(a,b):
    return b*(a//gcd(a,b))
def flcm(a,b):
    #lcm of fractions a[0]/a[1] and b[0]/b[1]
    d=lcm(a[1],b[1])
    n=lcm(a[0]*(d//a[1]),b[0]*(d//b[1]))
    g=gcd(n,d)
    d,n = d//g, n//g
    return [n,d]
n=int(input())
L=list(map(int,input().split()))
M=[]
#for periods L[0] and L[i],
#the distance between them increases at 1/L[0] - 1/L[i] = L[i]-L[0] / L[i]*L[0]
#so they're in line after (the reciprocal) days 
for i in range(1,n):
    a=L[i]*L[0]
    b=abs(L[i]-L[0])
    g=gcd(a,b)
    a,b = a//g, b//g
    M.append([a,b])
#print(M)
#take the lcm of these fractions
ans=M[0]
for i in range(1,len(M)):
    ans=flcm(ans,M[i])
print(ans[0],ans[1])

