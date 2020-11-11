program main;
uses gondola;
const
   mmax1   = 100001;
   maxs132 = 250001;
var
   gondolaSequence    : array [0..mmax1] of longint;
   replacementSequence : array [0..maxs132] of longint;
   i, n, nr : longint; {integer is not big enough}
   T	    : integer;
begin
   (* Read Input *)
   read(T);
   read(n);
   for i:=1 to n do
   begin
      read(gondolaSequence[i-1]);
   end;
   case T of
     1,2,3    : (*subtask 1-3 *)
       writeln(valid(n, gondolaSequence));
     4,5,6    : (*subtask 4-6 *)
       begin
	  nr:=replacement(n, gondolaSequence, replacementSequence);
	  write(nr); write(' ');
	  if nr > 0 then 
	  begin
	     for i:= 0 to nr-2 do
	     begin
		write(replacementSequence[i]); write(' ');
	     end;
	     writeln(replacementSequence[nr-1]);
	  end   
	  else writeln();
       end;
     7,8,9,10 : (*subtask 7-10 *)
       begin
	  writeln(countReplacement(n, gondolaSequence));
       end;
   end; { case }
end.
