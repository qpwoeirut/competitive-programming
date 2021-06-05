n=int(input())
s=input()
k=-1
cnt=0
for i in range(n):
    if int(s[i])!=k:
        cnt+=1
        k=int(s[i])
if s[0]=='0':
    cnt-=1
print(cnt//2)
        
        
