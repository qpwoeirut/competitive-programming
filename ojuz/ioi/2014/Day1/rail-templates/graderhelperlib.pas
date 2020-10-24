{$mode objfpc}
{$m+}

unit graderhelperlib;
interface
uses fgl;
type
	tstation = class
	private
	public
		L,R : Longint;
		index, typ, location : Longint;
		constructor create(_i,_t,_l : Longint);
		function getType() : Longint;
		function getLocation() : Longint;
		function getIndex() : Longint;
end;
	

procedure getInput();
procedure Quick1(var list : array of tstation;L : Longint;R : Longint);
procedure Quick2(var list : array of tstation;L : Longint;R : Longint);
procedure now_I_want_to_getLR();
procedure checkans(var anstype,anslocation : array of Longint; ok : Longint);
function getStationNumber() : Longint;
function getFirstStationLocation() : Longint;
function getDistance(x,y : Longint) : Longint;
function getSubtaskNumber() : Longint;
function getCnt() : Longint;

implementation

var
	S,cnt : Longint;
	TASKNUMBER : Longint;
	i,lotype, lolocation : Longint;
	slist : array[0..10005] of tstation;

procedure checkans(var anstype,anslocation : array of Longint; ok : Longint);
begin
	for i:=0 to S-1 do begin
		if anstype[i] <> slist[i].typ then begin
			ok := 0;			
			if anslocation[i] <> slist[i].location then begin
				ok := 0;
			end	
		end;
	end;
	if ok = 0 then begin write('Incorrect'); end;
	if ok = 1 then begin write('Correct'); end;
end;
function getCnt() : Longint;
begin
	getCnt := cnt;
end;
function getSubtaskNumber() : Longint;
begin
	getSubtaskNumber := TASKNUMBER;
end;
constructor tstation.create(_i,_t,_l : Longint);
	begin
		index := _i;
		typ := _t;
		location := _l;
		L := -1;
		R := -1;
	end;
function tstation.getType() : Longint;
	begin
		getType := typ;
	end;
function tstation.getLocation() : Longint;
	begin
		getLocation := location;
	end;
function tstation.getIndex() : Longint;
	begin
		getIndex := index;
	end;
function getStationNumber() : Longint;
	begin
		getStationNumber := S;
	end;
procedure Quick1(var list : array of tstation;L : Longint;R : Longint);
var
	pivot,ii,jj : Longint;
	tmp : tstation;
begin
	ii:=L; jj:=R; pivot:=list[(L+R) div 2].location;
	repeat
		while list[ii].location < pivot do inc(ii);
		while list[jj].location > pivot do dec(jj);
		if ii<=jj then
		begin
			tmp:=list[ii]; list[ii]:=list[jj]; list[jj]:=tmp;
			inc(ii); dec(jj);
		end;
	until ii>jj;
	if ii<R then Quick1(list,ii,R);
	if L<jj then Quick1(list,L,jj);
end;
procedure Quick2(var list : array of tstation;L : Longint;R : Longint);
var
	pivot,ii,jj : Longint;
	tmp : tstation;
begin
	ii:=L; jj:=R; pivot:=list[(L+R) div 2].index;
	repeat
		while list[ii].index < pivot do inc(ii);
		while list[jj].index > pivot do dec(jj);
		if ii<=jj then
		begin
			tmp:=list[ii]; list[ii]:=list[jj]; list[jj]:=tmp;
			inc(ii); dec(jj);
		end;
	until ii>jj;
	if ii<R then Quick2(list,ii,R);
	if L<jj then Quick2(list,L,jj);
end;
procedure now_I_want_to_getLR();
var
	now : Longint;
	begin
		now := slist[S-1].getIndex();
		for i:=S-2 downto 0 do
			begin
				slist[i].R := now;
				if slist[i].getType() = 2 then
					begin
						now := slist[i].getIndex();
					end;
			end;
		now := slist[0].getIndex();
		for i:=1 to S-1 do
			begin
				slist[i].L := now;
				if slist[i].getType() = 1 then
					begin
						now := slist[i].getIndex();
					end;
			end;
	end;

function getFirstStationLocation() : Longint;
	begin
		getFirstStationLocation := slist[0].getLocation();
	end;
function getDistance(x,y : Longint) : Longint;
var
	tmp : Longint;
	ret : Longint;
	begin
		cnt := cnt+1;
		if x<0 then begin
			getDistance := -1;
		end;
		if y<0 then begin
			getDistance := -1;
		end;
		if x>=S then begin
			getDistance := -1;
		end;
		if y>=S then begin
			getDistance := -1;
		end;
		if x = y then
			begin
				getDistance := 0;
			end;
		if slist[x].getLocation() > slist[y].getLocation() then
			begin
				tmp := x;
				x := y;
				y := tmp;
			end;

		if slist[x].getType() = 1 then
			begin
				case (slist[y].getType()) of
					1 : begin
							ret := slist[slist[y].R].getLocation()-slist[x].getLocation()+slist[slist[y].R].getLocation()-slist[y].getLocation();
						end;
					2 : begin
							ret := slist[y].getLocation()-slist[x].getLocation();
						end;
				end;
			end;
		if slist[x].getType() = 2 then
			begin
				case (slist[y].getType()) of
					1 : begin
							ret := slist[x].getLocation()-slist[slist[x].L].getLocation()+slist[slist[y].R].getLocation()-slist[slist[x].L].getLocation()+slist[slist[y].R].getLocation()-slist[y].getLocation();
						end;
					2 : begin

							ret := slist[x].getLocation()-slist[slist[x].L].getLocation()+slist[y].getLocation()-slist[slist[x].L].getLocation();

						end;
				end;
			end;
		getDistance := ret;
	end;
procedure getInput();
begin
	cnt := 0;
	readln(TASKNUMBER);
	readln(S);
	for i:=0 to S-1 do
	begin
		readln(lotype, lolocation);
		slist[i] := tstation.create(i,lotype,lolocation);
	end;
	Quick1(slist,0,S-1);
	now_I_want_to_getLR();
	Quick2(slist,0,S-1);
end;
	
end.
