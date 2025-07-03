import math

CROUCH_SPEED = 200
RUN_SPEED = 400

crouch_moves = []
run_moves = []

for dx in range(-RUN_SPEED, RUN_SPEED + 1):
    for dy in range(-RUN_SPEED, RUN_SPEED + 1):
        if dx % 25 != 0 or dy % 25 != 0: continue
        squared_dist = dx * dx + dy * dy
        if squared_dist <= CROUCH_SPEED * CROUCH_SPEED:
            crouch_moves.append((dx, dy))
        elif squared_dist <= RUN_SPEED * RUN_SPEED:
            run_moves.append((dx, dy))

lines = []

lines.append("#ifndef MOVES_H")
lines.append("#define MOVES_H")

lines.append(f"const int CROUCH_MOVES = {len(crouch_moves)};")
lines.append(f"const int RUN_MOVES = {len(run_moves)};")

lines.append("const int CROUCH_X[CROUCH_MOVES] = {" + ",".join(str(dx) for dx, _ in crouch_moves) + "};")
lines.append("const int CROUCH_Y[CROUCH_MOVES] = {" + ",".join(str(dy) for _, dy in crouch_moves) + "};")

lines.append("const int RUN_X[RUN_MOVES] = {" + ",".join(str(dx) for dx, _ in run_moves) + "};")
lines.append("const int RUN_Y[RUN_MOVES] = {" + ",".join(str(dy) for _, dy in run_moves) + "};")

lines.append("#endif  // MOVES_H")

with open("moves.h", "w") as f:
    f.write("\n".join(lines))
