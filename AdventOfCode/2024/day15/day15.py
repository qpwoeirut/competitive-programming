from submit_answer import submit_answer



#      N   E   S   W
CHR = [-1, 0,  1,  0, -1, -1,  1,  1]
CHC = [0,  1,  0, -1, -1,  1, -1,  1]
DIRS = "^>v<"


LEVEL = 2
SAMPLE_ANSWERS = [10092, 9021]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def apply_move(G: list[list[str]], d: int):
    new = [row.copy() for row in G.copy()]
    rr, rc = -1, -1
    for r in range(len(G)):
        for c in range(len(G[r])):
            if G[r][c] == '@':
                rr = r
                rc = c
                break
    assert rr != -1 and rc != -1

    if LEVEL == 1:
        new[rr][rc] = '.'
        moving = '@'
        for i in range(1, max(len(G), len(G[0]))):
            new[rr + i * CHR[d]][rc + i * CHC[d]] = moving
            if G[rr + i * CHR[d]][rc + i * CHC[d]] == 'O':
                moving = 'O'
            else:
                break
    else:
        if CHR[d] == 0:
            new[rr][rc] = '.'
            moving = '@'
            for i in range(1, max(len(G), len(G[0]))):
                new[rr + i * CHR[d]][rc + i * CHC[d]] = moving
                if G[rr + i * CHR[d]][rc + i * CHC[d]] in '[]':
                    moving = G[rr + i * CHR[d]][rc + i * CHC[d]]
                else:
                    break
        else:
            new[rr][rc] = '.'
            cols = {rc: G[rr][rc]}
            for i in range(1, max(len(G), len(G[0]))):
                new_cols = {}
                if not 0 <= rr + i * CHR[d] < len(G):
                    continue
                for col, val in cols.items():
                    if G[rr + i * CHR[d]][col] == '[':
                        new_cols[col] = G[rr + i * CHR[d]][col]
                        new[rr + i * CHR[d]][col] = '.'

                        new_cols[col + 1] = G[rr + i * CHR[d]][col + 1]
                        new[rr + i * CHR[d]][col + 1] = '.'

                    if G[rr + i * CHR[d]][col] == ']':
                        new_cols[col] = G[rr + i * CHR[d]][col]
                        new[rr + i * CHR[d]][col] = '.'

                        new_cols[col - 1] = G[rr + i * CHR[d]][col - 1]
                        new[rr + i * CHR[d]][col - 1] = '.'

                    if col >= 0 and val == ']' and G[rr + i * CHR[d]][col - 1] in '[]':
                        new_cols[col - 1] = G[rr + i * CHR[d]][col - 1]
                        new[rr + i * CHR[d]][col - 1] = '.'
                    if col + 1 < len(G[0]) and val == '[' and G[rr + i * CHR[d]][col + 1] in '[]':
                        new_cols[col + 1] = G[rr + i * CHR[d]][col + 1]
                        new[rr + i * CHR[d]][col + 1] = '.'
                for col, val in cols.items():
                    new[rr + i * CHR[d]][col] = val
                cols = new_cols
                if not cols:
                    break
    return new


def valid(G: list[list[str]], new: list[list[str]]) -> bool:
    for r in range(len(G)):
        for c in range(len(G[r])):
            if G[r][c] == '#' and new[r][c] != '#':
                return False
    return True


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    # A = [line for line in input_string.split('\n')]
    # A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line.split())) for line in input_string.split('\n')]

    G, moves = input_string.split('\n\n')
    G = list(map(list, G.split('\n')))
    moves = moves.replace('\n', '')

    if LEVEL == 2:
        for r in range(len(G)):
            G[r] = ''.join([c + c if c != 'O' else '[]' for c in G[r]])
            G[r] = G[r].replace('@@', '@.')
            G[r] = list(G[r])


    N = len(moves)
    print("N =", N)

    ans1 = 0
    ans2 = 0
    # for i in range(N):

    for move in moves:
        # print('\n'.join([''.join(r) for r in G]))
        new = apply_move(G, DIRS.index(move))
        if valid(G, new):
            G = new

    for r in range(len(G)):
        for c in range(len(G[r])):
            if G[r][c] == 'O':
                ans1 += 100 * r + c
            if G[r][c] == '[':
                ans2 += 100 * r + c


    # for i in range(N):

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
    assert submit_answer(2024, 15, LEVEL, answer) is True


if __name__ == '__main__':
    main()
