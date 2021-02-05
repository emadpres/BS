<?php

require('Moteghazi.inc');
require('ekhtera.inc');

$mtz = new Moteghazi();
$ekh = new ekhterat();

//$mtz->Register("hasan","hasan","a@a.a");

if($mtz->Login("hasan","hasan"))
{
	echo "true";
}
else
{
	echo "false";
}


$ekh->NewEkhtera("1","doogh");
$ekh->AddMoaref("1","boogh","man");
$temp = $ekh->GetEkhtera("1");
//print_r($temp);
echo $temp[0]['name'];

?>
