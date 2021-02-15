# Approx. 2.5 hrs to complete
# http://www.usaco.org/index.php?page=viewproblem2&cpid=735
# 3/17/18

from random import randint


def calculate_answer(initial_farmer_pos, cow_pos):
    current_farmer_pos = initial_farmer_pos
    total_distance_traveled = 0
    farthest_up = initial_farmer_pos
    farthest_down = initial_farmer_pos
    range_checked = range(farthest_down, farthest_up + 1)
    went_up_last = False
    distance_moved = 0.5

    while cow_pos not in range_checked:
        last_farmer_pos = current_farmer_pos

        distance_moved = int(distance_moved * 2)
        if went_up_last is False:
            # print('farmer is going up')
            current_farmer_pos = initial_farmer_pos + distance_moved
            farthest_up = current_farmer_pos
            went_up_last = True
        else:
            # print('farmer is going down')
            current_farmer_pos = initial_farmer_pos - distance_moved
            farthest_down = current_farmer_pos
            went_up_last = False
        range_checked = range(farthest_down, farthest_up + 1)
        if cow_pos in range_checked:
            total_distance_traveled += abs(current_farmer_pos - last_farmer_pos) - abs(current_farmer_pos - cow_pos)
        else:
            total_distance_traveled += abs(current_farmer_pos - last_farmer_pos)

    #     print(f'initial farmer pos: {initial_farmer_pos}')
    #     print(f'cow pos: {cow_pos}')
    #     print(f'current farmer pos: {current_farmer_pos}')
    #     print(f'last farmer pos: {last_farmer_pos}')
    #     print(f'total distance: {total_distance_traveled}')
    #     print(f'farthest up: {farthest_up}')
    #     print(f'farthest down: {farthest_down}')
    #     print(f'went up last: {went_up_last}')
    #     print(f'distance moved: {distance_moved}')
    #     print('\n ----------------------------------\nrange checked:\n')
    #     for num in range_checked:
    #         print(f'\t{num}')
    #     print('\n============================================\n\n\n')
    #
    # print('\n\n<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n')
    return total_distance_traveled


def website_solution_translated(x, y):
    ans = 0
    by = 1
    dir = 1

    while True:
        if (dir == 1 and x <= y and y <= x + by) or (dir == -1 and x - by <= y and y <= x):
            ans += abs(y-x)
            return ans
        else:
            ans += by * 2
            by *= 2
            dir *= -1


def compare_answers(farmer_pos, cow_pos):
    print(f'my answer: {calculate_answer(farmer_pos, cow_pos)}')
    # 25 lines and print statements

    print(f'website function answer: {website_solution_translated(farmer_pos, cow_pos)}')
    # 12 lines!!


# To test my answer
# for a in range(100):
#     farmer_pos = randint(0, 1000)
#     cow_pos = randint(0, 1000)
#     print(f'\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\nfarmer position: {farmer_pos}')
#     print(f'cow position: {cow_pos}')
#     compare_answers(farmer_pos, cow_pos)
#     print()

compare_answers(0, 1000)

