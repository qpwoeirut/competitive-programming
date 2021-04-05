uses horses;

var
	_buffer: array [0..1023] of byte;
	_charsNumber: longint;
	_currentChar: longint;
	_f: file;
	_o: text;

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
	_N, _M, _typ, _pos, _val, _i: longint;
	_X, _Y: array of longint;

begin
     assign(_f, 'horses.in');
     filemode := 4;
     reset(_f, 1);
     assign(_o, 'horses.out');
     rewrite(_o);

     _charsNumber := 0;
     _currentChar := 0;
	_N := _readInt;
	setlength(_X, _N);
	for _i := 0 to _N - 1 do
		_X[_i] := _readInt;
	setlength(_Y, _N);
	for _i := 0 to _N - 1 do
		_Y[_i] := _readInt;
	writeln(_o,init(_N,_X,_Y));
	_M := _readInt;
	for _i := 0 to _M - 1 do
	begin
	    _typ := _readInt;
	    _pos := _readInt;
	    _val := _readInt;
		if _typ = 1 then
			writeln(_o,updateX(_pos, _val))
		else
			writeln(_o,updateY(_pos, _val));
	end;
	close(_f);
	close(_o);
end.
