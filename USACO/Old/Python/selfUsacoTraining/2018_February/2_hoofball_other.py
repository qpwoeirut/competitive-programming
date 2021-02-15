# 6:04pm
# 7:40pm!!!
# 3/20/18
# THIS IS AN INCORRECT SOLUTION. Score: 3/10

for line in open('hoofball.in'):
    args = line.split(' ')
    if len(args) == 1:
        continue

    ans = 1
    cow_distances = {}
    nearest_cows = {}
    for cow_pos in args:
        cow_idx = args.index(cow_pos)
        cow_distances[cow_idx] = {args.index(_other_cow_pos): abs(int(cow_pos) - int(_other_cow_pos)) for
                                  _other_cow_pos in args if cow_idx != args.index(_other_cow_pos)}
        for other_cow_idx, other_cow_pos in cow_distances[cow_idx].items():
            if cow_idx != other_cow_idx:
                if other_cow_pos == min(_cow_diff for _cow_diff in cow_distances[cow_idx].values()):
                    nearest_cows[cow_idx] = other_cow_idx

    for first_cow, nearest_cow in nearest_cows.items():
        if nearest_cows[first_cow] == nearest_cow and nearest_cows[nearest_cow] == first_cow:
            ans += 0.5

    open('hoofball.out', 'a').write(str(int(ans)) + '\n')


# def UNFINISHEDwebsite_solution():
#     for line in open('hoofball.in'):
#         x = line.split(' ')
#         if len(x) == 1:
#             continue
#         N = len(x)
#         passto = [num for num in range(100)]
#
#         def target(i):
#             left_nbr = -1
#             left_dist = 1000
#             right_nbr = -1
#             right_dist = 1000
#
#             for j in range(N):
#                 if x[j] < x[i] and int(x[i]) - int(x[j]) < left_dist:
#                     left_nbr = j
#                     left_dist = int(x[i]) - int(x[j])
#             for j in range(N):
#                 if x[j] > x[i] and int(x[j]) - int(x[i]) < right_dist:
#                     right_nbr = j
#                 right_dist = int(x[j]) - int(x[i])
#
#             if left_dist <= right_dist:
#                 return left_nbr
#             return right_nbr
#
#         for i in range(N):
#             passto[target(i)] += 1
#
#         answer = 0
#         for i in range(N):
#             if passto[i] == 0:
#                 answer += 1
#             if i < target(i) and target(target(i)) == i and passto[i] == 1 and passto[target(i)] == 1:
#                 answer += 1
#
#         print(answer)
#         # open('hoofball.out', 'a').write(str(answer))
#
# website_solution()
#
