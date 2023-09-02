import os
import importlib

def validate_agent(module):
    # 1. Check if it has a play function
    if not hasattr(module, "play"):
        return False, "No play function found."

    # 2. Check the play function's output for a known input
    try:
        result = module.play("ab")
        if not isinstance(result, str):
            return False, "The play function should return a string."
        
        if result != "challenge" and len(result) != 1:
            return False, "The play function should return a single character or 'challenge'."
    except Exception as e:
        return False, f"Error while executing play function: {e}"

    return True, "Agent is valid."

def main():
    agent_files = [f for f in os.listdir('.') if f.endswith('_agent.py')]
    
    for agent_file in agent_files:
        print(f"Validating {agent_file}...")
        try:
            module_name = agent_file[:-3]
            module = importlib.import_module(module_name)
            
            is_valid, message = validate_agent(module)
            if is_valid:
                print(f"{agent_file} is valid.")
            else:
                print(f"{agent_file} is invalid. Reason: {message}")

        except Exception as e:
            print(f"Error while importing {agent_file}: {e}")

if __name__ == '__main__':
    main()
