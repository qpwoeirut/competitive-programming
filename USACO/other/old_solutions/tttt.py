count = 0
board_by_row = []
for line in open('tttt.in'):
    count += 1
    if count <= 3:
        board_by_row.append(line.strip('\n'))
    if count == 3:
        one_cow_wins = []
        two_cow_wins = []
        board_by_column = [str(board_by_row[0][0] + board_by_row[1][0] + board_by_row[2][0]),
                           str(board_by_row[0][1] + board_by_row[1][1] + board_by_row[2][1]),
                           str(board_by_row[0][2] + board_by_row[1][2] + board_by_row[2][2])]
        row_cows = {board_by_row.index(row): set(cow for cow in row) for row in board_by_row}
        column_cows = {board_by_column.index(row): set(cow for cow in row) for row in board_by_column}
        up_left_to_low_right_cows = set(board_by_row[0][0] + board_by_row[1][1] + board_by_row[2][2])
        low_left_to_up_right_cows = set(board_by_row[0][2] + board_by_row[1][1] + board_by_row[2][0])
        diagonals = [up_left_to_low_right_cows, low_left_to_up_right_cows]

        for cows_in_row in row_cows.values():
            if len(cows_in_row) == 1:
                one_cow_wins.append(cows_in_row)
            elif len(cows_in_row) == 2:
                two_cow_wins.append(cows_in_row)

        for cows_in_column in column_cows.values():
            if len(cows_in_column) == 1:
                one_cow_wins.append(cows_in_column)
            elif len(cows_in_column) == 2:
                two_cow_wins.append(cows_in_column)

        for cows_in_diagonal in diagonals:
            if len(cows_in_diagonal) == 1:
                one_cow_wins.append(cows_in_diagonal)
            elif len(cows_in_diagonal) == 2:
                two_cow_wins.append(cows_in_diagonal)

        one_cow_wins = [str(one) for one in one_cow_wins]
        two_cow_wins = [list(two) for two in two_cow_wins]

        unique_one_cow_wins = []
        for one_cow_win in one_cow_wins:
            if one_cow_win not in unique_one_cow_wins:
                unique_one_cow_wins.append(one_cow_win)

        unique_two_cow_wins = []
        for two_cow_win in two_cow_wins:
            if two_cow_win not in unique_two_cow_wins and reversed(two_cow_win) not in unique_two_cow_wins:
                unique_two_cow_wins.append(two_cow_win)

        open('tttt.out', 'a').write(str(len(unique_one_cow_wins)) + '\n' + str(len(unique_two_cow_wins)) + '\n')
        count = 0
        board_by_row = []

