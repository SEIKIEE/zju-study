program opcode;
	var a, b, c: integer;
begin
	a := 123;
	b := 456;
	c := a + b;
	writeln(c);		(* 579 *)
	c := a - b;		
	writeln(c);		(* -333 *)
	c := a * b;
	writeln(c);		(* 56088 *)
	c := a div b;
	writeln(c);		(* 0 *)
	c := a mod b;	
	writeln(c);		(* 123 *)
	c := a or b;	
	writeln(c);		(* 507 *)
	c := a and b;
	writeln(c);		(* 72 *)
(* embedded test*)
	c := a+b-c + a and b or c  - (a + c);
	writeln(c);		(* 579 or 72  - 195  392 *)
end.