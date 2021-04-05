unit horses;

interface

function init(N : longint; var X, Y : array of longint) : longint;
function updateX(pos, val : longint) : longint;
function updateY(pos, val : longint) : longint;

implementation

function init(N : longint; var X, Y : array of longint) : longint;
begin
	init := 0;
end;

function updateX(pos, val : longint) : longint;
begin
	updateX := 0;
end;

function updateY(pos, val : longint) : longint;
begin
	updateY := 0;
end;

end.
