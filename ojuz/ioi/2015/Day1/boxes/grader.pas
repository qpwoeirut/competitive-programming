uses boxes;

var
	_N, _K, _L, _i: longint;
	_p: array of longint;
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

begin
     assign(_f, 'boxes.in');
     filemode := 4;
     reset(_f, 1);
     assign(output, 'boxes.out');
     rewrite(output);

     _charsNumber := 0;
     _currentChar := 0;

     _N := _readInt;
     _K := _readInt;
     _L := _readInt;
	setlength(_p, _N);
	for _i := 0 to _N - 1 do
		_p[_i] := _readInt;
	writeln(delivery(_N, _K, _L, _p));
end.
