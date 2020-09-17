# 12:03pm
# WIP
# 3/24

count = 0
diamonds = {}
for line in open('diamond.in'):
    count += 1
    if count == 1:
        num_of_diamonds = int(line.split(' ')[0])
        max_diff = int(line.split(' ')[1])
    else:
        diamonds[count - 1] = (int(line))
        if count == num_of_diamonds + 1:
            print(num_of_diamonds)
            print(max_diff)
            print(diamonds)
            ans = 0
            diamonds_too_different = {}
            for diamond_idx, diamond in diamonds.items():
                print('\n\n')
                print(diamond_idx, diamond)
                print()
                diamonds_too_different[diamond_idx] = {diamond: _other_diamond for other_diamond_idx, _other_diamond in
                                                       diamonds.items() if diamond_idx != other_diamond_idx and abs(
                                                       diamond - _other_diamond) > max_diff}
                print(diamonds_too_different)

            # for _diamond_idx, other_diamond in diamonds_too_different.items():
            #     if other_diamond:
            #         for diamond_pos, other_diamond_pos in other_diamond.items():
            #
            #     else:
            #         ans += 1
            print(ans)

            open('diamond.out', 'a').write(str(int(ans)) + '\n')

            count = 0
            diamonds = []
