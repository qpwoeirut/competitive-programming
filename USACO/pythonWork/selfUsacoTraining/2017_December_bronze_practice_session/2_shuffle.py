# http://www.usaco.org/index.php?page=viewproblem2&cpid=760
# 3/22
# 23 or 22 lines
count = 0
for line in open('shuffle.in'):
    count += 1
    if count == 1:
        pass
    elif count == 2:
        shuffle_directions = line.split(' ')
        shuffle_directions = {shuffle_directions.index(shuffle_direction) + 1: int(shuffle_direction) for
                              shuffle_direction in shuffle_directions}
    else:
        cow_ids = line.split(' ')
        cow_ids[-1] = cow_ids[-1].strip('\n')

        for n in range(3):
            cow_ids_last_round = [None for a in cow_ids]
            for cow in cow_ids:
                current_position = cow_ids.index(cow) + 1
                for k, v in shuffle_directions.items():
                    if k == current_position:
                        for key, val in shuffle_directions.items():
                            if k == val:
                                cow_ids_last_round[key - 1] = cow
            cow_ids = cow_ids_last_round

        count = 0

        ans = '\n'.join(cow_ids)
        open('shuffle.out', 'a').write(ans + '\n')
