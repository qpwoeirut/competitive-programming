# from collections import *
# from itertools import *
# from math import *
from collections import defaultdict

from typing import Tuple

from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 2
SAMPLE_ANSWERS = [95437, 24933642]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def solve(s: str) -> int or str:
    # A = list(s)
    # A = list(map(int, s.split(',')))
    A = [line for line in s.split('\n')]
    # A = [line for line in s.split('\n')]
    # A = [list(map(int, line)) for line in s.split('\n')]

    N = len(A)
    print("N =", N)
    print(A[:10])
    # M = len(A[0])

    children = defaultdict(set)
    current = [""]
    files = dict()

    i = 0
    while i < N:
        # print(i, A[i])
        if A[i].startswith("$ cd"):
            _, _, path = A[i].split()
            print(path)
            if path == '/':
                current = [""]
            elif path == '..':
                current.pop()
                assert len(current) > 0
            else:
                current.append(path)
                cur_path = '/'.join(current)
                children[cur_path].add(path)
            i += 1
        elif A[i].startswith('$ ls'):
            i += 1
            while i < N and not A[i].startswith('$'):
                size, name = A[i].split()
                cur_path = '/'.join(current)
                children[cur_path].add(name)
                if size != "dir":
                    full_path = '/'.join(current + [name])
                    files[full_path] = int(size)
                i += 1
        else:
            assert False

    dir_sizes = dict()

    def dfs(cur_path: list) -> Tuple[int, int]:
        full_path = '/'.join(cur_path)
        if full_path in files.keys():
            # print("File:", full_path, files[full_path])
            return 0, files[full_path]
        # print(full_path, children[full_path])

        # print(full_path, len(children[full_path]))

        total = 0
        dir_size = 0
        for child in children[full_path]:
            ret, size = dfs(cur_path + [child])
            total += ret
            dir_size += size
        if dir_size <= 100000:
            total += dir_size
        print("Dir:", full_path, total, dir_size)
        dir_sizes[full_path] = dir_size
        return total, dir_size

    if LEVEL == 1:
        return dfs([""])[0]
    else:
        total_left = 70000000 - dfs([""])[1]
        needed = 30000000 - total_left
        return min([v for v in dir_sizes.values() if v >= needed])


def main():
    with open("sample.txt") as sample_file:
        sample_input = sample_file.read().strip('\n')
    sample_answer = solve(sample_input)
    print("Answer for sample:", sample_answer)
    assert sample_answer == SAMPLE_ANSWER, f"Got {sample_answer} instead of {SAMPLE_ANSWER}"

    with open("input.txt") as input_file:
        inp = input_file.read().strip('\n')
    answer = solve(inp)
    assert answer != 103724, "prev fail"
    print("Answer:", answer)
    assert submit_answer(2022, 7, LEVEL, answer) is True


if __name__ == '__main__':
    main()
