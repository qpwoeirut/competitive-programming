unit graderlib;

interface

procedure ini_query(_N, k: longint);
function getDistance(i, j: longint): longint;

implementation

var
	N : longint;
	dist : array [0..109, 0..109] of longint;
	quota, user_query : longint;


procedure ini_query(_N, k: longint);
var
	i, j : longint;
begin
    N := _N;
    for i := 0 to N - 1 do
    begin
    	for j := 0 to N - 1 do
    		read(dist[i, j]);
    end;

    if (k = 1) or (k = 3) then quota := N * (N - 1) div 2
    else if (k = 2) or (k = 4) or (k = 6) then quota := (7 * N + 1) div 2
    else quota := 5 * N;
    user_query := 0;

end;

function getDistance(i, j: longint): longint;
begin
	user_query := user_query + 1;
	if user_query > quota then 
	begin
		writeln(0);
		exit(0);
	end;
	if (i < 0) or (i >= n) then getDistance := 0
	else if (j < 0) or (j >= n) then getDistance := 0
	else getDistance := dist[i, j];
end;

end.
