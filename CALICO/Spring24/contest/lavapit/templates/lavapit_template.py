def solve(N: int, M: int, G: list[str]) -> int:
    """
    Return the maximum number of diamonds that Steve can mine before exiting the lava pit.

    N: number of rows in the lava pit
    M: number of columns in the lava pit
    G: description of the lava pit
    """
    # YOUR CODE HERE
    return 0


def main():
    T = int(input())
    for _ in range(T):
        N, M = map(int, input().split())
        G = [input() for i in range(N)]
        print(solve(N, M, G))


if __name__ == '__main__':
    main()
