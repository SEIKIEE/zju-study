program gogoto;
var a: integer;
begin
	a := 1;
	goto label;
	a := a+2;
	label: a := a+1;
	writeln(a);
end.



