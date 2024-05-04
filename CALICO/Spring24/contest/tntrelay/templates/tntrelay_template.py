def solve(N: int, K: int, S: str) -> int:
    """
    Return the maximum number of players that can make it across the TNT bridge.
    If infinitely many players can complete the course, return -1.
    
    N: number of blocks in the course
    K: maximum jump distance of every player
    S: description of the TNT bridge
    """
    # YOUR CODE HERE
    return 0

def main():
    T = int(input())
    for _ in range(T):
        temp = input().split()
        N, K = int(temp[0]), int(temp[1])
        S = input()
        print(solve(N, K, S))

if __name__ == '__main__':
    main()
