from collections import defaultdict

n, m = map(int, input().split())

grid = [list(map(int, input().split())) for _ in range(n)]

diag_main = defaultdict(set)
diag_anti = defaultdict(set) 
values = []
for r in range(n):
    for c in range(m):
        if grid[r][c] > 0:
            diag_main[r - c].add(grid[r][c])
            diag_anti[r + c].add(grid[r][c])
            values.append(grid[r][c])

values.sort()

i = 0
main_fwd = 0
for k in sorted(diag_main.keys()):
    sz = len(diag_main[k])
    target = set(values[i : i + sz])
    main_fwd += len(diag_main[k] - target)
    i += sz

i = 0
main_rev = 0
for k in sorted(diag_main.keys(), reverse=True):
    sz = len(diag_main[k])
    target = set(values[i : i + sz])
    main_rev += len(diag_main[k] - target)
    i += sz

i = 0
anti_fwd = 0
for k in sorted(diag_anti.keys()):
    sz = len(diag_anti[k])
    target = set(values[i : i + sz])
    anti_fwd += len(diag_anti[k] - target)
    i += sz

i = 0
anti_rev = 0
for k in sorted(diag_anti.keys(), reverse=True):
    sz = len(diag_anti[k])
    target = set(values[i : i + sz])
    anti_rev += len(diag_anti[k] - target)
    i += sz

print(min(main_fwd, main_rev, anti_fwd, anti_rev))

