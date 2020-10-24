program grader;

uses game;

var
    n, u, v, i: longint;

function read_int(): longint;
var
    x: longint;
begin
    read(x);
    read_int := x;
end;


begin
    n := read_int();
    initialize(n);
    for i := 1 to n * (n - 1) div 2 do
    begin
        u := read_int();
        v := read_int();
        writeln(hasEdge(u, v));
    end;
end.
