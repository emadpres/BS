<?php
require_once('Database.inc');

class ekhterat
{
	var $MyDB;
	function ekhterat()
	{
		$this->MyDB = new Database();
	}
	
	function NewEkhtera($user_id , $name , $memo = "", $reg_id="")
	{
		$query;
		if (isset($memo))
		{
			$query = "INSERT INTO ekhterat (user_id,name,memo,reg_id) VALUES ('$user_id','$name','$memo','$reg_id') ";
		}
		else
		{
			$query = "INSERT INTO ekhterat (user_id,name) VALUES ('$user_id','$name') ";
		}
		
		$ok = $this->MyDB->ExecQuery($query);
		if ($ok)
			return true;
		else
			return false;
	}
	
	function AddMemo($user_id , $name , $memo)
	{
		$query;
		
		$query = "UPDATE ekhterat SET memo = '$memo' WHERE user_id = '$user_id' AND name = '$name'";
		
		$ok = $this->MyDB->ExecQuery($query);
		if ($ok)
			return true;
		else
			return false;
	}
	
	function AddPoint($user_id , $name , $point)
	{
		$query;
		
		$query = "UPDATE ekhterat SET point = '$point' WHERE user_id = '$user_id' AND name = '$name'";
		
		$ok = $this->MyDB->ExecQuery($query);
		if ($ok)
			return true;
		else
			return false;
	}
	
	function AddMoaref($user_id , $name , $Moaref)
	{
		$query;
		
		$query = "UPDATE ekhterat SET Moaref = '$Moaref' WHERE user_id = '$user_id' AND name = '$name'";
		
		$ok = $this->MyDB->ExecQuery($query);
		if ($ok)
			return true;
		else
			return false;
	}
	
	function GetEkhtera($user_id)
	{
		$query;
		
	//	echo "XXXXXXXXXXXXXXXXXXXXXXX". $user_id."Xxxxxxxxxxxxxxxxx";
		
		$query = "SELECT name , memo , point , moaref FROM ekhterat WHERE user_id = '$user_id'";
		
		$ok = $this->MyDB->ExecQuery($query);
		
		return $this->MyDB->ReturnResult();
	}
	
	function GetNumOfEkhtera($user_id)
	{
		$query = "SELECT count(*) FROM ekhterat WHERE user_id = '$user_id'";
		
		$ok = $this->MyDB->ExecQuery($query);
		
		$temp =  $this->MyDB->ReturnResult();
		
		if (isset($temp) )
			return $temp[0][0];
		else
			return 0;
	}
}

?>