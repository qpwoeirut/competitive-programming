"""
Usage:

python hamilton-test.py command n t

Example with C++:
python hamilton-test.py "./my_binary" 5 2

Example with Python:
python hamilton-test.py "python my_code.py" 5 2

The script runs t test cases with n shuffled nodes. It checks the answer to
each test case and reports how many queries your program made.

Note that the shuffling is different on the server.
"""

import random
import subprocess
import sys

random.seed(1)


def run(command: str, n: int, t: int):
    if n < 4:
        sys.exit("n must be at least 4")
    if t < 1:
        sys.exit("t must be at least 1")

    proc = subprocess.Popen(
        command, stdin=subprocess.PIPE, stdout=subprocess.PIPE, shell=True
    )
    assert proc.stdin is not None
    assert proc.stdout is not None
    proc.stdin.write(f"{n} {t}\n".encode())
    proc.stdin.flush()

    G = [[0] * (n + 1) for _ in range(n + 1)]

    for i in range(n):
        line = proc.stdout.readline().strip()
        if len(line) != n:
            sys.exit("Incorrect format in graph description")
        for j in range(n):
            if line[j] not in b"01":
                sys.exit(
                    f'Graph description contains character other than 0 or 1:\n"{line.decode()}"'
                )
            G[i + 1][j + 1] = line[j] == ord("1")

    for i in range(1, n + 1):
        if G[i][i]:
            sys.exit("Graph has self-loop")

    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            if G[i][j] + G[j][i] != 1:
                sys.exit(f"Invalid edges between nodes {i + 1} and {j + 1}")

    total_query_count = 0

    for case in range(1, t + 1):
        print(f"Case #{case}: ", end="")

        mapping = list(range(1, n + 1))
        random.shuffle(mapping)
        mapping = [0] + mapping

        query_count = 0

        while True:
            line = proc.stdout.readline()
            parts = line.split()
            op = parts[0]

            if op == b"?":
                # Query
                try:
                    if len(parts) != 3:
                        raise ValueError
                    u = int(parts[1])
                    v = int(parts[2])
                    if u < 1 or u > n or v < 1 or v > n:
                        raise ValueError
                except ValueError:
                    sys.exit(f"Incorrect format in query:\n{line.decode()}")
                query_count += 1
                if G[mapping[u]][mapping[v]]:
                    proc.stdin.write(b">\n")
                else:
                    proc.stdin.write(b"<\n")
                proc.stdin.flush()

            elif op == b"!":
                # Answer
                try:
                    if len(parts) != n + 1:
                        raise ValueError
                    cycle = [int(c) for c in parts[1:]]
                    for c in cycle:
                        if c < 1 or c > n:
                            raise ValueError
                except ValueError:
                    sys.exit(f"Incorrect format in answer:\n{line.decode()}")

                if len(set(cycle)) != len(cycle):
                    sys.exit(f"Duplicate node in answer:\n{line.decode()}")

                for pos in range(n):
                    v_pos = pos + 1 if pos + 1 < n else 0
                    u = cycle[pos]
                    v = cycle[v_pos]
                    if not G[mapping[u]][mapping[v]]:
                        sys.exit(
                            f"Wrong answer: No edge from c_{pos + 1} to c_{v_pos + 1}"
                        )

                print(f"Correct answer after {query_count} queries")
                break

            else:
                sys.exit(f"Unexpected operation:\n{line.decode()}")

        total_query_count += query_count

    avg = total_query_count / t
    print(f"Average query count Q = {avg}")


def usage():
    print(__doc__, end="")
    exit(2)


if __name__ == "__main__":
    if len(sys.argv) != 4:
        usage()

    command = sys.argv[1]
    n = int(sys.argv[2])
    t = int(sys.argv[3])

    run(command, n, t)
