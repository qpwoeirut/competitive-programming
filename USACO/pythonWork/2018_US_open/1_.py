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
            try:
                mother_of_cow_one = daughter_to_mother[cow_one]
                mother_of_cow_two = daughter_to_mother[cow_two]
                print(mother_of_cow_one)
                print(mother_of_cow_two)
                if mother_of_cow_one == mother_of_cow_two:
                    ans = 'SIBLINGS'
                elif mother_of_cow_one == cow_two:
                    ans = cow_two.upper() + ' is the mother of ' + cow_one.upper()
                elif mother_of_cow_two == cow_one:
                    ans = cow_one.upper() + ' is the mother of ' + cow_two.upper()
                else:
                    print('starting grandmother')
                    g_mother_of_cow_one = daughter_to_mother[mother_of_cow_one]
                    g_mother_of_cow_two = daughter_to_mother[mother_of_cow_two]
                    print(g_mother_of_cow_one)
                    print(g_mother_of_cow_two)
                    if g_mother_of_cow_one == mother_of_cow_two:
                        ans = cow_two.upper() + ' is the aunt of ' + cow_one.upper()
                    elif g_mother_of_cow_two == mother_of_cow_one:
                        ans = cow_one.upper() + ' is the aunt of ' + cow_two.upper()
                    elif g_mother_of_cow_one == cow_two:
                        ans = cow_two.upper() + ' is the grand-mother of ' + cow_one.upper()
                    elif g_mother_of_cow_two == cow_one:
                        ans = cow_one.upper() + ' is the grand-mother of ' + cow_two.upper()
                    elif g_mother_of_cow_one == g_mother_of_cow_two:
                        ans = 'COUSINS'
                    else:
                        print('starting great-grandmother')
                        gg_mother_of_cow_one = daughter_to_mother[g_mother_of_cow_one]
                        gg_mother_of_cow_two = daughter_to_mother[g_mother_of_cow_two]
                        if gg_mother_of_cow_one == cow_two:
                            ans = cow_two.upper() + ' is the great-grand-mother of ' + cow_one.upper()
                        elif gg_mother_of_cow_two == cow_one:
                            ans = cow_one.upper() + ' is the great-grand-mother of ' + cow_two.upper()
                        elif gg_mother_of_cow_one == mother_of_cow_two:
                            ans = cow_two.upper() + ' is the great-aunt of ' + cow_one.upper()
                        elif gg_mother_of_cow_two == mother_of_cow_one:
                            ans = cow_one.upper() + ' is the great-aunt of ' + cow_two.upper()
                        elif gg_mother_of_cow_one == gg_mother_of_cow_two or gg_mother_of_cow_one == g_mother_of_cow_two or gg_mother_of_cow_two == g_mother_of_cow_one:
                            ans = 'COUSINS'
                        else:
                            print('starting great-great-grandmother')
                            ggg_mother_of_cow_one = daughter_to_mother[gg_mother_of_cow_one]
                            ggg_mother_of_cow_two = daughter_to_mother[gg_mother_of_cow_two]
                            if ggg_mother_of_cow_one == cow_two:
                                ans = cow_two.upper() + ' is the great-great-grand-mother of ' + cow_one.upper()
                            elif ggg_mother_of_cow_two == cow_one:
                                ans = cow_one.upper() + ' is the great-great-grand-mother of ' + cow_two.upper()
                            elif ggg_mother_of_cow_one == mother_of_cow_two:
                                ans = cow_two.upper() + ' is the great-great-aunt of ' + cow_one.upper()
                            elif ggg_mother_of_cow_two == mother_of_cow_one:
                                ans = cow_one.upper() + ' is the great-great-aunt of ' + cow_two.upper()
                            elif ggg_mother_of_cow_one == ggg_mother_of_cow_two or ggg_mother_of_cow_one == gg_mother_of_cow_two or ggg_mother_of_cow_two == gg_mother_of_cow_one:
                                ans = 'COUSINS'
                            else:
                                print('starting great-great-great-grandmother')
                                gggg_mother_of_cow_one = daughter_to_mother[ggg_mother_of_cow_one]
                                gggg_mother_of_cow_two = daughter_to_mother[ggg_mother_of_cow_two]
                                if gggg_mother_of_cow_one == cow_two:
                                    ans = cow_two.upper() + ' is the great-great-great-grand-mother of ' + cow_one.upper()
                                elif gggg_mother_of_cow_two == cow_one:
                                    ans = cow_one.upper() + ' is the great-great-great-grand-mother of ' + cow_two.upper()
                                elif gggg_mother_of_cow_one == mother_of_cow_two:
                                    ans = cow_two.upper() + ' is the great-great-great-aunt of ' + cow_one.upper()
                                elif gggg_mother_of_cow_two == mother_of_cow_one:
                                    ans = cow_one.upper() + ' is the great-great-great-aunt of ' + cow_two.upper()
                                elif gggg_mother_of_cow_one == gggg_mother_of_cow_two or gggg_mother_of_cow_one == ggg_mother_of_cow_two or gggg_mother_of_cow_two == ggg_mother_of_cow_one:
                                    ans = 'COUSINS'
                                else:
                                    print('starting great-great-great-great-grandmother')
                                    ggggg_mother_of_cow_one = daughter_to_mother[gggg_mother_of_cow_one]
                                    ggggg_mother_of_cow_two = daughter_to_mother[gggg_mother_of_cow_two]
                                    if ggggg_mother_of_cow_one == cow_two:
                                        ans = cow_two.upper() + ' is the great-great-great-great-grand-mother of ' + cow_one.upper()
                                    elif ggggg_mother_of_cow_two == cow_one:
                                        ans = cow_one.upper() + ' is the great-great-great-great-grand-mother of ' + cow_two.upper()
                                    elif ggggg_mother_of_cow_one == mother_of_cow_two:
                                        ans = cow_two.upper() + ' is the great-great-great-great-aunt of ' + cow_one.upper()
                                    elif ggggg_mother_of_cow_two == mother_of_cow_one:
                                        ans = cow_one.upper() + ' is the great-great-great-great-aunt of ' + cow_two.upper()
                                    elif ggggg_mother_of_cow_one == ggggg_mother_of_cow_two or ggggg_mother_of_cow_one == gggg_mother_of_cow_two or ggggg_mother_of_cow_two == gggg_mother_of_cow_one:
                                        ans = 'COUSINS'
                                    else:
                                        print('starting great-great-great-great-great-grandmother')
                                        gggggg_mother_of_cow_one = daughter_to_mother[ggggg_mother_of_cow_one]
                                        gggggg_mother_of_cow_two = daughter_to_mother[ggggg_mother_of_cow_two]
                                        if gggggg_mother_of_cow_one == cow_two:
                                            ans = cow_two.upper() + ' is the great-great-great-great-great-grand-mother of ' + cow_one.upper()
                                        elif gggggg_mother_of_cow_two == cow_one:
                                            ans = cow_one.upper() + ' is the great-great-great-great-great-grand-mother of ' + cow_two.upper()
                                        elif gggggg_mother_of_cow_one == mother_of_cow_two:
                                            ans = cow_two.upper() + ' is the great-great-great-great-great-aunt of ' + cow_one.upper()
                                        elif gggggg_mother_of_cow_two == mother_of_cow_one:
                                            ans = cow_one.upper() + ' is the great-great-great-great-great-aunt of ' + cow_two.upper()
                                        elif gggggg_mother_of_cow_one == gggggg_mother_of_cow_two or gggggg_mother_of_cow_one == ggggg_mother_of_cow_two or gggggg_mother_of_cow_two == ggggg_mother_of_cow_one:
                                            ans = 'COUSINS'
            except KeyError:
                pass

            open('family.out', 'a').write(ans + '\n')
            count = 0
