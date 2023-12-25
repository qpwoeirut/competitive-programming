from submit_answer import submit_answer



#      N   E   S   W
chr = [-1, 0,  1,  0, -1, -1,  1,  1]
chc = [0,  1,  0, -1, -1,  1, -1,  1]


LEVEL = 1
SAMPLE_ANSWERS = [54, None]
SAMPLE_ANSWER = SAMPLE_ANSWERS[LEVEL - 1]


def calc_flow(src: str, sink: str, adj: dict[str, set[str]]) -> tuple[int, dict[str, dict[str, int]]]:
    flow = {u: {v: 0 for v in adj[u]} for u in adj.keys()}

    def augment() -> list[str] or None:
        q = [[src]]
        visited = set()
        visited.add(src)
        while q:
            path = q.pop(0)

            u = path[-1]
            if u == sink:
                return path
            for v in adj[u]:
                if v not in visited and flow[u][v] < 1:
                    visited.add(v)
                    q.append([x for x in path] + [v])  # slow but whatever

        return None

    total = 0
    while (flow_path := augment()) is not None:
        for i in range(1, len(flow_path)):
            u, v = flow_path[i - 1], flow_path[i]
            flow[u][v] += 1
            flow[v][u] -= 1
        total += 1

    return total, flow


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

    ans1 = 0
    ans2 = 0

    adj = dict()
    for i in range(N):
        u, v = A[i].split(':')
        adj[u.strip()] = {x.strip() for x in v.split()}
    old_keys = [k for k in adj.keys()]
    for k in old_keys:
        for v in adj[k]:
            assert v != k
            if v not in adj:
                adj[v] = set()
            adj[v].add(k)

    size1 = -1
    size2 = -1
    source = list(adj.keys())[0]
    for sink in adj.keys():
        if source == sink:
            continue
        total, flow = calc_flow(source, sink, adj)
        if total > 3:
            continue
        print(source, sink)

        visited = set()
        visited.add(source)
        q = [source]
        size1 = 0
        while q:
            cur = q.pop()
            size1 += 1
            for v in adj[cur]:
                if v not in visited and flow[cur][v] < 1:
                    visited.add(v)
                    q.append(v)

        for u in visited:
            for v in adj[u]:
                if v not in visited:
                    print("removed", u, v)
        size2 = 0
        visited.add(sink)
        q = [sink]
        while q:
            cur = q.pop()
            size2 += 1
            for v in adj[cur]:
                if v not in visited and flow[cur][v] < 1:
                    visited.add(v)
                    q.append(v)
        break

    assert size1 != -1 and size2 != -1
    print(size1, size2, len(adj))
    ans1 = size1 * size2

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
    assert submit_answer(2023, 25, LEVEL, answer) is True


if __name__ == '__main__':
    main()
