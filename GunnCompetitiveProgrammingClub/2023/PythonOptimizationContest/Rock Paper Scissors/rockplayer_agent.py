# sample_agent.py

import random

def play(previous_opponent_move=None):
    """
    This function returns the move of the agent.
    Each agent receives the last move the opponent made as an argument.
    Agents can use this to make strategic decisions.
    For this sample agent, we'll just ignore the opponent's move and play randomly.
    """
    moves = ['rock', 'paper', 'scissors']
    return moves[0];
