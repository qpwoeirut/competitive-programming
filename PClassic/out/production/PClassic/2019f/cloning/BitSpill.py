import json
import queue


def bit_spill(x, y, m):
    d = len(m)
    v = m[x][y]
    q = queue.LifoQueue()
    q.put((x, y))

    while q.qsize() != 0:
        (x, y) = q.get()
        if m[x][y] == v:
            m[x][y] ^= 1
            if x > 0:
                q.put((x - 1, y))
            if x < d - 1:
                q.put((x + 1, y))
            if y > 0:
                q.put((x, y - 1))
            if y < d - 1:
                q.put((x, y + 1))


# Do not modify below this line
if __name__ == '__main__':

    with open('BitSpillIN.txt', 'r') as f:

        for line in f:
            if line == '':
                break

            l = line.split(' - ')
            s = json.loads(l[0])
            m = json.loads(l[1])

            for (x, y) in s:
                bit_spill(x, y, m)

            print(m)
