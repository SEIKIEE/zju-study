program proc;
var a, b, c : integer;
   
function max(num1, num2: integer): integer;
var result: integer;
begin
      if (num1 > num2) then
      begin
         result := num1;
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
   write(c);
end.