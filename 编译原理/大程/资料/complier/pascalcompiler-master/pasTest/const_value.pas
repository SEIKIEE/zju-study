program const_circle;
const PI = 3.1415926;
var
r, d, c : real; 
begin
   writeln("Enter the radius of the circle");
   read(r);
	d := 2.0 * r;
	c :=  PI * d;

   write("The circumference of the circle is ");
   writeln(c);
end.