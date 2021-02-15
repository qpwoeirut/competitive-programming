# https://cses.fi/problemset/hack/1755/entry/1436878/

arr = list(input())
n = len(arr)
ans = list()
li = list()
for i in range(n):
    if arr[i] in li:
        ans.append(arr[i])
        li.remove(arr[i])
    else:
        li.append(arr[i])
#print(ans,li)
if n%2==0:
    if len(ans)*2!=n:
        print("NO SOLUTION")
    else:
        for i in ans:
            print(i,end="")
        for i in range(len(ans)-1,-1,-1):
            print(ans[i],end="")
else:
    if len(li)!=1:
        print("NO SOLUTION")
    else:
        for i in ans:
            print(i,end="")
        print(li[0],end="")
        for i in range(len(ans)-1,-1,-1):
            print(ans[i],end="")

