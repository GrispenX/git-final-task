program apb;

var
  fut, duym:integer;
  meter:real;

begin
  readLn(fut);
  readLn(duym);
  meter := ((fut * 12 + duym) * 25.4) / 1000;
  writeLn(fut,'''', duym, '" = ', meter:0:2, 'm.');
end.  