import random

MOVES = ["rock", "paper", "scissors"]


class Agent:
    def __init__(self):
        self.history = []

    def play(self, previous_opponent_move=None):
        if previous_opponent_move in MOVES:
            self.history.append(previous_opponent_move)

        their_random_move = random.choice(self.history + MOVES)
        return MOVES[(MOVES.index(their_random_move) + 1) % len(MOVES)]



