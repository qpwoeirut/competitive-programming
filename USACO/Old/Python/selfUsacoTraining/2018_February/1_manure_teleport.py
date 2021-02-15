# 6:26pm
# 6:41pm
# 3/19/18


def calculate_answer():
    for line in open('teleport.in'):
        args = line.split(' ')
        loc_a = int(args[0])
        loc_b = int(args[1])
        teleport_x = int(args[2])
        teleport_y = int(args[3])

        if abs(loc_a - teleport_x) <= abs(loc_a - teleport_y):
            start_to_teleporter = abs(loc_a - teleport_x)
            teleporter_to_end = abs(teleport_y - loc_b)
        else:
            start_to_teleporter = abs(loc_a - teleport_y)
            teleporter_to_end = abs(teleport_x - loc_b)

        if start_to_teleporter + teleporter_to_end <= abs(loc_a - loc_b):
            ans = start_to_teleporter + teleporter_to_end
        else:
            ans = abs(loc_a - loc_b)

        with open('teleport.out', 'a') as file:
            file.write(str(ans) + '\n')


calculate_answer()
# with open('teleport.out') as answer_file:
#     print(answer_file.read())
