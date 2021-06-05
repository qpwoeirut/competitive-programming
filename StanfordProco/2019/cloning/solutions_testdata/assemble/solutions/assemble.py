s=input()
freq={}
for i in range(len(s)):
    if s[i] in freq:
        freq[s[i]]+=1
    else:
        freq[s[i]]=1
most=0
pick='a'
for k in freq:
    if freq[k]>most:
        most=freq[k]
        pick=k
print(pick)
print(s)
