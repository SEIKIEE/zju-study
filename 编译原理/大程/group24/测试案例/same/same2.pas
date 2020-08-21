program hello;
var	f : integer;
    g : integer;
function go(var a : integer): integer;
var f : integer;
begin
    f := 2;
    g := 2;
    writeln(f);
    go := 1;
end
;

begin
	f := 0;
    g := 1;
    writeln(f);
	f := go(1);
	writeln(f);
    writeln(g);
end.
