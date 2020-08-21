program exProcedure;
var
   a, b, c,  min: integer;
procedure findMin(x, y, z: integer; var m: integer); 
(* Finds the minimum of the 3 values *)
begin
   if x < y then
      m:= x
   else
      m:= y;
   if z < m then
      m:= z;
end; 
begin
   writeln(" Enter three numbers: ");
   read(a);
   read(b);
   read(c);
   findMin(a, b, c, min); (* Procedure call *)
   writeln(" Minimum: ");
   writeln(min);
end.