program grader;

uses towns, graderlib;

var
	_buffer: array [0..1023] of byte;
	_charsNumber: longint;
	_currentChar: longint;
	ncase, N, R : longint;
	subtask: longint;

begin
    assign(input, 'towns.in');
    reset(input);
    assign(output, 'towns.out');
    rewrite(output);

    _charsNumber := 0;
    _currentChar := 0;
    read(subtask, ncase);
    while ncase > 0 do
    begin
        dec(ncase);
        read(N);
        ini_query(N, subtask);
        R := hubDistance(N, subtask);
    writeln(r);
    end;
    close(input);
    close(output);
end.
