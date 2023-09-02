import random

def play(fragment):
    alphabet = 'abcdefghijklmnopqrstuvwxyz'
    
    # Simple logic: if fragment is short, add a random letter; otherwise, challenge.
    if len(fragment) < 3:
        return random.choice(alphabet)
    else:
        return "challenge" if random.random() > 0.8 else random.choice(alphabet)  # 20% chance to challenge if fragment is 3 or longer
