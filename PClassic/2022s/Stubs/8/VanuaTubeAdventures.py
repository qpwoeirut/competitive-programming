def tubeAdventures(n, m, q, islands, queries): 
    #your code here
    pass

#DO NOT MODIFY BELOW THIS LINE
#n, m, q, grid, queries
if __name__ == "__main__":
    tests = int(input())
    for i in range(tests):
        nmq = input().split(" ")
        n = int(nmq[0])
        m = int(nmq[1])
        q = int(nmq[2])
        islands = []
        queries = []
        for i in range(n):
            row = input().strip()
            islands.append(row)
        for i in range(q):
            queries.append(int(input().strip()))
        results = tubeAdventures(n, m, q, islands, queries)
        for result in results:
            print(result)