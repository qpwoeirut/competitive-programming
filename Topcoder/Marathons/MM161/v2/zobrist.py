import random

random.seed(8)
PIECES = "EPNBRQK"

print("#ifndef ZOBRIST_H")
print("#define ZOBRIST_H")
for c in PIECES:
    nums = [[random.randint(0, 2**64 - 1) for _ in range(8)] for _ in range(20)]
    print(f"const uint64_t ZOBRIST_{c}[20][8] =", '{')
    for row in nums:
        row_str = ", ".join(f"{n}ULL" for n in row)
        print("    {", row_str, "},")
    print("};")

print("inline uint64_t zobrist(const int r, const int c, const char val) {")
print("    if (val == '.') return 0;")
print("    if (val == '#') return 0;")
for c in PIECES:
    print(f"    if (val == '{c}') return ZOBRIST_{c}[r][c];")
print("    assert(0);")
print("}")
print("#endif  // ZOBRIST_H")

