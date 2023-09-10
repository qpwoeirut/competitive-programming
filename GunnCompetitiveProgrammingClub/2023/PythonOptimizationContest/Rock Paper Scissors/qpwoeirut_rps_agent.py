# by qpwoeirut


import random

MOVES = ["rock", "paper", "scissors"]


class Agent:
    def __init__(self):
        self.my_history = []
        self.their_history = []

    def play(self, previous_opponent_move=None):
        if previous_opponent_move is None:
            self.my_history.clear()
            self.their_history.clear()
        if previous_opponent_move in MOVES:
            self.their_history.append(previous_opponent_move)

        matrix: dict[str, dict[str, dict[str, int]]] = {
            my_move: {their_move: {next_move: 0 for next_move in MOVES} for their_move in MOVES}
            for my_move in MOVES
        }
        for i in range(1, len(self.their_history)):
            matrix[self.my_history[i - 1]][self.their_history[i - 1]][self.their_history[i]] += 1

        if len(self.my_history) == 0 or len(self.their_history) == 0:
            move = random.choice(MOVES)
        else:
            # we get same score for a win or a draw, so play it safe
            history_dict = matrix[self.my_history[-1]][self.their_history[-1]].copy()
            for move in self.their_history:
                history_dict[move] += 0.0001  # for tiebreak purposes
            sorted_moves = list(history_dict.items())
            sorted_moves.sort(key=lambda t: t[1])
            if sorted_moves[0][1] == sorted_moves[1][1]:  # if tie, counter most likely move
                move = MOVES[(MOVES.index(sorted_moves[2][0]) + 1) % len(MOVES)]
            else:
                move = MOVES[(MOVES.index(sorted_moves[0][0]) + 2) % len(MOVES)]

        self.my_history.append(move)
        return move
