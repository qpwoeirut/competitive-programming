# http://www.usaco.org/index.php?page=viewproblem2&cpid=759
# 3/22
# 60 or 56 lines
def calculate_steak_overlap(feed_billboard_coords, steak_billboard_coords):
    x_left_feed = int(feed_billboard_coords[0])
    y_lower_feed = int(feed_billboard_coords[1])
    x_right_feed = int(feed_billboard_coords[2])
    y_upper_feed = int(feed_billboard_coords[3])
    x_left_steak = int(steak_billboard_coords[0])
    y_lower_steak = int(steak_billboard_coords[1])
    x_right_steak = int(steak_billboard_coords[2])
    y_upper_steak = int(steak_billboard_coords[3])

    steak_in_front = []
    x_range_steak = range(x_left_steak, x_right_steak + 1)
    y_range_steak = range(y_lower_steak, y_upper_steak + 1)
    x_range_feed = range(x_left_feed, x_right_feed + 1)
    y_range_feed = range(y_lower_feed, y_upper_feed + 1)
    if ((x_left_feed in x_range_steak or x_right_feed in x_range_steak) or (
            x_left_steak in x_range_feed or x_right_steak in x_range_feed)) and (
            (y_lower_feed in y_range_steak or y_upper_feed in y_range_steak) or (
            y_lower_steak in y_range_feed or y_upper_steak in y_range_feed)):
        if x_left_feed < x_left_steak:
            steak_in_front.append(x_left_steak)
        else:
            steak_in_front.append(x_left_feed)

        if y_lower_feed < y_lower_steak:
            steak_in_front.append(y_lower_steak)
        else:
            steak_in_front.append(y_lower_feed)

        if x_right_feed > x_right_steak:
            steak_in_front.append(x_right_steak)
        else:
            steak_in_front.append(x_right_feed)

        if y_upper_feed > y_upper_steak:
            steak_in_front.append(y_upper_steak)
        else:
            steak_in_front.append(y_upper_feed)

    return steak_in_front


def get_billboard_size(billboard_coords):
    if billboard_coords:
        return (int(billboard_coords[2]) - int(billboard_coords[0])) * (
                int(billboard_coords[3]) - int(billboard_coords[1]))
    return 0


count = 0
for line in open('billboard.in'):
    count += 1
    if count == 1:
        alex_billboard = line.split(' ')
    elif count == 2:
        greg_billboard = line.split(' ')
    else:
        steak_billboard = line.split(' ')

        alex_billboard_size = get_billboard_size(alex_billboard)
        greg_billboard_size = get_billboard_size(greg_billboard)

        steak_covering_alex = calculate_steak_overlap(alex_billboard, steak_billboard)
        steak_covering_alex = get_billboard_size(steak_covering_alex)

        steak_covering_greg = calculate_steak_overlap(greg_billboard, steak_billboard)
        steak_covering_greg = get_billboard_size(steak_covering_greg)

        total_feed_billboard = alex_billboard_size + greg_billboard_size

        ans = str(alex_billboard_size + greg_billboard_size - (steak_covering_alex + steak_covering_greg))
        open('billboard.out', 'a').write(ans + '\n')

        count = 0
