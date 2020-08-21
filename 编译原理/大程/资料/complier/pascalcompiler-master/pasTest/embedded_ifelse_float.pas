program exProcedure;
var
   a, b, c,  min: real;

begin
   a := 1.1;
   b := 2.2;
   c := 3.3;
   if (b < a) then 
      writeln("b<a")
   else 
      if (c<a) then
         writeln("c<a")
      else
         writeln("c>=a");
end.