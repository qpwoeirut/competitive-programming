unit towns;

interface

function hubDistance(N, subtask: longint): longint;

implementation

uses graderlib;

function hubDistance(N, subtask: longint):longint;
var R : longint;
begin
    R := getDistance(0, 1);
    hubDistance := R;
end;

end.
