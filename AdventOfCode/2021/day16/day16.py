# from collections import *
# from itertools import *
# from math import *
import operator
from functools import reduce


ans = 0
ans2 = 0

#      N   E   S   W
chr = [-1, 0, 1, 0, -1, -1, 1, 1]
chc = [0, 1, 0, -1, -1, 1, -1, 1]

with open("input.txt") as file:
    # A = list(map(int, file.readline().split(',')))
    # A = [int(line.strip()) for line in file]
    A = [line.strip() for line in file]
    # A = [list(map(int, line.strip())) for line in file]
S = A[0]
hex_to_bin = {
    hex(i)[2:].upper(): bin(i)[2:].rjust(4, '0') for i in range(16)
}
print(S)
for k, v in hex_to_bin.items():
    S = S.replace(k, v)


# def parse_packet(i, end, rem_packets):
#     print("i,end:", i, end)
#     global ans
#     print(S[i:end])
#
#     while i < end:
#         if set(S[i:end]) == {'0'} or rem_packets == 0:
#             return i
#         print("i:", i)
#         version = int(S[i:i + 3], 2)
#         ans += version
#         i += 3
#
#         packet_type = int(S[i:i + 3], 2)
#         i += 3
#         print("v,pt:", version, packet_type)
#
#         if packet_type == 4:
#             while i + 5 <= end:
#                 x = S[i + 1:i + 5]
#                 if S[i] == '1':
#                     i += 5
#                 else:
#                     i += 5
#                     break
#         else:
#             len_type = S[i]
#             i += 1
#             if len_type == '0':
#                 total_len = int(S[i:i + 15], 2)
#                 print("total_len:", total_len)
#                 i += 15
#
#                 i = parse_packet(i, i + total_len, 999)
#             else:
#                 contained = int(S[i:i + 11], 2)
#                 print("contained:", contained)
#                 i += 11
#
#                 i = parse_packet(i, end, contained)
#     return i
#
#
# parse_packet(0, len(S), 999)


def recurse(i) -> tuple:
    print(S[i:])
    if S[i:].count('1') == 0:
        return 0, i+1
    global ans
    version = int(S[i:i + 3], 2)
    ans += version
    i += 3

    packet_type = int(S[i:i + 3], 2)
    i += 3

    if packet_type == 4:
        value = ""
        while True:
            value += S[i + 1:i + 5]
            if S[i] == '1':
                i += 5
            else:
                i += 5
                break
        return int(value, 2), i
    else:
        len_type = S[i]
        i += 1
        sub_vals = []
        if len_type == '0':
            sub_len = int(S[i:i + 15], 2)
            i += 15
            end = i + sub_len
            print("end:", end)
            while i < end:
                val, i = recurse(i)
                sub_vals.append(val)
        else:
            contained = int(S[i:i + 11], 2)
            print("contained:", contained)
            i += 11
            for _ in range(contained):
                val, i = recurse(i)
                sub_vals.append(val)
        print(sub_vals)

        if packet_type == 0:
            return sum(sub_vals), i
        elif packet_type == 1:
            return reduce(operator.mul, sub_vals), i
        elif packet_type == 2:
            return min(sub_vals), i
        elif packet_type == 3:
            return max(sub_vals), i
        elif packet_type == 5:
            return int(sub_vals[0] > sub_vals[1]), i
        elif packet_type == 6:
            return int(sub_vals[0] < sub_vals[1]), i
        elif packet_type == 7:
            return int(sub_vals[0] == sub_vals[1]), i
        else:
            assert False, packet_type


ans2, end = recurse(0)
assert S[end:].count('1') == 0

print("ans1:", ans)
print("ans2:", ans2)
