import requests


with open("/Users/qpwoeirut/CompetitiveProgramming/AdventOfCode/.token") as token:
    cookies = {"session": token.read().strip()}


def submit_answer(year: int, day: int, level: int, answer) -> bool:
    payload = {"level": level, "answer": str(answer)}
    resp = requests.post(f"https://adventofcode.com/{year}/day/{day}/answer", data=payload, cookies=cookies)

    if b"That's not the right answer" in resp.content:
        return False
    if b"To play, please identify yourself" in resp.content:
        raise Exception("Not logged in")
    if b"You gave an answer too recently" in resp.content:
        raise Exception("Need to wait")
    return True


if __name__ == '__main__':
    print(submit_answer(2022, 1, 1, 0))
