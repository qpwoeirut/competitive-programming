uses teams;

var
	_buffer: array [0..1023] of byte;
	_charsNumber: longint;
	_currentChar: longint;
	_f: file;

function _readByte: longint; inline;
begin
    if (_charsNumber < 0) then halt(1);
    if (_charsNumber = 0) or (_currentChar = _charsNumber) then
    begin
    	blockread(_f, _buffer, sizeof(_buffer), _charsNumber);
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
	_N, _Q, _M, _i, _j: longint;
	_A, _B, _K: array of longint;

begin
	assign(_f, 'teams.in');
	filemode := 4;
	reset(_f, 1);
     assign(output, 'teams.out'); rewrite(output);

	_N := _readInt;
	setlength(_A, _N);
	setlength(_B, _N);
	for _i := 0 to _N - 1 do
	begin
		_A[_i] := _readInt;
		_B[_i] := _readInt;
	end;
	init(_N, _A, _B);
	_Q := _readInt;
	for _i := 0 to _Q - 1 do
	begin
		_M := _readInt;
		setlength(_K, _M);
		for _j := 0 to _M - 1 do
		begin
			_K[_j] := _readInt;
		end;
		writeln(can(_M, _K));
	end;
end.