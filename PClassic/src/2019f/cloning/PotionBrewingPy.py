# -*- coding: utf-8 -*-
def getNumOfPotions(n, k):
    mod = 100000007
    arr = [0] * (n+1)
    arr[0] = 1
    num = 0
    for i in range(1, n+1):
        arr[i] += arr[i-1]
        if i - k >= 0:
            num = arr[i - k]
            arr[i] = arr[i] + num 
            arr[i] = (arr[i] % mod)
        if i - k < 0:
            arr[i] += 1
    return arr[n]


# Do not modify below this line
if __name__ == '__main__':
   # out = open('PotionBrewingOUT.txt', 'w')
    with open('PotionBrewingIN.txt', 'r') as f:
        line = f.readline().strip()
        while line != "":
            numbers = line.split(" ")
            days = int(numbers[0])
            wizards = int(numbers[1])
            num = getNumOfPotions(days, wizards)
            #out.write('\n'.str(num))
            print(num)
            line = f.readline().strip()

