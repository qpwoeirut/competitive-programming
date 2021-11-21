def solve (n, arr):
    prefix = {}
    prefixxor = []
    prefixxor.append(arr[0])
    l0 = []
    l1 = []
    total = 0
    if prefixxor[0] == 0:
        l0.append(-1)
        l0.append(0)
        prefix[0] = l0
    else:
        l0.append(0)
        l1.append(-1)
        prefix[prefixxor[0]] = l0
        prefix[0] = l1
    for i in range(1, n):
        prefixxor.append(prefixxor[i - 1] ^ arr[i])
        if (prefixxor[i] in prefix):
            prefix.get(prefixxor[i]).append(i)
        else:
            l = [i]
            prefix[prefixxor[i]] = l
    for i in list(prefix):
        l = prefix[i]
        size = len(l)
        count = - size + 1
        for j in range(size):
            total += l[j] * count
            count += 2
        total -= (size * (size - 1)) / 2
    return int(total)
    
if __name__ == '__main__':
    with open('XORIN.txt', 'r') as f:
        t = int(f.readline().strip())
        l = []
        while t > 0:
            n = int(f.readline().strip())
            temp = n
            l = []
            while temp > 0:
                l.append(int(f.readline().strip()))
                temp = temp - 1
            print(solve(int(n), l))
            t = t - 1


        
    
    


