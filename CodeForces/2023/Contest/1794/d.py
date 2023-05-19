N = 2022
with open("d.txt", "w+") as f:
    f.write(str(N) + "\n")
    f.write(' '.join([str(i+1) for i in range(2*N)]))
        
