unit gondola;

interface

function valid(n : longint; inputSeq: array of longint): integer;


function replacement(n : longint; gondolaSeq: array of longint; var replacementSeq: array of longint):longint;


function countReplacement(n : longint; inputSeq:array of longint): longint;


implementation


(*----------------------------*)
function valid(n : longint; inputSeq: array of longint): integer;

begin

   valid := -1;

end; { valid }

(*-------------------------*)

function replacement(n : longint; gondolaSeq: array of longint; var replacementSeq: array of longint):longint;

begin

   replacement := -2;

end; { replacement }

(*--------------------------*)

function countReplacement(n : longint; inputSeq: array of longint): longint;

begin

   countReplacement := -3;

end; { countReplacement }

end.
