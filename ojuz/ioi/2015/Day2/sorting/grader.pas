uses sorting;

var
	_buffer: array [0..1023] of byte;
	_charsNumber: longint;
	_currentChar: longint;
	_fin: file;
	_fout: text;

function _readByte: longint; inline;
begin
    if (_charsNumber < 0) then halt(1);
    if (_charsNumber = 0) or (_currentChar = _charsNumber) then
    begin
    	blockread(_fin, _buffer, sizeof(_buffer), _charsNumber);
    	_currentChar := 0
    end;
    if (_charsNumber <= 0) then
    begin
    	_readByte := -1;
    	exit;
    end;
    _readByte := _buffer[_currentChar];
    inc(_currentChar);
end;

function _readInt: longint; inline;
var
	c: byte;
	x: longint;
begin
	x := 0;
	c := _readByte;
	while (c < 48) or (c > 57) do
	begin
		c := _readByte;
	end;
	while (c >= 48) and (c <= 57) do
	begin
		x := x * 10;
		inc(x, c - 48);
		c := _readByte;
	end;
	_readInt := x;
end;

var
	N, M, i, ans: longint;
	S, X, Y, P, Q: array of longint;

begin
     assign(_fin, 'sorting.in');
     filemode := 4;
     reset(_fin, 1);
     assign(_fout, 'sorting.out');
     rewrite(_fout);

     _charsNumber := 0;
     _currentChar := 0;
	 
	N := _readInt;
	setlength(S, N);
	for i := 0 to N - 1 do
		S[i] := _readInt;
	M := _readInt;
	setlength(X, M);
	setlength(Y, M);
	for i := 0 to M - 1 do
	begin
		X[i] := _readInt;
		Y[i] := _readInt;
	end;

	setlength(P, M);
	setlength(Q, M);
	for i := 0 to M - 1 do
	begin
	    P[i] := -1;
	    Q[i] := -1;
	end;

	ans := findSwapPairs(N, S, M, X, Y, P, Q);

	writeln(_fout, ans);
	for i := 0 to ans - 1 do
		writeln(_fout, P[i], ' ', Q[i]);
	close(_fin);
	close(_fout);
end.
