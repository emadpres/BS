<?php
require_once('Database.inc');

class Moteghazi
{
	var $MyDB;
	function Moteghazi()
	{
		$this->MyDB = new Database();
	}
	
	function Register($username , $password , $Email)
	{
		$password = md5($password);
		
		$query = "INSERT INTO moteghazi (username , password , email) VALUES ('$username','$password','$Email')";
		
		return $this->MyDB->ExecQuery($query);
	}
	
	function Login($username , $password)
	{
		$password = md5($password);
		
		$query = "SELECT password,id FROM moteghazi WHERE username = '$username'";
		
		$this->MyDB->ExecQuery($query);
		
		$result = $this->MyDB->ReturnResult();
		
		if (isset($result[0]['password']))
		{
			if ($result[0]['password'] == $password)
				return $result[0]['id'];
			else
				return false;
		}
		else
			return false;
		
	}
	
	function GetUsername($user_id)
	{
		$query = "SELECT username FROM moteghazi WHERE id = '$user_id'";
		
		$this->MyDB->ExecQuery($query);
		
		$result = $this->MyDB->ReturnResult();
		
		if (isset($result[0]['username']))
			return $result[0]['username'];
		else
			return "error";
	}
}
?>