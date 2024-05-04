def start() -> str:
    """
    Phase 1: Initialize N.
    
    Return a string of digits denoting the initial persistent value.
    """
    # YOUR CODE HERE


def observe(N: str, color: str) -> str:
    """
    Phase 2: Observe each brick.
    
    N: a digit string denoting the persistent value from the previous run
    color: a letter ('B', 'S', or 'G') denoting the color of the current brick
    
    Return a string of digits denoting the updated persistent value for the next
    run. This string must have the same length as the given N.
    """
    # YOUR CODE HERE


def answer(N: str) -> str:
    """
    Phase 3: Submit the final answer.
    
    N: a digit string denoting the persistent value from the previous run
    
    Return a string of length 3 containing each of the characters 'B', 'S', and
    'G' exactly once, denoting the types from least to most frequent. For
    example, if silver was the least frequent, gold was in the middle, and
    bronze was the most frequent, then you should output 'SGB'
    """
    # YOUR CODE HERE


def main():
    phase = input()
    if phase == 'START':
        print(start())
    elif phase == 'OBSERVE':
        N = input()
        color = input()
        print(observe(N, color))
    else:
        N = input()
        print(answer(N))


if __name__ == '__main__':
    main()
