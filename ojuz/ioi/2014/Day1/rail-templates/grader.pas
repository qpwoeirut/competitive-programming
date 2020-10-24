program grader;

uses rail,graderhelperlib;

var
	anslocation : array[0..10004] of Longint;
	anstype : array[0..10004] of Longint;
	i,S,TASKNUMBER,ok : Longint;

begin
	getInput();
	S := getStationNumber();
	TASKNUMBER := getSubtaskNumber();
	for i:=0 to S-1 do
	begin
		anslocation[i] := -1;
		anstype[i] := -1;
	end;

	findLocation(S,getFirstStationLocation(),anslocation,anstype);
	ok := 1;
	i := getCnt();
	if TASKNUMBER=3 then begin
		if i>S*(S-1) then begin		
			ok := 0;
		end;
	end;

	if TASKNUMBER=4 then begin
		if i>3*(S-1) then begin		
			ok := 0;
		end;
	end;


	checkans(anstype,anslocation,ok);
	

end.
