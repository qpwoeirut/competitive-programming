# from https://github.com/ytchang05/AdventOfCode/blob/main/initialize.py

import os
import requests
import time
from datetime import datetime, timedelta
from pytz import timezone, utc

with open(".token") as token:
    cookies = {"session": token.read().strip()}


# Function to get current time EST
def est_now() -> datetime:
    return datetime.now(tz=utc).astimezone(timezone("US/Eastern"))


# Get current year, day (adding 3 hours for those running it before 12EST)
year, day = est_now().strftime("%Y"), (est_now() + timedelta(hours=3)).strftime("%-d")

# Create new folder for the day
if not os.path.exists(f"{year}/day{day}"):
    os.makedirs(f"{year}/day{day}/")

# Create new Python file for the day
with open(f"{year}/day{day}/day{day}.py", "w") as f, open("template.py") as template:
    f.write(template.read().replace("{{year}}", year).replace("{{day}}", day))
open(f"{year}/day{day}/sample.txt", "w+").close()

# Wait for midnight EST
now = est_now()
while now.hour != 0:
    print(now)
    time.sleep(0.5)
    now = est_now()

# 12:00 AM EST!
print("Advent of Code started!")

# Download input txt file from AoC website
with open(f"{year}/day{day}/input.txt", "w") as f:
    f.write(requests.get(f"https://adventofcode.com/{year}/day/{day}/input", cookies=cookies).content.decode())
