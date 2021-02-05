<?php
	session_start();
	if(isset($_SESSION['ValidUserID']))
	{
		header('Location: /MyHome.php');
	}
	else
	{
		header('Location: /login.html');
	}
?>