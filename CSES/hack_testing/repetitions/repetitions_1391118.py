# https://cses.fi/problemset/hack/1069/entry/1391118/

# acacac
_input = input()
arr = [0] * 91
a,c,t,g = 1,1,1,1
for i in range(len(_input)-1):
  if _input[i] == 'A' and _input[i+1] == 'A':
    a += 1
    g = 1
    c = 1
    t = 1
    arr[ord(_input[i])]  = max(arr[ord(_input[i])], a)
 
  elif _input[i] == 'C' and _input[i+1] == 'C':
    c += 1
    a = 1
    g = 1
    t = 1
    arr[ord(_input[i])]  = max(arr[ord(_input[i])], c)
 
  elif _input[i] == 'T' and _input[i+1] == 'T':
    t += 1
    a = 1
    c = 1
    g = 1
    arr[ord(_input[i])]  = max(arr[ord(_input[i])], t)
 
  elif _input[i] == 'G' and _input[i+1] == 'G':
    g += 1
    a = 1
    c = 1
    t = 1
    arr[ord(_input[i])]  = max(arr[ord(_input[i])], g)
 
  else:
    g = 1
    a = 1
    c = 1
    t = 1
 
print(max((max(arr), 1)))
