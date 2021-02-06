<?php
require_once('Database.inc');

class moaref
{
	var $MyDB;
	function moaref()
	{
		$this->MyDB = new Database();
	}
	
	function addMoaref($user_id,$name ,$family , $gerayesh , $post)
	{
		$query = "INSERT INTO moaref (user_id ,name , family , gerayesh , post) VALUES ('$user_id','$name','$family','$gerayesh', '$post')";
		
		$this->MyDB->ExecQuery($query);
		
		return;
	}
}