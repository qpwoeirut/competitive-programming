unit sorting;

interface
function findSwapPairs(N: longint; var S: array of longint; var M: longint; var X, Y, P, Q: array of longint) : longint;

implementation

function findSwapPairs(N: longint; var S: array of longint; var M: longint; var X, Y, P, Q: array of longint) : longint;
begin
	P[0] := 0;
	Q[0] := 0;
	findSwapPairs := 1;
end;

end.
