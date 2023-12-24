# from https://github.com/ytchang05/AdventOfCode/blob/main/initialize.py

import bs4
import os
import requests
import time
from datetime import datetime, timedelta
from pytz import timezone, utc


# Get current time in Eastern Time
def est_now() -> datetime:
    return datetime.now(tz=utc).astimezone(timezone("US/Eastern"))


def pre_setup(year: str, day: str):
    # Create new folder for the day
    if not os.path.exists(f"{year}/day{day}"):
        os.makedirs(f"{year}/day{day}/")

    # Create new Python file for the day
    with open(f"{year}/day{day}/day{day}.py", "w") as f, open("template.py") as template:
        f.write(template.read().replace("{{year}}", year).replace("{{day}}", day))


def wait_for_start():
    # Wait for midnight EST
    now = est_now()
    while now.hour != 0:
        print(now)
        time.sleep(0.5)
        now = est_now()


def fetch_input(year: str, day: str, cookies: dict[str, str]):
    # Download input txt file from AoC website
    with open(f"{year}/day{day}/input.txt", "w") as f:
        f.write(requests.get(f"https://adventofcode.com/{year}/day/{day}/input", cookies=cookies).content.decode().strip())

    # Parse page and grab the largest <code> element, which we'll assume is the sample
    page = requests.get(f"https://adventofcode.com/{year}/day/{day}", cookies=cookies).content.decode()
    soup = bs4.BeautifulSoup(page, features="html.parser")
    codes = [code.text.strip() for code in soup.find_all("code")]
    sample = max(codes, key=len)
    with open(f"{year}/day{day}/sample.txt", "w+") as sample_file:
        sample_file.write(sample)


def main():
    with open(".token") as token:
        cookies = {"session": token.read().strip()}

    # Get current year, day (adding 3 hours for those running it before 12EST)
    # year, day = est_now().strftime("%Y"), (est_now() + timedelta(hours=3)).strftime("%-d")

    year = "2023"
    day = "22"
    pre_setup(year, day)
    # wait_for_start()

    # 12:00 AM Eastern!
    print("Advent of Code started!")

    fetch_input(year, day, cookies)


if __name__ == '__main__':
    main()
