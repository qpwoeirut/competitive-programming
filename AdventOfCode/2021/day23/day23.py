from collections import *
# from itertools import *
# from math import *
from copy import deepcopy
from heapq import heappop, heappush
from time import sleep

ans = 0
ans2 = 0

#      N   E   S   W
chr = [-1, 0, 1, 0, -1, -1, 1, 1]
chc = [0, 1, 0, -1, -1, 1, -1, 1]

with open("input.txt") as file:
    # A = list(map(int, file.readline().split(',')))
    # A = [int(line.strip()) for line in file]
    A = [line.strip('\n') for line in file]
    # A = [list(map(int, line.strip())) for line in file]

A.insert(3, "  #D#C#B#A#")
A.insert(4, "  #D#B#A#C#")
print('\n'.join(A))

N = len(A)
print("N =", N)
print(A[:10])
# M = len(A[0])

# part 1 solved by hand


dist = defaultdict(lambda: 1e9)
start_hall = '.' * 7
start_cols = tuple(''.join([A[r][c] for r in range(2, N - 1)]) for c in range(3, 10, 2))
dist[(start_hall, start_cols)] = 0

end_hall = start_hall
end_cols = tuple(c * (N - 3) for c in "ABCD")
end = (end_hall, end_cols)

cost = {
    'A': 1,
    'B': 10,
    'C': 100,
    'D': 1000
}


def calc_dist(hall_col, col, row):
    real_col = col * 2 + 2
    real_hc = hall_col + (min(hall_col, 5) - 1 if 2 <= hall_col else 0)
    return (row + 1) + abs(real_hc - real_col)


pq = [(0, (start_hall, start_cols))]
while pq:
    cur = heappop(pq)

    print(cur)
    if cur[1][0] == end_hall and cur[1][1] == end_cols:
        ans2 = cur[0]
        break
    if dist[cur[1]] < cur[0]:
        continue

    hall, cols = cur[1]
    cols = list(cols)

    # move amphipod from room to hallway
    for c, col in enumerate(cols):
        if set(col) == {'.'}:
            continue
        top = min([1e9 if col.find(x) == -1 else col.find(x) for x in "ABCD"])
        assert top != -1
        for hc, spot in enumerate(hall):
            if hc <= c + 1 and not set(hall[hc:c + 2]) <= {'.'}:  # amphipod goes up and left, blocked
                continue
            if hc > c + 1 and not set(hall[c + 2:hc + 1]) <= {'.'}:  # amphipod goes up and right, blocked
                continue
            assert spot == '.', hall[hc:c + 2] + '\n' + hall[c + 2:hc + 1]

            new_hall = list(hall)
            new_hall[hc] = col[top]
            new_hall = ''.join(new_hall)
            new_cols = deepcopy(cols)
            new_cols[c] = ''.join(['.' if i == top else c for i, c in enumerate(cols[c])])
            new_cols = tuple(new_cols)
            new_dist = cur[0] + calc_dist(hc, c, top) * cost[col[top]]
            if dist[(new_hall, new_cols)] > new_dist:
                dist[(new_hall, new_cols)] = new_dist
                heappush(pq, (new_dist, (new_hall, new_cols)))

    # move amphipod from hallway to room
    for hc, spot in enumerate(hall):
        if spot == '.':  # nothing to move
            continue

        c = ord(spot) - ord('A')  # find target column
        col = cols[c]
        if not set(col) <= {".", spot}:
            # if '....' in cols:
            # print("column not ready:", set(col), spot)
            continue
        if hc < c + 1 and not set(hall[hc + 1:c + 2]) <= {'.'}:  # amphipod goes right and down, blocked
            # if '....' in cols:
            # print("blocked going right", hall[hc + 1:c + 2], spot)
            continue
        if hc >= c + 1 and not set(hall[c + 2:hc]) <= {'.'}:  # amphipod goes left and down, blocked
            # if '....' in cols:
            # print("blocked going left", hall[c + 2:hc], spot)
            continue

        top = col.rfind('.')
        new_hall = list(hall)
        new_hall[hc] = '.'
        new_hall = ''.join(new_hall)
        new_cols = deepcopy(cols)
        new_cols[c] = ''.join([spot if i == top else c for i, c in enumerate(cols[c])])
        new_cols = tuple(new_cols)
        new_dist = cur[0] + calc_dist(hc, c, top) * cost[spot]
        # print(new_hall, new_cols, new_dist, dist[(new_hall, new_cols)])
        if dist[(new_hall, new_cols)] > new_dist:
            dist[(new_hall, new_cols)] = new_dist
            heappush(pq, (new_dist, (new_hall, new_cols)))


print("ans1:", ans)
print("ans2:", ans2)
