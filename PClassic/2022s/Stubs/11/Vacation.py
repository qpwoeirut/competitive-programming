import sys

def vacation(n, q, trees, queries): 
    #your code here
    pass

#DO NOT MODIFY BELOW THIS LINE
#n, m, q, grid, queries
if __name__ == "__main__":
    nq = input().split(" ")
    n = int(nq[0])
    q = int(nq[1])
    
    trees = []
    queries = []
    
    for i in range(n):
        r = input().strip().split()
        row = [int(x) for x in r]
        trees.append(row)
        
    for i in range(q):
        r = input().strip().split()
        lr = [int(x) for x in r]
        queries.append(lr)

    print(trees)
    print(queries)
        
    results = vacation(n, q, trees, queries)
    for result in results:
        print(result)
