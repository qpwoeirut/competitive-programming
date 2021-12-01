import datetime
import requests
import time

with open(".token") as token:
    cookies = {"session": token.read().strip()}

today_est = datetime.datetime.today() + datetime.timedelta(hours=3)
while today_est.hour != 0:
    print("waiting for midnight...")
    print(today_est)
    time.sleep(0.5)
    today_est = datetime.datetime.today() + datetime.timedelta(hours=3)

year = today_est.strftime("%Y")
day = today_est.strftime("%d").lstrip('0')

with open(f"{year}/day{day}/day{day}.py", "w+") as prog, open("template.py") as template_file:
    prog.write(template_file.read())
with open(f"{year}/day{day}/input.txt", "w+") as inp:
    resp = requests.get(f"https://adventofcode.com/{year}/day/{day}/input", cookies=cookies)
    inp.write(resp.content.decode())
