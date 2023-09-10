import random

def play(fragment):
    alphabet = 'abcdefghijklmnopqrstuvwxyz'
    if len(fragment) < 3:
        return "e"
    else:
        return "challenge" if random.random() > 0.8 else 'e'  # 20% chance to challenge if fragment is 3 or longer
