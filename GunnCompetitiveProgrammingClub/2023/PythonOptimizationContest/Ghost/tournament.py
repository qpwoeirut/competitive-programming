import importlib
import os

def can_form_word(fragment, wordlist):
    return any(word.startswith(fragment) for word in wordlist)

def determine_winner(fragment, challenger, challenged, wordlist):
    if can_form_word(fragment, wordlist):
        return challenged
    else:
        return challenger

def load_words(filename):
    with open(filename, 'r') as file:
        return [word.strip() for word in file.readlines()]


# Load the valid words into a global list
wordlist = load_words('valid_words.txt')

def is_valid_fragment(fragment):
    for word in wordlist:
        if word.startswith(fragment):
            return True
    return False

def run_match(agent1, agent2, rounds=100):
    score1, score2 = 0, 0
#asifnas0gfbqwe08gbe23r0gb2e3rgbeigf AHHHHHHH
    for _ in range(rounds):
        fragment = ""
        current_agent = agent1  # start with agent1 for the first move.
        opponent_agent = agent2
        while len(fragment) <= 100:  # until fragment exceeds 100 characters
            action = current_agent.play(fragment)
            if action == "challenge":
                #  if the fragment is shorter than 3 characters
                if len(fragment) < 3:
                    print(f"Invalid challenge by {current_agent.__name__}. Fragment is less than 3 characters.")
                    # The challenging player who made the invalid challenge loses this round
                    score1 += 1 if opponent_agent == agent1 else 0
                    score2 += 1 if opponent_agent == agent2 else 0
                    break

                # validate the challenge
                if not is_valid_fragment(fragment):
                    # If the fragment is indeed not valid, the challenging player wins the round
                    score1 += 1 if current_agent == agent1 else 0
                    score2 += 1 if current_agent == agent2 else 0
                else:
                    # If the fragment is valid, the challenging player loses the round
                    score1 += 1 if opponent_agent == agent1 else 0
                    score2 += 1 if opponent_agent == agent2 else 0
                break
            else:
                fragment += action
                # Check if the fragment is a complete word (3 letters or more)
                if len(fragment) >= 3 and fragment in wordlist:
                    score1 += 1 if current_agent == agent2 else 0  # The player completing the word loses
                    score2 += 1 if current_agent == agent1 else 0
                    break

            # Switch turns.
            current_agent, opponent_agent = opponent_agent, current_agent

    return score1, score2



def main():
    
    # remove the lines related to loading the wordlist in main.

    agent_files = [f for f in os.listdir('.') if f.endswith('_agent.py')]# already loaded wordlist globally, no need to reload here.
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
            if i != j:
                score1, score2 = run_match(agent1, agent2)  # only pass agent1 and agent2
                scores[agent1.__name__] += score1
                scores[agent2.__name__] += score2

    sorted_scores = sorted(scores.items(), key=lambda x: x[1], reverse=True)
    
    # print the results
    print("Tournament Results:")
    for agent_name, score in sorted_scores:
        print(f"{agent_name}: {score} points")

if __name__ == '__main__':#rooderp
    main()
