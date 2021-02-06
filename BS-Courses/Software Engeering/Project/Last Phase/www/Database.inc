<?php
class Database
{
	var $db;
	var $result;
	function Database()
	{
		$this->db = mysql_connect("localhost","root","");
		
		if (! $this->db)
		{
			echo "Error : connect to database";
			exit;
		}
		mysql_select_db('SE');
	}
	
	function ExecQuery($query)
	{
		$this-> result = mysql_query($query);
		return $this->result;
	} 
	
	function ReturnResult()
	{
		$num = mysql_num_rows($this -> result);
		
		$temp = array();
		for ($i = 0 ; $i<$num ; $i++)
		{
			$row = mysql_fetch_array($this->result);
			array_push($temp,$row);
			
		}
		
		return $temp;
	}
	
	function CloseDB()
	{
		return mysql_close($this -> db);
	}
}
?>