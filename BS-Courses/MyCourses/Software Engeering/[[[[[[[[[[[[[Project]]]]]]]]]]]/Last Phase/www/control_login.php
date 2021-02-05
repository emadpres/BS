<?php
if(isset($_POST['username']) && isset($_POST['password']))
{
	if (empty($_POST['username']) || empty($_POST['password']))
	{
		header('Location: /login.html');
		exit;
	}
	{
	}
	require_once('Moteghazi.inc');
	
	$mtz = new Moteghazi();
	
	$user_id = $mtz->Login($_POST['username'],$_POST['password']);
	if($user_id)
	{
		session_start();
		
		$_SESSION['ValidUserID'] = $user_id;
		
		//unset($_SESSION['ValidUserID']);
		//session_destroy();
		
		header('Location: /MyHome.php');
		
	}
	else
	{
		echo "Username or password is wrongh";
		
		header('Location: /login.html');
		
		//unset($_SESSION['ValidUserID']);
		//session_destroy();
	}

}
?>