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
    Each match consists of a certain number of rounds (default 100).
    """
    score1, score2 = 0, 0
    move1 = None
    move2 = None
    for _ in range(rounds):
        move1 = agent1.play(move2)
        move2 = agent2.play(move1)

        winner = determine_winner(move1, move2)
        if winner == 0:
            score1 += 1
        elif winner == 1:
            score2 += 1
        else:
            score1 += 1
            score2 += 1

    return score1, score2

def main():
    agent_files = [f for f in os.listdir('.') if f.endswith('_agent.py')]
    
    agents = []
    agent_instances = []

    # dynamically import all agent modules
    for agent_file in agent_files:
        module_name = agent_file[:-3]
        module = __import__(module_name)
        agents.append(module)
        agent_instances.append(module.Agent())

    scores = {agent.__name__: 0 for agent in agents}
    print(f"Imported {len(agents)} agents.")
    
    for i, agent1_instance in enumerate(agent_instances):
        for j, agent2_instance in enumerate(agent_instances):
            if i != j:  # don't play an agent against itself
                score1, score2 = run_match(agent1_instance, agent2_instance)
                scores[agents[i].__name__] += score1
                scores[agents[j].__name__] += score2

    sorted_scores = sorted(scores.items(), key=lambda x: x[1], reverse=True)
    
    # print the results
    print("Tournament Results:")
    for agent_name, score in sorted_scores:
        print(f"{agent_name}: {score} points")

if __name__ == '__main__':
    main()
