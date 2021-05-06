# https://codereview.stackexchange.com/questions/42524/solving-the-reves-puzzle
def frame_stewart(ndisks,npegs):
    if ndisks == 0 or npegs == 1:
        return 0
    if ndisks == 1:
        return 1
    if npegs == 3: #3 pegs is well defined optimal solution of 2^n-1
        return 2 ** ndisks - 1
    if npegs >= 3 and ndisks > 0:
        potential_solutions = (2 * frame_stewart(kdisks,npegs) + frame_stewart(ndisks-kdisks,npegs-1) for kdisks in range(1,ndisks))
        return min(potential_solutions) #the best solution

    return float('inf')

n, k = map(int, input().split())
print(frame_stewart(n, k))

