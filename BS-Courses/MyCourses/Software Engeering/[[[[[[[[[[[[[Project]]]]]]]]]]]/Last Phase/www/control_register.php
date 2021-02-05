<?php
if(isset($_POST['username']) && isset($_POST['password']) && isset($_POST['rpassword']) && isset($_POST['Email']) )
{
	
	if (empty($_POST['username']) || empty($_POST['password']) || empty($_POST['rpassword']) || empty($_POST['Email']))
	{
		header('Location: /register.html');
		exit;
	}
	
	require_once('Moteghazi.inc');
	
	$mtz = new Moteghazi();
	
	if ($_POST['password'] == $_POST['rpassword'] )
	{
		$mtz->Register($_POST['username'],$_POST['rpassword'],$_POST['Email']);
		
	}
	else
	{
		echo "password is not same";
		header('Location: /register.html');
	}
	
	$user_id = $mtz->Login($_POST['username'],$_POST['password']);
	if($user_id)
	{
		session_start();
		
		$_SESSION['ValidUserID'] = $user_id;
		
		//unset($_SESSION['ValidUserID']);
		//session_destroy();
		
		header('Location: /myHome.php');
		
	}
	else
	{
		echo "Username or password is wrongh";
		
		//unset($_SESSION['ValidUserID']);
		//session_destroy();
	}

}
else
{
	echo "password is not same";
	header('Location: /register.html');
}
?>