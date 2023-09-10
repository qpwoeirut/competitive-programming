import random

GAME_LENGTH = 100
MATCH_LENGTH = 100
MAX_LOADS = 101
MOVES = ["load", "shield", "fireball", "tsunami", "mirror"]

MY_MIRROR = 0b01
OPP_MIRROR = 0b10
NO_MY_MIRROR = 0b11 ^ MY_MIRROR
NO_OPP_MIRROR = 0b11 ^ OPP_MIRROR

history = []


def warn_assert(true_or_false: bool, message: str):
    if true_or_false is False:
        print("qpwoeirut_agent:", message)


class Agent:
    def __init__(self):
        self.my_loads = 0
        self.opp_loads = 0
        self.mirror_mask = MY_MIRROR | OPP_MIRROR

        self.my_last_move = None

        if len(history) >= MATCH_LENGTH:
            history.clear()
        history.append([])

        self.opponent_moves = self.calculate_opponent_moves()
        self.opp_deterministic = self.can_assume_deterministic(self.opponent_moves)

    def calculate_opponent_moves(self) -> list[list[list[list[int]]]]:
        opponent_moves = [
            [
                [[] for _ in range(4)]
                for _ in range(MAX_LOADS)
            ] for _ in range(MAX_LOADS)
        ]

        for game in history:
            my_loads = 0
            opp_loads = 0
            mirror_mask = 0b11
            for rnd, moves in enumerate(game):
                my_move, opp_move = moves
                if opp_move is None:
                    if my_move == "load" or rnd + 1 == GAME_LENGTH:
                        break
                    if my_move == "shield":
                        opp_move = "tsunami"
                    elif my_move in ["fireball", "tsunami"]:
                        opp_move = "mirror"
                    else:
                        warn_assert(False, "move reconstruction failed")

                opponent_moves[my_loads][opp_loads][mirror_mask].append(opp_move)
                my_loads += self.load_change(my_move)
                opp_loads += self.load_change(opp_move)
                if my_move == "mirror":
                    warn_assert(mirror_mask & MY_MIRROR > 0, "my mirror used twice in history")
                    mirror_mask &= NO_MY_MIRROR
                if opp_move == "mirror":
                    warn_assert(mirror_mask & OPP_MIRROR > 0, "opponent mirror used twice in history")
                    mirror_mask &= NO_OPP_MIRROR
        return opponent_moves

    @staticmethod
    def can_assume_deterministic(opponent_moves: list[list[list[list[int]]]]):
        for my_loads in range(MAX_LOADS):
            for opp_loads in range(MAX_LOADS):
                for mirror_mask in range(4):
                    if len(set(opponent_moves[my_loads][opp_loads][mirror_mask])) > 1:
                        return False
        return True

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
        if opponent_last_move in MOVES:
            history[-1].append((self.my_last_move, opponent_last_move))
            self.opponent_moves[self.my_loads][self.opp_loads][self.mirror_mask].append(opponent_last_move)

            self.my_loads += self.load_change(self.my_last_move)
            if self.my_last_move == "mirror":
                warn_assert(self.mirror_mask & MY_MIRROR > 0, "my mirror used twice while playing")
                self.mirror_mask &= NO_MY_MIRROR

            if len(set(self.opponent_moves[self.my_loads][self.opp_loads][self.mirror_mask])) > 1:
                self.opp_deterministic = False

            self.opp_loads += self.load_change(opponent_last_move)
            if opponent_last_move == "mirror":
                warn_assert(self.mirror_mask & OPP_MIRROR > 0, "opponent mirror used twice while playing")
                self.mirror_mask &= NO_OPP_MIRROR

        historical_opp_moves = self.opponent_moves[self.my_loads][self.opp_loads][self.mirror_mask]
        move = "load"  # default to load
        if self.opp_deterministic and len(historical_opp_moves) > 0 and len(historical_opp_moves) + len(history) / 10 >= 2:  # try to draw
            opp_move = historical_opp_moves[0]
            if opp_move in ["shield", "fireball"]:
                move = "shield"
            elif opp_move == "tsunami":
                if self.my_loads > 0:
                    move = "fireball"  # cancels tsunami
                elif (self.mirror_mask & MY_MIRROR) > 0:
                    move = "mirror"  # better to win than lose
        elif len(historical_opp_moves) >= 5 and len(set(historical_opp_moves)) == 1:
            # can predict this move but not future ones; try to win
            opp_move = historical_opp_moves[0]
            if opp_move in ["shield", "fireball"]:
                move = "shield"
            elif opp_move == "tsunami":
                if self.my_loads > 0:
                    move = "fireball"  # cancels tsunami
                elif (self.mirror_mask & MY_MIRROR) > 0:
                    move = "mirror"
            elif opp_move == "load" and self.my_loads > 0:
                move = "fireball"
        else:  # try to win
            if self.opp_loads >= 2:
                if (self.mirror_mask & MY_MIRROR) > 0:
                    move = "mirror"
                elif self.my_loads > 0:
                    move = "fireball"
                else:
                    move = "shield"
            elif self.opp_loads == 1:
                move = "shield"
            elif self.my_loads > 0 and (self.mirror_mask & OPP_MIRROR) == 0:
                move = "fireball"

        self.my_last_move = move
        return move
