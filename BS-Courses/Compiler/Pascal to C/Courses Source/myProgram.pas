program test(input,output);
var a,b,c:integer;
var d,e,f:real;
var g,h:array [3..8] of integer;
{Functions Declerations}
procedure proc1(pr:integer;z:real);
var s1,s2:integer;
var s3,s4:real;
begin
s1 := s1 * s2 ;
s3 := s1 mod s2
end;
function func1(x,y:integer;z:real):integer;
var i,j,l,m:integer;
var k:array [1..10] of real;
begin
l := 6 ;
h[HIGH] := 4;
m := 9 ;
i := 1 ;
j := 1 ;
while i < 10 do
begin
j := j * i ;
k[i] := j ;
i := i + 1
end;
if i < 20 then m := l * m else if i >= 20 then m := l / m else m := l mod m
end;
function func2(a:integer):real;{Func2 decleration}
var n,o:integer;
var h,p,q:real;{p and q is varriable}
begin
q := n * (o / 3) ;
p := a mod q ;
if n < 3 then o := 5 else if n > 3 then q := o + 7 else q := n - 4
end;
begin
a := func1(5,10,2.4);
b := a / 2 ;
c := a + b * 3 ;
h[HIGH] := 4;
e := 0.8E+3 ;
proc1(a);
h[4] := c ;
while a < b do
begin
a := a + 1 ;
d := c * a /b
end

end.