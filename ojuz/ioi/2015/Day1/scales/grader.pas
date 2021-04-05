uses scales, graderlib, CTypes;

var
    _T, _i : longint;

begin
	assign(input, 'scales.in');
	reset(input);
	assign(output, 'scales.out');
	rewrite(output);

     _T := _getNumberOfTests();
	init(_T);
	
	for _i := 1 to _T do begin
		_initNewTest; 
		orderCoins;
	end;
	close(input);
	close(output);
end.
