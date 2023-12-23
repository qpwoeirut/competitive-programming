from submit_answer import submit_answer

#      N   E   S   W
chr = [-1, 0, 1, 0, -1, -1, 1, 1]
chc = [0, 1, 0, -1, -1, 1, -1, 1]

LEVEL = 2
SAMPLE_ANSWERS = [42, None]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]

STEPS = 26501365


def investigate(A, start_row, start_col):
    N = len(A)
    M = len(A[0])
    assert N == 131
    assert M == 131

    even = set()
    even.add((start_row, start_col))
    odd = set()

    sizes = [0]
    differences = [0]
    for step in range(1, 1200):  # this takes a while to run
        if step % 2 == 0:
            new_even = set()
            for r, c in odd:
                for d in range(4):
                    nr = r + chr[d]
                    nc = c + chc[d]
                    if A[nr % N][nc % M] != '#':
                        if (nr, nc) not in even:
                            new_even.add((nr, nc))
            even = even.union(new_even)
        else:
            new_odd = set()
            for r, c in even:
                for d in range(4):
                    nr = r + chr[d]
                    nc = c + chc[d]
                    if A[nr % N][nc % M] != '#':
                        if (nr, nc) not in odd:
                            new_odd.add((nr, nc))
            odd = odd.union(new_odd)

            if step % N == STEPS % N:
                diff = len(odd) - sizes[-1]
                print(step, len(odd), diff, diff - differences[-1])
                sizes.append(len(odd))
                differences.append(diff)
    # 65 3849 3849 3849
    # 327 95175 91326 87477
    # 589 307949 212774 121448
    # 851 642171 334222 121448


def solve(input_string: str) -> int or str:
    # A = list(input_string)
    # A = list(map(int, input_string.split(',')))
    A = [line for line in input_string.split('\n')]
    # A = [line + line for line in input_string.split('\n')]
    # A += A
    # A = [int(line) for line in input_string.split('\n')]
    # A = [list(map(int, line.split())) for line in input_string.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    M = len(A[0])

    ans1 = 0
    ans2 = 0
    # for i in range(N):

    start_row = None
    start_col = None

    for r in range(N):
        for c in range(M):
            if A[r][c] == 'S':
                start_row = r
                start_col = c
                break
        if start_row is not None:
            break

    ways = [[[0 for _ in row] for row in A] for _ in range(65)]
    ways[0][start_row][start_col] = 1
    for i in range(64):
        for r in range(N):
            for c in range(M):
                if A[r][c] == '#':
                    ways[i][r][c] = 0
                elif ways[i][r][c] > 0:
                    for d in range(4):
                        nr = r + chr[d]
                        nc = c + chc[d]
                        if 0 <= nr < N and 0 <= nc < M and A[nr][nc] != '#':
                            ways[i + 1][nr][nc] += ways[i][r][c]

    for r in range(N):
        for c in range(M):
            if ways[64][r][c] > 0:
                ans1 += 1

    # investigate(A, start_row, start_col)
    # we do a little hardcoding based on lucky input patterns
    step_size = 121448
    base_count = 95175
    base_add = 91326
    steps = (STEPS - 327) // (N * 2)
    assert (STEPS - 327) % (N * 2) == 0

    lo = base_add + step_size
    hi = base_add + steps * step_size
    ans2 = base_count + steps * (lo + hi) // 2

    if LEVEL == 1:
        return ans1
    else:
        return ans2


def main():
    # with open("sample.txt") as sample_file:
    #     sample_input = sample_file.read().strip('\n')
    # sample_answer = solve(sample_input)
    # print("Answer for sample:", sample_answer)
    # assert sample_answer == SAMPLE_ANSWER and sample_answer is not None, f"Got {sample_answer} instead of {SAMPLE_ANSWER}"

    with open("input.txt") as input_file:
        inp = input_file.read().strip('\n')
    answer = solve(inp)
    print("Answer:", answer)
    assert submit_answer(2023, 21, LEVEL, answer) is True


if __name__ == '__main__':
    main()
