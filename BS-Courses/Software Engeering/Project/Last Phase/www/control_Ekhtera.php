<?php
if(isset($_POST['name']) && isset($_POST['memo']) )
{
	
	if (empty($_POST['name']))
	{
		header('Location: /newEkhtera.html');
		exit;
	}
	
	
	session_start();
	if(!isset($_SESSION['ValidUserID']))
	{
		header('Location: /login.html');
		exit;
	}
	
	require('ekhtera.inc');
	$ekh = new ekhterat();
	
	$ekh->NewEkhtera($_SESSION['ValidUserID'],$_POST['name'],$_POST['memo'],$_POST['reg_id']);
	
	//if (! empty($_POST['moaref']))
	//{
	//	$ekh->AddMoaref($_SESSION['ValidUserID'],$_POST['moaref']);
	//}
	
	header('Location: /MyHome.php');
	exit;
}
?>