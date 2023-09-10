# by qpwoeirut
# for testing


import random

MOVES = ["rock", "paper", "scissors"]


class Agent:
    def play(self, previous_opponent_move=None):
        if previous_opponent_move not in MOVES:
            return random.choice(MOVES)
        else:
            return MOVES[(MOVES.index(previous_opponent_move) + 2) % len(MOVES)]
