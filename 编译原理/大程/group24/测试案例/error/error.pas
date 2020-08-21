program proc;
var a, b, c : integer; e : real;
   
function max(num1, num2: integer): integer;
var result: integer;
begin
      if (num1 > num2) then
      begin
         result := num1;
         result1 := num2;
      end
      else
      begin
         result := num2;
      end
      ;
      max := result + c;
end;

begin
   a := 100;
   b := 200;
   c := max(a, b);
   d := 100;
   c := max(a);
   c := maxi(a, b);
   e := "123";
   write(c);
end.
