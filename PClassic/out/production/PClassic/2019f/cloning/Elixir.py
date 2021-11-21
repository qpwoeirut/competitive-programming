# Fill out the body of this method
ma = []
sm = []
sr = 0
sc = 0


def solve(m):
    global ma
    global sm
    global sr
    global sc
    ma = []
    sm = []
    sr = 0
    sc = 0
    ma = m
    r = len(ma)
    c = len(ma[0])
    sr = -1
    sc = -1
    er = -1
    ec = -1
    for i in range(0, r):
        sm.append([])
        for j in range(0, c):
            sm[i].append([])
            for k in range(0, 4):
                sm[i][j].append(9999999999999999)
            if ma[i][j] == 'S':
                sr = i
                sc = j
            if ma[i][j] == 'E':
                er = i
                ec = j
    solve2(sr, sc, 0, 0)
    ans = 9999999999999999
    for i in range(0, 4):
        ans = min(ans, sm[er][ec][i])
    if ans != 9999999999999999:
        return ans
    else:
        return -1


def solve2(r, c, steps, dire):
    global ma
    global sm
    if r < 0 or r >= len(ma) or c < 0 or c >= len(ma[r]) or ma[r][c] == 'G' or sm[r][c][dire] <= steps:
        return
    if ma[r][c] == 'E':
        sm[r][c][dire] = steps
        return
    if caught(r, c, dire):
        return
    sm[r][c][dire] = steps
    newdir = (dire + 1) % 4
    solve2(r, c, steps + 1, newdir)
    solve2(r + 1, c, steps + 1, newdir)
    solve2(r - 1, c, steps + 1, newdir)
    solve2(r, c + 1, steps + 1, newdir)
    solve2(r, c - 1, steps + 1, newdir)


def caught(r, c, dire):
    global ma
    if dire == 0:
        for i in range(r, len(ma)):
            if ma[i][c] == 'G':
                return True
    elif dire == 1:
        for i in range(c, -1, -1):
            if ma[r][i] == 'G':
                return True
    elif dire == 2:
        for i in range(r, -1, -1):
            if ma[i][c] == 'G':
                return True
    elif dire == 3:
        for i in range(c, len(ma)):
            if ma[r][i] == 'G':
                return True
    else:
        return False


# DO NOT MODIFY BELOW THIS LINE
if __name__ == '__main__':
    with open('ElixirIN.txt', 'r') as f:
        t = int(f.readline().strip())
        while t > 0:
            st = f.readline().strip().split()
            ra = int(st[0])
            ca = int(st[1])
            md = []
            for i in range(0, ra):
                st = f.readline().strip()
                md.append([])
                for j in range(0, ca):
                    md[i].append(st[j])
            result = solve(md)
            if result < 0:
                print("Can't escape!")
            else:
                print("Escaped in " + str(result) + " steps.")
            t = t - 1
