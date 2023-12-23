import requests

with open("/Users/qpwoeirut/CompetitiveProgramming/AdventOfCode/.token") as token:
    cookies = {"session": token.read().strip()}

try:
    with open("/Users/qpwoeirut/CompetitiveProgramming/AdventOfCode/.cache", 'r') as token:
        pass
except FileNotFoundError:
    with open("/Users/qpwoeirut/CompetitiveProgramming/AdventOfCode/.cache", 'w') as token:
        pass


def submit_answer(year: int, day: int, level: int, answer) -> bool:
    hash_value = f"{year}-{day}-{level}={answer}"
    with open("/Users/qpwoeirut/CompetitiveProgramming/AdventOfCode/.cache", "r") as cache:
        entries = {line.strip() for line in cache}
    if hash_value in entries:
        print(answer, "was already submitted")
        return False

    payload = {"level": level, "answer": str(answer)}
    resp = requests.post(f"https://adventofcode.com/{year}/day/{day}/answer", data=payload, cookies=cookies)

    if b"That's not the right answer" in resp.content:
        with open("/Users/qpwoeirut/CompetitiveProgramming/AdventOfCode/.cache", "a") as cache:
            cache.write(hash_value + "\n")
        return False
    if b"To play, please identify yourself" in resp.content:
        raise Exception("Not logged in")
    if b"You gave an answer too recently" in resp.content:
        raise Exception("Need to wait")
    return True


if __name__ == '__main__':
    print(submit_answer(2022, 1, 1, 0))
