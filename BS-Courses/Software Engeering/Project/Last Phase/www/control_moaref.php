<?php

	require('moaref.inc');

	session_start();
	if(!isset($_SESSION['ValidUserID']))
	{
		header('Location: /login.html');
		exit;
	}
	$mof = new moaref();
	
	$mof->addMoaref($_SESSION['ValidUserID'],$_POST['name'],$_POST['family'],$_POST['gerayesh'],$_POST['post']);
	
	//if (! empty($_POST['moaref']))
	//{
	//	$mof->AddMoaref($_SESSION['ValidUserID'],$_POST['moaref']);
	//}
	
	header('Location: /MyHome.php');
	exit;

?>