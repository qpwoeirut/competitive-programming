from math import *
# from itertools import *
# from math import *

ans = 0
ans2 = 0


class Tile:
    def __init__(self, s: str, num):
        self.num = num
        self.top = s.split('\n')[0]
        self.bottom = s.split('\n')[-1]
        self.left = ''.join([r[0] for r in s.split('\n')])
        self.right = ''.join([r[-1] for r in s.split('\n')])

        self.matches = [set() for _ in range(4 * 2 * 2)]

        self.state = 0

    def rot(self):
        tmp = self.top
        self.top = self.left[::-1]
        self.left = self.bottom
        self.bottom = self.right[::-1]
        self.right = tmp

        self.state = ((self.state >> 2) << 2) + (((self.state & 3) + 1) & 3)

    def fliph(self):
        tmp = self.top
        self.top = self.bottom
        self.bottom = tmp
        self.left = self.left[::-1]
        self.right = self.right[::-1]
        x = (self.state >> 2) > 0
        self.state |= 1 << 2
        if x:
            self.state -= 1 << 2

    def flipv(self):
        tmp = self.left
        self.left = self.right
        self.right = tmp
        self.top = self.top[::-1]
        self.bottom = self.bottom[::-1]
        x = (self.state >> 3) > 0
        self.state |= 1 << 3
        if x:
            self.state -= 1 << 3

    def orient(self, state):
        while self.state & 3 != state & 3:
            self.rot()
        if self.state >> 2 != state >> 2:
            self.fliph()
        if self.state >> 3 != state >> 3:
            self.flipv()

    def matches_right(self, tile):
        return self.right == tile.left

    def matches_bottom(self, tile):
        return self.bottom == tile.top


with open("input.txt") as file:
    A = [x.split('\n', 1) for x in file.read().split('\n\n') if x]
    # A = [int(line.strip()) for line in file]

tiles = set(Tile(s[1], int(s[0].split()[-1].strip(':'))) for s in A)
N = len(A)
print("N =", N)

used = set()


def recurse(row, col, r, c, grid):
    print(row, col)
    if row == r:
        for x in grid:
            print([t.num for t in x])
        global ans
        ans = grid[0][0].num * grid[-1][0].num * grid[0][-1].num * grid[-1][-1].num
        print(ans)
        return

    if row > 0 and col > 0:
        above = grid[row - 1][col]
        left = grid[row][col - 1]
        opts = above.matches[above.state].intersection(left.matches[left.state])
    elif row > 0:
        above = grid[row - 1][col]
        opts = above.matches[above.state]
    elif col > 0:
        left = grid[row][col - 1]
        opts = left.matches[left.state]
    else:
        assert False

    for state, tile in opts:
        print(state, tile.num)
        if tile.num in used:
            continue

        tile.orient(state)
        assert row == 0 or grid[row - 1][col].matches_bottom(tile)
        assert col == 0 or grid[row][col - 1].matches_right(tile), f"{grid[row][col-1].right} {tile.left}"
        grid[row][col] = tile
        used.add(tile.num)
        if col == c-1:
            recurse(row + 1, 0, r, c, grid)
        else:
            recurse(row, col + 1, r, c, grid)
        used.remove(tile.num)


def main():
    global used
    for tile1 in tiles:
        for tile2 in tiles:
            if tile1.num == tile2.num:
                continue

            for _ in range(2):
                for _ in range(2):
                    for _ in range(4):
                        for _ in range(2):
                            for _ in range(2):
                                for _ in range(4):
                                    if tile1.matches_right(tile2) or tile1.matches_bottom(tile2) or tile2.matches_right(tile1) or tile2.matches_bottom(tile1):
                                        tile1.matches[tile1.state].add((tile2.state, tile2))
                                        tile2.matches[tile2.state].add((tile1.state, tile1))
                                    tile2.rot()
                                tile2.fliph()
                            tile2.flipv()
                        tile1.rot()
                    tile1.fliph()
                tile1.flipv()

    for r in reversed(range(1, int(sqrt(N) + 1))):
        if N % r > 0:
            continue

        c = N // r

        print(r, c)
        grid = [[None for _ in range(c)] for _ in range(r)]
        for tile in tiles:
            grid[0][0] = tile
            used = {tile.num}
            recurse(0, 1, r, c, grid)

    print("ans1:", ans)
    print("ans2:", ans2)


main()

def test():
    x = tiles.pop()
    print(x.s)
    print()
    print(x.top, x.bottom, x.left, x.right)
    x.rot()
    print(x.top, x.bottom, x.left, x.right)
    x.rot()
    print(x.top, x.bottom, x.left, x.right)
    x.rot()
    print(x.top, x.bottom, x.left, x.right)
    x.rot()
    print(x.top, x.bottom, x.left, x.right)
    print()
    x.fliph()
    print(x.top, x.bottom, x.left, x.right)
    x.flipv()
    print(x.top, x.bottom, x.left, x.right)
    x.fliph()
    print(x.top, x.bottom, x.left, x.right)
    x.flipv()
    print(x.top, x.bottom, x.left, x.right)