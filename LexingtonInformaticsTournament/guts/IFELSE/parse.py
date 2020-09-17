out = ''

others = []
with open("sample.txt") as f:
    for idx, line in enumerate(f):
        line = line.strip()
        if idx == 0:
            N = int(line)
        elif idx == 1:
            attrs = line.split()
        elif idx == 2:
            bools = line.split()
            bools = [b == "TRUE" for b in bools]
        else:
            if line.startswith("IF"):
                attr = line.split()[3]
                if attr not in attrs:
                    others.append(attr)
                line = line.replace("(", '){')
                line = line.replace("IF", 'if (')
            elif line[0] == ')':
                line = '}' + line[1:]
            elif line.startswith("output"):
                line = str(line)
                line = 'cout << "' + ''.join(line.split(' ', 1)[1]) + '" << endl;'
            line = line.replace("ELSE (", "else {")
            line = line.replace(" IS ", '.')

            out += line

init = "#include <bits/stdc++.h>\nusing namespace std;\nstruct obj {"
attrs += others
bools += [False] * len(others)
for a,v in zip(attrs, bools):
    init += f"bool {a} = {str(v).lower()};"
init += "};"
out = init + out
print(out)