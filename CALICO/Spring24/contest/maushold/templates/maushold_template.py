def solve(H: int, N: int, M: int, R: list[int]) -> int:
    """
    Return the probability of your Pokemon fainting after being hit with Population Bomb
    If the probability is p/q, return p * q^-1 mod 1000000007

    H: Your Pokemon's HP
    N: Number of times that Population Bomb hits
    M: Number of damage rolls
    R: List of M damage rolls
    """
    # YOUR CODE HERE
    return 0


def main():
    H, N, M = [int(x) for x in input().split()]
    R = [int(x) for x in input().split()]
    print(solve(H, N, M, R))


if __name__ == '__main__':
    main()
