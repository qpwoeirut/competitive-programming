from typing import List
import sys


class Pos:
    def __init__(self, y: int, x: int):
        self.y = y
        self.x = x


class Judge:
    def set_temperature(self, temperature: List[List[int]]) -> None:
        for row in temperature:
            print(" ".join(map(str, row)))
        sys.stdout.flush()

    def measure(self, i: int, y: int, x: int) -> int:
        print(f"{i} {y} {x}", flush=True)
        v = int(input())
        if v == -1:
            print(f"something went wrong. i={i} y={y} x={x}", file=sys.stderr)
            sys.exit(1)
        return v

    def answer(self, estimate: List[int]) -> None:
        print("-1 -1 -1")
        for e in estimate:
            print(e)
        sys.stdout.flush()


class Solver:

    def __init__(self, L: int, N: int, S: int, landing_pos: List[Pos]):
        self.L = L
        self.N = N
        self.S = S
        self.landing_pos = landing_pos
        self.judge = Judge()

    def solve(self) -> None:
        temperature = self._create_temperature()
        self.judge.set_temperature(temperature)
        estimate = self._predict(temperature)
        self.judge.answer(estimate)

    def _create_temperature(self) -> List[List[int]]:
        temperature = [[0] * self.L for _ in range(self.L)]
        # set the temperature to i * 10 for i-th position
        for i, pos in enumerate(self.landing_pos):
            temperature[pos.y][pos.x] = i * 10
        return temperature

    def _predict(self, temperature: List[List[int]]) -> List[int]:
        estimate = [-1] * self.N
        for i_in in range(self.N):
            # you can output comment
            print(f"# measure i={i_in} y=0 x=0")

            measured_value = self.judge.measure(i_in, 0, 0)
            # answer the position with the temperature closest to the measured value
            min_diff = 9999
            for i_out, pos in enumerate(self.landing_pos):
                diff = abs(temperature[pos.y][pos.x] - measured_value)
                if diff < min_diff:
                    min_diff = diff
                    estimate[i_in] = i_out
        return estimate


def main():
    L, N, S = [int(v) for v in input().split(" ")]
    landing_pos = []
    for _ in range(N):
        y, x = (int(v) for v in input().split(" "))
        landing_pos.append(Pos(y, x))

    solver = Solver(L, N, S, landing_pos)
    solver.solve()


if __name__ == "__main__":
    main()
