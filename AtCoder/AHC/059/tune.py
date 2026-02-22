#!/usr/bin/env python3

import argparse
import os
import re
import subprocess
import sys
import time
from dataclasses import dataclass
from pathlib import Path
from random import Random


@dataclass
class Params:
    T0: float
    T1: float
    alpha: float
    w_swap: int
    w_edit: int
    w_insert: int
    w_reverse: int
    w_erase: int
    w_pair_erase: int

    def argv(self):
        return [
            f"{self.T0}",
            f"{self.T1}",
            f"{self.alpha}",
            str(self.w_swap),
            str(self.w_edit),
            str(self.w_insert),
            str(self.w_reverse),
            str(self.w_erase),
            str(self.w_pair_erase),
        ]


SCORE_RE = re.compile(r"Best score:\s*(\d+)")


def compile_solver(cpp: Path, exe: Path, cxx: str):
    cmd = [
        cxx,
        "-std=c++20",
        "-O2",
        "-Wall",
        str(cpp),
        "-o",
        str(exe),
    ]
    subprocess.run(cmd, check=True)


def run_case(exe: Path, inp: Path, params: Params):
    proc = subprocess.run(
        [str(exe), *params.argv()],
        stdin=inp.open("rb"),
        stdout=subprocess.DEVNULL,
        stderr=subprocess.PIPE,
    )
    m = SCORE_RE.search(proc.stderr.decode("utf-8", errors="replace"))
    if not m:
        return None
    return int(m.group(1))


def sample_params(rng: Random):
    # Narrowed ranges based on best configs observed in terminal logs.
    # - T0 tended to be moderate/high (roughly 100..550)
    # - T1 tended to be near 0.5..1.0
    # - alpha tended to be near 0.6..1.6
    T0 = rng.uniform(100.0, 600.0)
    T1 = rng.uniform(0.45, 1.20)
    alpha = rng.uniform(0.55, 1.80)

    # Mutation probabilities (must sum to 100).
    # From observed good sets:
    # - reverse: high
    # - insert: medium/high
    # - swap/edit: low/medium
    # - erase/pair_erase: low/medium
    p_swap = rng.randint(0, 30)
    p_edit = rng.randint(0, 25)
    p_insert = rng.randint(5, 45)
    p_reverse = rng.randint(25, 60)
    p_erase = rng.randint(0, 25)
    p_pair = rng.randint(0, 25)

    parts = [p_swap, p_edit, p_insert, p_reverse, p_erase, p_pair]
    s = sum(parts)
    if s == 0:
        parts = [10, 0, 30, 50, 5, 5]
        s = sum(parts)

    # Renormalize to sum to 100.
    scaled = [(x * 100) // s for x in parts]
    acc = sum(scaled)
    # Distribute remainder to the largest original components.
    order = sorted(range(6), key=lambda i: parts[i], reverse=True)
    for k in range(100 - acc):
        scaled[order[k % 6]] += 1

    return Params(
        T0=T0,
        T1=T1,
        alpha=alpha,
        w_swap=scaled[0],
        w_edit=scaled[1],
        w_insert=scaled[2],
        w_reverse=scaled[3],
        w_erase=scaled[4],
        w_pair_erase=scaled[5],
    )


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--cpp", default="sol.cpp")
    ap.add_argument("--exe", default="sol_tune.out")
    ap.add_argument("--cxx", default="g++-15")
    ap.add_argument("--seed", type=int, default=1)
    ap.add_argument("--trials", type=int, default=30)
    ap.add_argument("--cases", type=int, default=10)
    ap.add_argument("--time_budget", type=float, default=120.0)
    args = ap.parse_args()

    root = Path(__file__).resolve().parent
    cpp = (root / args.cpp).resolve()
    exe = (root / args.exe).resolve()

    in_dir = root / "in"
    inputs = sorted(in_dir.glob("*.txt"))
    if not inputs:
        print("no inputs found in ./in", file=sys.stderr)
        return 2

    if args.cases > len(inputs):
        args.cases = len(inputs)
    inputs = inputs[: args.cases]

    compile_solver(cpp, exe, args.cxx)

    rng = Random(args.seed)

    best = None
    best_avg = -10**18
    start = time.time()

    for t in range(args.trials):
        if time.time() - start > args.time_budget:
            break
        p = sample_params(rng)
        scores = []
        ok = True
        for inp in inputs:
            s = run_case(exe, inp, p)
            if s is None:
                ok = False
                break
            scores.append(s)
        if not ok or not scores:
            continue
        avg = sum(scores) / len(scores)
        if avg > best_avg:
            best_avg = avg
            best = (p, scores)
            print(f"best_avg={best_avg:.2f} params={p.argv()} scores={scores}", file=sys.stderr)

    if best is None:
        print("no valid parameter set found", file=sys.stderr)
        return 1

    p, scores = best
    print(" ".join(p.argv()))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
