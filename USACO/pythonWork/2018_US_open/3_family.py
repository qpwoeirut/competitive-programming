# Edited after contest on 4/2/18
# 7:06pm - ?:??pm

# Edited again on 4/3/18
# Resubmitted 8:20pm on 4/3, missed 4, 5, 8 out of 15

# Edited w/ test data and resubmitted at 8:37pm, got 15/15
# I forgot to break the loops!


def get_mother_of(daughter):
    mother = None
    try:
        mother = daughter_to_mother[daughter]
    except KeyError:
        pass
    return mother


count = 0
daughter_to_mother = {}
for line in open('family.in'):
    count += 1
    if count == 1:
        lines_given = int(line.split(' ')[0].strip('\n'))
        cow_one = line.split(' ')[1].strip('\n')
        cow_two = line.split(' ')[2].strip('\n')
    else:
        daughter_to_mother[line.split(' ')[1].strip('\n')] = line.split(' ')[0].strip('\n')
        if count == lines_given + 1:
            ans = 'NOT RELATED'
            print(daughter_to_mother)
            print(get_mother_of(cow_one))
            mothers_of_cow_one = {}
            cow_one_relative = cow_one
            one_relatives = []
            while cow_one_relative is not None:
                one_relatives.append(cow_one_relative)
                cow_one_relative = get_mother_of(cow_one_relative)

            cow_two_relative = cow_two
            two_relatives = []
            while cow_two_relative is not None:
                two_relatives.append(cow_two_relative)
                cow_two_relative = get_mother_of(cow_two_relative)

            print(one_relatives)
            print(two_relatives)

            if cow_one in two_relatives:
                if two_relatives.index(cow_one) == 1:
                    ans = cow_one + ' is the mother of ' + cow_two
                else:
                    num_of_greats = two_relatives.index(cow_one) - 2
                    ans = cow_one + ' is the ' + 'great-' * num_of_greats + 'grand-mother of ' + cow_two

            elif cow_two in one_relatives:
                if one_relatives.index(cow_two) == 1:
                    ans = cow_two + ' is the mother of ' + cow_one
                else:
                    num_of_greats = one_relatives.index(cow_two) - 2
                    ans = cow_two + ' is the ' + 'great-' * num_of_greats + 'grand-mother of ' + cow_one

            else:
                ans_found = False
                for one_relative in one_relatives:
                    for two_relative in two_relatives:  # iterate and check for matches between each relative of each cow
                        if one_relative == two_relative:  # if the cows share a relative
                            one_relative_index = one_relatives.index(one_relative)
                            two_relative_index = two_relatives.index(two_relative)
                            if one_relative_index == two_relatives.index(two_relative):  # if relatives are same generation
                                if one_relative_index == 1:  # if relatives are mothers
                                    ans = 'SIBLINGS'
                                else:
                                    ans = 'COUSINS'

                            else:
                                num_of_greats = abs(one_relative_index - two_relative_index) - 1
                                if one_relative_index < two_relative_index:  # one's relative is nearer in family tree
                                    if one_relative_index == 1:
                                        ans = cow_one + ' is the ' + 'great-' * num_of_greats + 'aunt of ' + cow_two
                                    else:
                                        ans = 'COUSINS'
                                else:
                                    if two_relative_index == 1:
                                        ans = cow_two + ' is the ' + 'great-' * num_of_greats + 'aunt of ' + cow_one
                                    else:
                                        ans = 'COUSINS'

                            ans_found = True
                            break
                    if ans_found is True:
                        break

            count = 0
            open('family.out', 'a').write(str(ans) + '\n')
            daughter_to_mother = {}
