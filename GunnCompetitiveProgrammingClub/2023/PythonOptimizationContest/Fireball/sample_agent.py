import random

class Agent:
    def __init__(self):
        self.loads = 0
        self.used_mirror = False

    def play(self, opponent_last_move):
        if opponent_last_move in ['fireball', 'tsunami'] and not self.used_mirror:
            self.used_mirror = True
            return 'mirror'

        if self.loads >= 2:
            self.loads -= 2
            return 'tsunami'
        elif self.loads == 1:
            self.loads -= 1
            return 'fireball'
        else:
            self.loads += 1
            return random.choice(['load', 'shield'])

# create an instance of the agent
agent = Agent()

# define the play function for the tournament to use
def play(opponent_last_move):
    return agent.play(opponent_last_move)
