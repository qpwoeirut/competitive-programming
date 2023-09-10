import random

MOVES = ["rock", "paper", "scissors"]


class Agent:
    def play(self, previous_opponent_move=None):
        return random.choice(MOVES)
