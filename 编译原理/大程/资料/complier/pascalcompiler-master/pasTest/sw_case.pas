program checkCase;
var
   grade: char;
begin
   grade := 'A';

   case (grade) of
      'A': writeln("A");
      'B': writeln("B");
   end;
end.