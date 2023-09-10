class Agent:
    def __init__(self):
        self.my_loads = 0
        self.opp_loads = 0
        self.my_mirror = True
        self.opp_mirror = True

    @staticmethod
    def load_change(move):
        if move == "load":
            return 1
        elif move == "fireball":
            return -1
        elif move == "tsunami":
            return -2
        else:
            return 0

    def play(self, opponent_last_move):
        self.opp_loads += self.load_change(opponent_last_move)
        if opponent_last_move == "mirror":
            self.opp_mirror = False

        if self.opp_loads >= 2 and self.my_mirror is True:
            move = "mirror"
            self.my_mirror = False
        elif self.my_loads > 0:
            move = "fireball"
        elif self.opp_loads >= 1:
            move = "shield"
        else:
            move = "load"
        self.my_loads += self.load_change(move)
        return move
