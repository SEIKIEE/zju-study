program xunhuan;
var num :integer;
begin
	for num :=1 to 3 do
		num := num +1;
	writeln(num);	(* 4 *)
	num := 1;
	while num<5 do
	begin
		num := num+1;
	end;
	writeln(num);		(* 5 *)
	num := 1;
	repeat
		num := num +1;
		num := num+1;
	until num = 9;
	writeln(num);		(* 9 *)
end.