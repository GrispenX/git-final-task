program next;

var
  a, b: integer;

begin
  read(a, b);
  WriteLn((abs(a) + abs(b)) - abs(a + b));
end.