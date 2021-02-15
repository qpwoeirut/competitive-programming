count = 0
milking_pos_of_cow = {}
for line in open('milkorder.in'):
    count += 1
    if count == 1:
        num_args = line.split(' ')
        num_of_cows = int(num_args[0])
        num_of_hierarchical_cows = int(num_args[1])
        num_of_position_cows = int(num_args[2])
    elif count == 2:
        hierarchical_cow_order = line.split(' ')
    else:
        if num_of_position_cows != 0:
            milking_pos_of_cow[int(line.split(' ')[0])] = int(line.split(' ')[1])
        if count == num_of_position_cows + 2:
            milking_order_by_cow = {cow_number + 1: None for cow_number in range(num_of_cows)}
            milking_order_by_pos = {cow_number + 1: None for cow_number in range(num_of_cows)}
            for cow_num, milking_pos in milking_pos_of_cow.items():
                milking_order_by_cow[cow_num] = milking_pos
                milking_order_by_pos[milking_pos] = cow_num

            hierarchical_cow_position = {int(hierarchical_cow): milking_order_by_cow[int(hierarchical_cow)] for
                                         hierarchical_cow in hierarchical_cow_order}
            hierarchical_cow_available_positions = {}
            for a in range(num_of_hierarchical_cows):
                for hierarchical_cow_num, hierarchical_cow_pos in hierarchical_cow_position.items():
                    if hierarchical_cow_pos is None:
                        available_positions = []
                        upper_boundary = num_of_cows
                        lower_boundary = 0
                        for other_hierarchical_cow_num, other_hierarchical_cow_pos in hierarchical_cow_position.items():
                            if other_hierarchical_cow_num != hierarchical_cow_num:
                                if milking_order_by_cow[other_hierarchical_cow_num] is not None:
                                    if hierarchical_cow_num < other_hierarchical_cow_num:
                                        if upper_boundary > milking_order_by_cow[other_hierarchical_cow_num]:
                                            upper_boundary = milking_order_by_cow[other_hierarchical_cow_num]
                                    else:
                                        if lower_boundary < milking_order_by_cow[other_hierarchical_cow_num]:
                                            lower_boundary = milking_order_by_cow[other_hierarchical_cow_num]

                        for order_number in range(lower_boundary + 1, upper_boundary):
                            if milking_order_by_pos[order_number] is None:
                                available_positions.append(order_number)

                        if len(available_positions) == 1:
                            milking_order_by_cow[hierarchical_cow_num] = available_positions[0]
                            milking_order_by_pos[available_positions[0]] = hierarchical_cow_num
                        else:
                            # for h_cow in hierarchical_cow_order:
                            #     if int(h_cow) == hierarchical_cow_num:
                            #         h_cow_idx = hierarchical_cow_order.index(h_cow)
                            #         if h_cow_idx == 0:
                            #             milking_order_by_cow[hierarchical_cow_num] = available_positions[0]
                            #             milking_order_by_pos[available_positions[0]] = hierarchical_cow_num
                            #         elif h_cow_idx == num_of_hierarchical_cows:
                            #             milking_order_by_cow[hierarchical_cow_num] = available_positions[-1]
                            #             milking_order_by_pos[available_positions[-1]] = hierarchical_cow_num

                            hierarchical_cow_available_positions[hierarchical_cow_num] = available_positions

            print('cows: ' + str(num_of_cows))
            print('ordered cows: ' + str(num_of_hierarchical_cows))
            print('positioned cows: ' + str(num_of_position_cows))
            print('cow order: ' + str(hierarchical_cow_order))
            print('milking position: ' + str(milking_pos_of_cow))
            print('milking order by cow: ' + str(milking_order_by_cow))
            print('milking order by position: ' + str(milking_order_by_pos))
            print('hierarchical_cow_available_positions:', hierarchical_cow_available_positions)
            print('ordered cow position: ' + str(hierarchical_cow_position))
            print('\n\n\n\n\n\n-------------------------------------------------------------------------------\n\n\n')

            available_spots_in_order = [milking_position for milking_position, milking_pos_holder in milking_order_by_pos.items() if milking_pos_holder is None]
            open('milkorder.out', 'a').write(str(available_spots_in_order[0]) + '\n')
            count = 0
            milking_pos_of_cow = {}
