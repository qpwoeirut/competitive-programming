unit scales;

interface

procedure init(T : longint);
procedure orderCoins();

implementation

uses graderlib;

procedure init(T : longint);
begin
end;

procedure orderCoins();
var i : longint;
    W : array[0..5] of longint;
begin
	for i := 0 to 5 do W[i] := i + 1;
	answer(W);
end;

end.