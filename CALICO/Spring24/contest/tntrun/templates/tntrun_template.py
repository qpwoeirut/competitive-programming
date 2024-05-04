def solve(N: int, S: list[str], E: list[str]):
    """
    Output YES if it is possible for the player to run on the course such that it
    consists of blocks and banned otherwise.
    
    N: the number of blocks in the course.
    S: the list of starting blocks
    E: the list of ending blocks
    """
    return


def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        S = [x for x in input()]
        E = [x for x in input()]
        solve(N, S, E)


if __name__ == '__main__':
    main()
