def solve(n, grid):
    # Calculate the permutation of columns
    col_perm = sorted([(grid[0][c], c) for c in range(n)])
    
    # Check for duplicate elements in the first row
    for c in range(1, n):
        if col_perm[c-1][0] == col_perm[c][0]:
            print 'N'
            return
    
    # Make sure all other rows are also sorted
    for r in range(1, n):
        for c in range(1, n):
            if grid[r][col_perm[c-1][1]] >= grid[r][col_perm[c][1]]:
                print 'N'
                return
    
    # Now do the exact same for the permutation of rows
    row_perm = sorted([(grid[r][0], r) for r in range(n)])
    for r in range(1, n):
        if row_perm[r-1][0] == row_perm[r][0]:
            print 'N'
            return

    for c in range(1, n):
        for r in range(1, n):
            if grid[row_perm[r-1][1]][c] >= grid[row_perm[r][1]][c]:
                print 'N'
                return
    
    # Otherwise, the grid is sortable
    print 'Y'

n = int(raw_input())
grid = [map(int, raw_input().split()) for _ in range(n)]
solve(n, grid)
