"""
ID: zhongbr1
LANG: PYTHON3
TASK: test
"""
for line in open('test.in'):
    x = line.split(' ')[0]
    y = line.split(' ')[1]
    sum = int(x) + int(y)
    print(sum)
    fout = open('test.out', 'a')
    fout.write(str(sum) + '\n')
    fout.close()
