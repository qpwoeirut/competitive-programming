import random

MOVES = ["rock", "paper", "scissors"]
PERIOD = 33


class Agent:
    def __init__(self):
        self.my_history = []

    def play(self, previous_opponent_move=None):
        if len(self.my_history) == 0:
            move = random.choice(MOVES)
        elif len(set(self.my_history[-PERIOD:])) == 1 and len(self.my_history) >= PERIOD:
            move = MOVES[(MOVES.index(self.my_history[-1]) + 1) % len(MOVES)]
        else:
            move = self.my_history[-1]

        self.my_history.append(move)
        return move
