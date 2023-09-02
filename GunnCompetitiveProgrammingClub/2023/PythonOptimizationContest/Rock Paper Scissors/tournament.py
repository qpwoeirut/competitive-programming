import importlib
import os
import sys


#import new_sample_agent
#print(dir(new_sample_agent))
def determine_winner(move1, move2):
    if move1 == move2:
        return None  # Draw
    if (move1 == 'rock' and move2 == 'scissors') or \
       (move1 == 'scissors' and move2 == 'paper') or \
       (move1 == 'paper' and move2 == 'rock'):
        return 0  # First move wins
    return 1  # Second move wins

def run_match(agent1, agent2, rounds=100):
    """
    eech match consists of a certain number of rounds (default 100).
    """
    score1, score2 = 0, 0
    last_move1, last_move2 = None, None
    for _ in range(rounds):
        move1 = agent1.play(last_move2)
        move2 = agent2.play(last_move1)

        winner = determine_winner(move1, move2)
        if winner == 0:
            score1 += 1
        elif winner == 1:
            score2 += 1
        else:
            score1 += 1
            score2 += 1

        last_move1, last_move2 = move1, move2

    return score1, score2

def main():
    agent_files = [f for f in os.listdir('.') if f.endswith('_agent.py')]
    #print(f"Found agent files: {agent_files}")
    agents = []
    
    # dynamically import all agent modules
    for agent_file in agent_files:
        module_name = agent_file[:-3]
        module = __import__(module_name)
        agents.append(module)

    scores = {agent.__name__: 0 for agent in agents}
    print(f"Imported {len(agents)} agents.")
    for i, agent1 in enumerate(agents):
        for j, agent2 in enumerate(agents):
            if i != j:  # don't play an agent against itself
                score1, score2 = run_match(agent1, agent2)
                scores[agent1.__name__] += score1
                scores[agent2.__name__] += score2

    sorted_scores = sorted(scores.items(), key=lambda x: x[1], reverse=True)
    
    # print the results
    print("Tournament Results:")
    for agent_name, score in sorted_scores:
        print(f"{agent_name}: {score} points")

if __name__ == '__main__':
    main()
