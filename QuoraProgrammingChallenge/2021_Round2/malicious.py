with open("training_data.txt") as f:
    data = []
    bools = []
    for idx, line in enumerate(f):
        if idx == 0:
            K, D, M = map(int, line.split())
        elif idx <= K:
            data.append(line)
        else:
            bools.append(line.strip() == '1')

with open("malicious.txt", 'w') as f:
    for i in range(M):
        f.write(data[i])
    for i in range(M):
        f.write(str(int(not bools[i])) + '\n')