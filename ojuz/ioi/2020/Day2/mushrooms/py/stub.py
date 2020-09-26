from typing import Final, List, Callable


def _main():
    import sys
    import os
    from typing import Optional

    this_module_name = os.path.splitext(os.path.basename(__file__))[0]
    # Preventing this file to be loaded again.
    this_module = sys.modules[this_module_name] = sys.modules[__name__]

    class InputReader:

        def __init__(self, input_stream):
            self._stream = input_stream
            self._eof: bool = False

        def close(self) -> None:
            try:
                self._stream.close()
            except IOError:
                pass

        def __enter__(self):
            return self

        def __exit__(self, exc_type, exc_value, exc_traceback):
            self.close()

        def eof(self) -> bool:
            return self._eof

        def read(self) -> Optional[str]:
            if self._eof:
                return None
            c = self._stream.read(1)
            if c:
                return c
            self._eof = True
            return None

        def _eat_white(self) -> Optional[str]:
            c: Optional[str] = self.read()
            while c is not None and c.isspace():
                c = self.read()
            return c

        def read_token(self) -> Optional[str]:
            c: Optional[str] = self._eat_white()
            if c is None:
                return None
            tok: str = ""
            while c is not None and not c.isspace():
                tok += c
                c = self.read()
            return tok

        def read_int(self) -> Optional[int]:
            tok: Optional[str] = self.read_token()
            return int(tok) if tok is not None else None

        def read_line(self) -> str:
            line: str = ""
            while True:
                c: Optional[str] = self.read()
                if c is None or c in '\n\r':
                    break
                line += c
            if c == '\r':
                self.read() # Consume '\n'
            return line


    min_n: Final[int] = 2
    max_n: Final[int] = 20000
    max_qc: Final[int] = 20000
    max_qs: Final[int] = 100000
    species_A: Final[int] = 0
    species_B: Final[int] = 1

    n: int
    species: List[int]
    qc: int
    qs: int

    def error_if(cond: bool, message: str) -> None:
        if cond:
            print(message)
            sys.exit(0)

    def wrong_if(cond: bool, message: str) -> None:
        error_if(cond, "Wrong Answer: "+message)

    def local_use_machine(x: List[int]) -> int:
        xs: Final[int] = len(x)
        wrong_if(xs < 2, "Too small array for query.")
        wrong_if(xs > n, "Too large array for query.")
        nonlocal qc
        qc += 1
        wrong_if(qc > max_qc, "Too many queries.")
        nonlocal qs
        qs += xs
        wrong_if(qs > max_qs, "Too many total array sizes as queries.")
        for i in range(xs):
            wrong_if(x[i] < 0 or n - 1 < x[i], "Invalid value in the query array.")
        used: List[bool] = n * [False]
        for i in range(xs):
            wrong_if(used[x[i]], "Duplicate value in the query array.")
            used[x[i]] = True
        diffs: int = 0
        for i in range(1, xs):
            diffs += 1 if (species[x[i]] != species[x[i-1]]) else 0
        return diffs

    def check_input(cond: bool, message: str) -> None:
        error_if(not cond, "Invalid input: "+message)

    def read_int(input_reader: InputReader, error_message: str) -> int:
        try:
            value: Optional[int] = input_reader.read_int()
            if value is None:
                raise ValueError
            return value
        except (ValueError, IOError):
            check_input(False, error_message)
            return 0


    this_module.use_machine = local_use_machine
    input_reader = InputReader(sys.stdin)
    n = read_int(input_reader, "Could not read n.")
    check_input(min_n <= n, "n must not be less than %d, but it is %d." % (min_n, n))
    check_input(n <= max_n, "n must not be greater than %d, but it is %d." % (max_n, n))
    species = n * [0]
    for i in range(n):
        species[i] = read_int(input_reader, "Could not read species element [%d]." % (i,))
        check_input(species[i] == species_A or species[i] == species_B,
                    "Species elements must be %d or %d, but species element [%d] is %d." % (species_A, species_B, i, species[i]))
    check_input(species[0] == species_A, "Species element [%d] must be %d." % (0, species_A))
    # Postponed closing standard input in order to allow interactive usage of the grader.

    qc = 0
    qs = 0
    from mushrooms import count_mushrooms
    answer: int = count_mushrooms(n)
    print(answer)
    print(qc)
    sys.stdout.close()
    input_reader.close()


use_machine: Callable[[List[int]], int]

__all__ = ["use_machine"]


if __name__ == "__main__":
    _main()
