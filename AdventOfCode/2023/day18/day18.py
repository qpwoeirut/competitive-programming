from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [62, 952408144115]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    A = [line for line in input_string.split('\n')]
    # A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line.split())) for line in input_string.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    # M = len(A[0])

    trench = set()
    trench.add((0, 0))
    row, col = 0, 0
    for i in range(N):
        d, n, color = A[i].split()
        color = color[2:-1]
        if LEVEL == 1:
            n = int(n)
            d = "URDL".index(d)
        else:
            d = int(color[-1])
            d = (d + 1) % 4
            n = int(color[:-1], 16)
        row += chr[d] * n
        col += chc[d] * n
        trench.add((row, col))

    rows = [r for r, c in trench]
    rows = [rr for r in rows for rr in [r - 1, r, r + 1]]
    cols = [c for r, c in trench]
    cols = [cc for c in cols for cc in [c - 1, c, c + 1]]

    rows = list(set(rows))
    cols = list(set(cols))
    rows.sort()
    cols.sort()

    mini_pts = [(rows.index(r), cols.index(c)) for r, c in trench]
    sr, sc = rows.index(0), cols.index(0)
    mini_pts.append((sr, sc))

    mtrench = set()
    mtrench.add((sr, sc))
    row, col = sr, sc
    ans1 = 0
    ans2 = 0
    for pt in mini_pts:
        assert row == pt[0] or col == pt[1], f"{row} {col} != {pt}"
        while row < pt[0]:
            row += 1
            mtrench.add((row, col))
        while row > pt[0]:
            row -= 1
            mtrench.add((row, col))
        while col < pt[1]:
            col += 1
            mtrench.add((row, col))
        while col > pt[1]:
            col -= 1
            mtrench.add((row, col))
    print("Finished trench")

    # for r in range(20):
    #     for c in range(20):
    #         print('#' if (r, c) in mtrench else '.', end='')
    #     print()
    mn = min(mtrench)
    q = [(mn[0] + 1, mn[1] + 1)]
    assert q[0] not in mtrench
    visited = set()
    while q:
        r, c = q.pop()
        for i in range(4):
            nr = r + chr[i]
            nc = c + chc[i]
            if (nr, nc) in visited or (nr, nc) in mtrench:
                continue
            q.append((nr, nc))
            visited.add((nr, nc))

    print(len(visited))
    print(len(mtrench))
    for r, c in visited.union(mtrench):
        ans2 += (rows[r] - rows[r - 1]) * (cols[c] - cols[c - 1])

    if LEVEL == 1:
        return ans1
    else:
        return ans2


def main():
    with open("sample.txt") as sample_file:
        sample_input = sample_file.read().strip('\n')
    sample_answer = solve(sample_input)
    print("Answer for sample:", sample_answer)
    assert sample_answer == SAMPLE_ANSWER and sample_answer is not None, f"Got {sample_answer} instead of {SAMPLE_ANSWER} {SAMPLE_ANSWER - sample_answer}"

    with open("input.txt") as input_file:
        inp = input_file.read().strip('\n')
    answer = solve(inp)
    print("Answer:", answer)
    assert submit_answer(2023, 18, LEVEL, answer) is True


if __name__ == '__main__':
    main()
