with open("day4.txt") as f:
    s = [line.strip() for line in f]

ans = 0
needed = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"}
cur = dict()
for line in s:
    if len(line) == 0:
        ok = True
        for x in needed:
            if x not in cur:
                ok = False
        for k,v in cur.items():
            if k == "byr" and not (1920 <= int(v) <= 2002):
                ok = False
            if k == "iyr" and not (2010 <= int(v) <= 2020):
                ok = False
            if k == "eyr" and not (2020 <= int(v) <= 2030):
                ok = False
            if k == "hgt":
                if v.endswith("cm") and not (150 <= int(v.rstrip("cm")) <= 193):
                    ok = False
                if v.endswith("in") and not (59 <= int(v.rstrip("in")) <= 76):
                    ok = False
            if k == "hcl" and not (v[0] == '#' and len(v) == 7 and set(v[1:]) <= set("0123456789abcdef")):
                ok = False
            if k == "ecl" and not (v in set("amb blu brn gry grn hzl oth".split())):
                ok = False
            if k == "pid" and not (v.isnumeric() and len(v) == 9):
                ok = False
        if ok:
            ans += 1
        cur = dict()
    else:
        parts = line.split()
        for part in parts:
            cur[part.split(':')[0]] = part.split(':')[1]
print(ans)