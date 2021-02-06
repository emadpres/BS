1)
Select Student.sname
From Stundet, Reg
Where Stundet.sNo=Reg.sNo
AND Reg.year <> 1390

Select Student.sname
From Stundet INNER JOIN Reg ON Stundet.sNo=Reg.sNo
Where Reg.year <> 1390

Select Student.sname
From Student INNER JOIN 
	(Select DISTINCT sNo
	From Reg 
	minus Select DISTINCT sNo
	From Reg
	Where year=1390 ) as Temp ON Student.sNo = Temp.sNo

2)
Select Student.sname
From Stundet INNER JOIN Reg ON Stundet.sNo=Reg.sNo
Where (Reg.year=1389 OR Reg.year=1390) ;

3)
Select Class.cName, AVG(Score)
From Class INNER JOIN Score ON Score.cNo=Class.cNo
Group By Class.cName

4)
Select courseName, AVG(Score)
From Score
Group By courseName


5)
Select Teacher.tName, AVG(Score.score)
From Score ,Class, Teacher 
Where Score.cNo=Class.cNo AND Class.tNo=Teacher.tNo
Group By Teacher.tNo

6)
-- Each courseName + ClassNo that got Max Avg in that courseName
Select Temp.courseName, Temp.cNo
From ( Select courseName, cNo,  AVG(Score) as avgC
		From Score	
		Group By courseName, cNo) as Temp, ( Select Temp.courseName, MAX(Temp.avgC) as maxC
											From Temp
											Group By Temp.courseName ) as Temp2
Where Temp.courseName=Temp2.courseName AND Temp.avgC=Temp2.maxC

--( Part 6 _ FINAL ANSWER )
Select Teacher.tName
From Teacher, Class ( Select courseName, cNo,  AVG(Score) as avgC
		From Score	
		Group By courseName, cNo) as Temp, ( Select Temp.courseName, MAX(Temp.avgC) as maxC
											From Temp
											Group By Temp.courseName ) as Temp2
Where Temp.courseName=Temp2.courseName AND Temp.avgC=Temp2.maxC
AND Class.cNo=Temp.cNo AND Class.tNo=Teacher.tNo

7)
Select DISTINCT Teacher.tName, Student.sName
From Student, Reg, Class, Teacher
Where Student.sNo=Reg.sNo AND Reg.cNo=Class.cNo AND Class.tNo=Teacher.tNo
Order By Teacher.tName ASC, Student.sName ASC

8)
Select  Teacher.tName, Student.sName
From Student, Reg, Class, Teacher
Where Student.sNo=Reg.sNo AND Reg.cNo=Class.cNo AND Class.tNo=Teacher.tNo
Group By Teacher.tName, Student.sName
Having Count(*)>1

9)
Select Student.sName, Score.score, Temp.avgC
From Student, Score, (Select sNo, AVG(score) as avgC 
			From Score
			Group By sNo) as Temp
Where Student.sNo=Score.sNo AND Score.sNo=Temp.sNo
Order By Student.sName

10)
Select Student.sName
From Student,Reg
Where Student.sNo=Reg.sNo AND Not Exist ( Select *
										From Score
										Where Reg.cNo=Score.cNo 
										AND Reg.sNo=Score.sNo 
										AND Reg.year=Score.year)
				
11)
I)
Select tName
From Teacher, Class
Where Teacher.tNo=Class.tNo
	AND  Not Exist ( Select * From Score
					Where Class.cNo=Score.cNo )
II)
Select tNo
From Teacher,Class
Where Teacher.tNo=Class.tNo
minus Select Distinct  tNo
	From Score





	