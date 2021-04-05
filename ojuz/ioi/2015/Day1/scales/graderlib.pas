unit graderlib;

interface

function _getNumberOfTests() : longint;
procedure _initNewTest();
procedure answer(W: array of longint);
procedure _checkQuery(A, B, C, D : longint);
function getMedian(A, B, C : longint) : longint;
function getHeaviest(A, B, C : longint) : longint;
function getLightest(A, B, C : longint) : longint; 
function getNextLightest(A, B, C, D : longint) : longint;

implementation

var
    _numQueries, _numAnswerCalls : longint;
    _realC, _ind : array[0..10] of longint;   
function _getNumberOfTests() : longint;
    var T : longint;
begin
    read(T);
    _getNumberOfTests := T;
end;

procedure _initNewTest();
    var i : longint;
begin
    for i := 0 to 5 do
    begin
        read(_realC[i]);
        dec(_realC[i]);
        _ind[_realC[i]] := i;
    end;
    
    _numQueries := 0;
    _numAnswerCalls := 0;
end;

procedure answer(W: array of longint);
    var 
        i : longint;
begin
    inc(_numAnswerCalls);
    
    if (_numAnswerCalls <= 1) then
    begin
        for i := 0 to 5 do
            write(W[i], ' ');
        writeln;
        writeln(_numQueries);
    end;            
end;

procedure _checkQuery(A, B, C, D : longint);
begin
    if (D = -1) then
    begin
        if ((A < 1) or (A > 6) or (B < 1) or (B > 6) or (C < 1) or (C > 6)) then
            Assert(false);
        if ((A = B) or (B = C) or (A = C)) then
            Assert(false);
    end
    else
    begin
        if ((A < 1) or (A > 6) or (B < 1) or (B > 6) or (C < 1) or (C > 6) or (D < 1) or (D > 6)) then
            Assert(false);
        if ((A = B) or (A = C) or (A = D) or (B = C) or (B = D) or (C = D)) then
            Assert(false);
    end;
end;

function getMedian(A, B, C : longint) : longint;
begin
    inc(_numQueries);
    _checkQuery(A, B, C, -1);
    
    dec(A);
    dec(B);
    dec(C);
    
    if ((_ind[B] < _ind[A]) and (_ind[A] < _ind[C])) then
        getMedian := A + 1
    else if ((_ind[C] < _ind[A]) and (_ind[A] < _ind[B])) then
        getMedian := A + 1
    else if ((_ind[A] < _ind[B]) and (_ind[B] < _ind[C])) then
        getMedian := B + 1
    else if ((_ind[C] < _ind[B]) and (_ind[B] < _ind[A])) then
        getMedian := B + 1
    else
        getMedian := C + 1;
end;

function getHeaviest(A, B, C : longint) : longint;
begin
    inc(_numQueries);
    _checkQuery(A, B, C, -1);    

    dec(A);
    dec(B);
    dec(C);

    if ((_ind[A] > _ind[B]) and (_ind[A] > _ind[C])) then
        getHeaviest := A + 1
    else if ((_ind[B] > _ind[A]) and (_ind[B] > _ind[C])) then
        getHeaviest := B + 1
    else 
        getHeaviest :=  C + 1;
end;

function getLightest(A, B, C : longint) : longint; 
begin
    inc(_numQueries);
    _checkQuery(A, B, C, -1);

    dec(A);
    dec(B);
    dec(C);

    if ((_ind[A] < _ind[B]) and (_ind[A] < _ind[C])) then
        getLightest := A + 1
    else if ((_ind[B] < _ind[A]) and (_ind[B] < _ind[C])) then
        getLightest := B + 1
    else
        getLightest := C + 1;
end;

function getNextLightest(A, B, C, D : longint) : longint;
    var
        allLess : longint;
begin
    allLess := 1;    

    inc(_numQueries);
    _checkQuery(A, B, C, D);

    dec(A);
    dec(B);
    dec(C);
    dec(D);

    if ((_ind[A] > _ind[D]) or (_ind[B] > _ind[D]) or (_ind[C] > _ind[D])) then
        allLess := 0;

    if (allLess = 1) then
    begin
        if ((_ind[A] < _ind[B]) and (_ind[A] < _ind[C])) then
            getNextLightest := A + 1
        else if ((_ind[B] < _ind[A]) and (_ind[B] < _ind[C])) then
            getNextLightest := B + 1
        else
            getNextLightest := C + 1;
    end
    else
    begin
        if ((_ind[A] > _ind[D]) and (((_ind[A] < _ind[B]) or (_ind[B] < _ind[D])) and ((_ind[A] < _ind[C]) or (_ind[C] < _ind[D])))) then
            getNextLightest := A + 1
        else if ((_ind[B] > _ind[D]) and (((_ind[B] < _ind[A]) or (_ind[A] < _ind[D])) and ((_ind[B] < _ind[C]) or (_ind[C] < _ind[D])))) then
            getNextLightest := B + 1
        else
            getNextLightest := C + 1;
    end;
end;

end.