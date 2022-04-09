def shiftingsands(board, moves):

    return board


# Do not modify below this line
if __name__ == "__main__":
    tests = int(input())
    for test in range(tests):
        board = []
        for i in range(4):
            line = input()
            board.append([])
            line = line.split(" ")
            for j in range(4):
                board[i].append(int(line[j]))

        moves = input().split(" ")

        output = shiftingsands(board, moves)
        print(output)
