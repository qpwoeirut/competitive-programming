def solve(n, k, list):
    fen = [0] * (n + 1)
    ans = 0
    curr_inversions = 0
    left = 0
    for right in range(n):
        q = query(fen, list[right])
        curr_inversions += (right - left - q)
        update(fen, list[right], n, 1)
        while curr_inversions > k:
            update(fen, list[left], n, -1)
            q = query(fen, list[left])
            curr_inversions -= q
            left += 1
        ans += (right - left + 1)
    return ans


def update(fen, index, n, val):
    while index <= n:
        fen[index] += val
        index += index & (-index)


def query(fen, index):
    ans = 0
    while index > 0:
        ans += fen[index]
        index -= index & (-index)
    return ans


# Do not modify below this line
if __name__ == '__main__':
    with open('InversionsIN.txt', 'r') as f:
        tests = int(f.readline())
        for i in range(tests):
            row = f.readline().split(" ")
            n = int(row[0])
            k = int(row[1])
            list = [0] * n
            row = f.readline().split(" ")
            for j in range(n):
                list[j] = int(row[j])
            print(solve(n, k, list))
