program main;

uses holiday;

var 
    attraction : array[0..99999] of longint;
    n, start, d, i: longint;

begin
    read(n, start, d);
    for i:=0 to n-1 do
    begin
	read(attraction[i]);
    end;
    writeln(findMaxAttraction(n, start, d, attraction));
end.
