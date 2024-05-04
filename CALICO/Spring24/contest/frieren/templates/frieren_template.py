def solve(B: int, L: int, E: int) -> int:
    """
    Return the number of times the given person sees the Era Meteor Shower over the course of their life, it it occurs every fifty years.

    B: the number of years ago when someone was born
    L: the lifespan of that person
    E: the number of years until the next Era Meteor Shower
    """
    return -1


def main():
    T = int(input())
    for _ in range(T):
        B, L, E = map(int, input().split())
        print(solve(B, L, E))

if __name__ == '__main__':
    main()