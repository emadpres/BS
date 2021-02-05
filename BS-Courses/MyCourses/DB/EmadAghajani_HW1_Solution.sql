1)
	A.
	Select EatsAt.ResturantName
	From EatsAt, Person
	Where ( EatsAt.pname = Person.pname AND Person.age<18 ) ;
	
	B.
	Select Person.pname
	From Eats, Person
	Where ( Eats.pname = Person.pname AND Person.gender='male'
		AND ( Eats.foodname='X' OR Eats.foodname='Y') );
	
	C.
	Select Person.pname
	From Eats, Person
	Where ( Eats.pname = Person.pname AND Person.gender='male'
		AND Eats.foodname='X' AND Person.pname in( Select pname From Eats
													 Where foodName='Y' )
	
	D.
	Select ResturantMenue.ResturantName
	From EatsAt, Eats, ResturantMenue
	Where Eats.pname = EatsAt.pname AND Eats.foodName=ResturantMenue.foodName
		AND ResturantMenue.ResturantName=EatsAt.ResturantName AND price<5000 AND Eats.pname='P' ;
	
	E.I
	Select pname
	From Person
	Where ( Select COUNT(*) From EatsAt
				 Where EatsAt.pname = Persons.pname) =
			( Select COUNT(*) 
				From ( Select * From Eats
						Where pname=Person.pname ) as Fp, ( Select * From EatsAt
															Where EatsAt.pname = Persons.pname) as Rp
				Where Fp.foodName = Rp.foodname ); 		
	E.II
	Select DISTINCT Person.pName
	From Person, EatsAt, Eats, ResturantMenu
	Where Person.pName=EatsAt.pName AND Person.pName=Eats.pName 
	AND EatsAt.ResturantName=ResturantMenu.ResturantName
	AND Eats.foodName=ResturantMenu.foodName
	
	
2)
	A.I
	Select Student.*
	From Register, Student
	Where Student.sid=Register.sid AND Register.date<D 
		AND Register.cid IN ( Select cid From Cource Where prof='X' ) ;
	A.II
	Select Student.*
	From Register, Student, Cource
	Where Student.sid=Register.sid AND Register.date<D 
		AND Cource.prof='X' AND Cource.cid=Register.cid ;
	
	B.I
	select title
	From Cource
	Where cid IN ( Select cid From Register
					Where termNo='891' ) ;
	B.II
	select Cource.title
	From Cource, Register
	Where Cource.cid=Register.cid AND termNo='891' ;
	
	C.I
	Select *
	From Student
	Where Not Exist  ( Select * From Register
						Where Student.sid=sid );
	C.II
	Select sid, sname
	From Student
	minus Select Student.sid, Student.sname From Register, Student
			Where Register.sid=Student.sid ;
	
	D.I C1 AND C2 ?
	Select DISTINCT Stundet.*
	From Student, Cource as C1, Cource as c2, Register as R1, Resgister as R2
	Where Student.sid=R1.sid AND Student.sid=R2.sid
		AND R1.termNo='CurTermNo' AND R2.termNo='CurTermNo' 
		AND R1.cid = C1.cid AND C1.title='C1'
		AND R2.cid = C2.cid AND C2.title='C2'
	D.II C1 OR C2 ?
	Select DISTINCT Student.*
	From Student, Register, Cource
	Where Student.sid=Register.sid AND Register.termNo='CurTermNo'
		AND Register.cid = Cource.cid 
		AND ( Cource.title='C1' OR Cource.title='C2' )
	