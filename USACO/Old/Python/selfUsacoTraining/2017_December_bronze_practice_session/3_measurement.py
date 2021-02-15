# http://www.usaco.org/index.php?page=viewproblem2&cpid=761
# 3/22
# 43 lines
def get_highest_output(cow_milk_output_dict):
    highest_milk_output_cow = []
    milk_outputs = [output for output in cow_milk_output_dict.values()]
    highest_milk_output_amount = max(milk_outputs)
    for cow, output in cow_milk_output_dict.items():
        if output == highest_milk_output_amount:
            highest_milk_output_cow.append(cow)
    return highest_milk_output_cow


count = 0
logs = {}
for line in open('measurement.in'):
    count += 1
    if count == 1:
        num_of_logs = int(line)
    else:
        log_args = line.split(' ')
        try:
            logs[int(log_args[0])].append({log_args[1]: int(log_args[2])})
        except KeyError:
            logs[int(log_args[0])] = [{log_args[1]: int(log_args[2])}]

        if count == num_of_logs + 1:
            ans = 0
            cows_milk_output = {'Bessie': 7, 'Elsie': 7, 'Mildred': 7}
            highest_output = get_highest_output(cows_milk_output)
            for day in range(101):
                try:
                    for log in logs[day]:
                        for cow, change in log.items():
                            if cow == 'Bessie':
                                cows_milk_output['Bessie'] += change
                            elif cow == 'Elsie':
                                cows_milk_output['Elsie'] += change
                            elif cow == 'Mildred':
                                cows_milk_output['Mildred'] += change
                    new_highest_output = get_highest_output(cows_milk_output)
                    if highest_output != new_highest_output:
                        ans += 1
                        highest_output = new_highest_output

                except KeyError:
                    pass
            count = 0
            logs = {}
            open('measurement.out', 'a').write(str(ans) + '\n')
