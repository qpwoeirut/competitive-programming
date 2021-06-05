t=int(input())
N=1000001
sieve=[1]*N
primes=[]
for i in range(2,N):
    if sieve[i]==1:
        primes.append(i)
        for j in range(i,((N-1)//i)+1):
            sieve[i*j]=0
            
for ca in range(t):
    x=int(input())
    if x==1:
        print(4,8)
    else:
        n,m=1,1
        for p in primes:
            e=0
            while x%p==0:
                e+=1
                x//=p
            if e!=0:
                a,b=1,1
                if e<3:
                    a,b=e,e
                else:
                    b=e%3
                    a=(2*b+e)//3
                n*=p**a
                m*=p**b
        if x!=1:
            n*=x
            m*=x
        if n==m:
            n*=4
            m*=8
        print(n,m)
