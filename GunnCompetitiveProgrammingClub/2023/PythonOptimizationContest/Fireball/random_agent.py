import random

MOVES = ["load", "shield", "fireball", "tsunami", "mirror"]


class Agent:
    def play(self, opponent_last_move):
        return random.choice(MOVES)  # let move validation handle loading
