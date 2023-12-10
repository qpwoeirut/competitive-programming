import collections

from submit_answer import submit_answer

#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


dirs = {
    "|": 1 | 4,
    "-": 2 | 8,
    "L": 1 | 2,
    "J": 1 | 8,
    "7": 4 | 8,
    "F": 2 | 4,
}


LEVEL = 2
SAMPLE_ANSWERS = [8, 8]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def find_start(A):
    for r in range(len(A)):
        for c in range(len(A[r])):
            if A[r][c] == 'S':
                sval = 0
                for i in range(4):
                    nr = r + chr[i]
                    nc = c + chc[i]
                    if 0 <= nr < len(A) and 0 <= nc < len(A[nr]) and A[nr][nc] != '.' and dirs[A[nr][nc]] & (1 << ((i + 2) % 4)):
                        sval |= 1 << i
                return r, c, sval
    raise ValueError()


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    A = [line for line in input_string.split('\n')]
    # A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line.split())) for line in input_string.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    M = len(A[0])

    ans1 = 0
    ans2 = 0
    # for i in range(N):

    sr, sc, sval = find_start(A)
    dist = [[10**9 for _ in row] for row in A]

    q = collections.deque(maxlen=N*M)
    q.append((sr, sc, 0))
    dist[sr][sc] = 0
    while q:
        r, c, d = q.popleft()
        print(r, c, d)
        if dist[r][c] < d:
            continue
        ans1 = max(ans1, d)

        val = dirs[A[r][c]] if A[r][c] != 'S' else sval
        for i in range(4):
            nr = r + chr[i]
            nc = c + chc[i]
            if (val >> i) & 1 and 0 <= nr < N and 0 <= nc < M and dist[nr][nc] > d + 1:
                dist[nr][nc] = d + 1
                q.append((nr, nc, d + 1))

    big = []
    for r, row in enumerate(A):
        big.extend(["", "", ""])
        for c, ch in enumerate(row):
            s = [
                ['.', '.', '.'],
                [".", '.', '.'],
                ['.', '.', '.']
            ]
            if ch != '.' and dist[r][c] < 10**9:
                s[1][1] = '#'
                val = dirs[ch] if ch != 'S' else sval
                for i in range(4):
                    if (val >> i) & 1:
                        s[1 + chr[i]][1 + chc[i]] = '#'
            s = [''.join(r) for r in s]
            for i in range(3):
                big[i - 3] += s[i]

    for r in big:
        print(r)

    visited = [[False for _ in row] for row in big]
    n = len(big)
    m = len(big[0])
    for r in range(n):
        for c in range(m):
            if r == 0 or r == n - 1 or c == 0 or c == m - 1:
                q.append((r, c))
    while q:
        r, c = q.popleft()
        for i in range(4):
            nr = r + chr[i]
            nc = c + chc[i]
            if not (0 <= nr < n and 0 <= nc < m):
                continue
            if visited[nr][nc] or big[nr][nc] == '#':
                continue
            visited[nr][nc] = True
            q.append((nr, nc))
    for r in visited:
        print(''.join(list(map(str, map(int, r)))))

    ans2 = sum([[(not visited[r][c]) and big[r][c] == '.' and r % 3 == 1 and c % 3 == 1 for c in range(m)].count(True) for r in range(n)])

    if LEVEL == 1:
        return ans1
    else:
        return ans2


def main():
    with open("sample.txt") as sample_file:
        sample_input = sample_file.read().strip('\n')
    sample_answer = solve(sample_input)
    print("Answer for sample:", sample_answer)
    assert sample_answer == SAMPLE_ANSWER and sample_answer is not None, f"Got {sample_answer} instead of {SAMPLE_ANSWER}"

    with open("input.txt") as input_file:
        inp = input_file.read().strip('\n')
    answer = solve(inp)
    print("Answer:", answer)
    assert submit_answer(2023, 10, LEVEL, answer) is True


if __name__ == '__main__':
    main()
