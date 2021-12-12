import sys

input = sys.stdin.readline

N, g = map(int, input().split())
connections = [input().split() for _ in range(N)]
assert all([len(connection) == 2 for connection in connections])

P = 0
G = 0

for connection in connections:
    if "Power" in connection:
        P += 1
    if "Ground" in connection:
        G += 1

adj = dict()
pins = set()
parts = dict()
for p1, p2 in connections:
    if p1 not in adj:
        adj[p1] = []
    if p2 not in adj:
        adj[p2] = []

    adj[p1].append(p2)
    adj[p2].append(p1)

    pins.add(p1)
    pins.add(p2)

    parts[p1.split('-')[0]] = 0
    parts[p2.split('-')[0]] = 0

pins.remove("Power")
pins.remove("Ground")
for pin in pins:
    parts[pin.split('-')[0]] += 1


def convert_name_to_tuple(name: str):
    s = ""
    while name[0].isalpha():
        s += name[0]
        name = name[1:]
    return s, int(name)


parts = [(item[0], item[1]) for item in parts.items() if item[0] not in ["Power", "Ground"]]
parts.sort(key=lambda t: convert_name_to_tuple(t[0]))

visited = {"Power", "Ground"}


def dfs(u):
    if u in visited:
        return 0
    visited.add(u)
    sz = 1
    for v in adj[u]:
        sz += dfs(v)
    return sz


groups = []
for pin in pins:
    if pin not in visited:
        groups.append(dfs(pin))


def calc_h(group):
    if group <= 1:
        return 0
    if group == 2:
        return 1
    lo, hi = 0, 100000
    while lo < hi:
        mid = (lo + hi) >> 1
        if (g - 2) * mid + 2 < group:
            lo = mid + 1
        else:
            hi = mid
    return lo


H = sum([calc_h(group) for group in groups])

print(f"Need {P} holes on power rail", flush=False)
print(f"Need {G} holes on ground rail", flush=False)
print(f"Need {H} additional {g}-hole groups", flush=False)

for name, count in parts:
    print(f"Part {name} has {count} pins", flush=False)
