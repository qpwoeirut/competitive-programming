#https://cses.fi/problemset/hack/1755/entry/659199/


bind = []
unbind = []
for c in input():
    if unbind.count(c)==1:
        unbind.remove(c)
        bind.append(c)
    elif unbind.count(c)==0:
        unbind.append(c)
    else:
        print("ERROR")
 
#print(unbind)
 
if len(unbind)>1:
    print("NO SOLUTION")
elif len(unbind)==1:
    res =""
    for c in bind:
        res+=c
    res+=unbind[0]
    for c in reversed(bind):
        res+=c
    print(res)
else:
    res =""
    for c in bind:
        res+=c
    for c in reversed(bind):
        res+=c
    print(res)
