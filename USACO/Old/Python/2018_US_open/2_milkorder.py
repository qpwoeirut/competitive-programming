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

            h_cow_idxs = {hierarchical_cow_order.index(h_cow): int(h_cow) for h_cow in hierarchical_cow_order}
            hierarchical_cow_available_positions = {}
            for hierarchical_cow_num in hierarchical_cow_order:
                if milking_order_by_cow[int(hierarchical_cow_num)] is None:
                    available_positions = []
                    upper_boundary = num_of_cows + 1
                    lower_boundary = 0
                    for other_hierarchical_cow in hierarchical_cow_order:
                        if hierarchical_cow_num != other_hierarchical_cow:
                            if milking_order_by_cow[int(other_hierarchical_cow)] is not None:
                                if hierarchical_cow_order.index(other_hierarchical_cow) > int(hierarchical_cow_num):
                                    if upper_boundary > milking_order_by_cow[int(other_hierarchical_cow)]:
                                        upper_boundary = milking_order_by_cow[int(other_hierarchical_cow)]
                                elif lower_boundary < milking_order_by_cow[int(other_hierarchical_cow)]:
                                    lower_boundary = milking_order_by_cow[int(other_hierarchical_cow)]

                    for order_number in range(lower_boundary + 1, upper_boundary):
                        if milking_order_by_pos[order_number] is None:
                            available_positions.append(order_number)

                    hierarchical_cow_available_positions[int(hierarchical_cow_num)] = available_positions

                    unplaced_h_cow_idx = 0
                    temp_hierarchical_cow_available_positions = hierarchical_cow_available_positions
                    for unplaced_h_cow, available_spots_for_cow in hierarchical_cow_available_positions.items():
                        spots_from_left = unplaced_h_cow_idx
                        spots_from_right = len(hierarchical_cow_available_positions) - unplaced_h_cow_idx
                        temp_hierarchical_cow_available_positions[unplaced_h_cow] = \
                        temp_hierarchical_cow_available_positions[unplaced_h_cow][spots_from_left:]
                        temp_hierarchical_cow_available_positions[unplaced_h_cow] = \
                        temp_hierarchical_cow_available_positions[unplaced_h_cow][:-spots_from_right + 1]
                        unplaced_h_cow_idx += 1

                    hierarchical_cow_available_positions = temp_hierarchical_cow_available_positions
                    for h_cow, available_pos in hierarchical_cow_available_positions.items():
                        if len(available_pos) == 1:
                            milking_order_by_cow[h_cow] = available_pos[0]
                            milking_order_by_pos[available_pos[0]] = h_cow
                        else:
                            hierarchical_cow_available_positions[h_cow] = available_pos

            print('cows: ' + str(num_of_cows))
            print('ordered cows: ' + str(num_of_hierarchical_cows))
            print('positioned cows: ' + str(num_of_position_cows))
            print('hierarchical cow order: ' + str(hierarchical_cow_order))
            print('milking position: ' + str(milking_pos_of_cow))
            print('milking order by cow: ' + str(milking_order_by_cow))
            print('milking order by position: ' + str(milking_order_by_pos))
            print('hierarchical_cow_available_positions:', hierarchical_cow_available_positions)
            # print('hierarchical cow position: ' + str(hierarchical_cow_position))

            available_spots_in_order = [milking_position for milking_position, milking_pos_holder in
                                        milking_order_by_pos.items() if milking_pos_holder is None]
            open('milkorder.out', 'a').write(str(available_spots_in_order[0]) + '\n')
            count = 0
            milking_pos_of_cow = {}
            print('\n\n\n\n\n\n\n\n---------------------------------------------------------------------------\n\n\n\n')
