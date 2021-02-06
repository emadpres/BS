<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">

<html>
<head>
		
		
<meta http-equiv="Content-Language" content="fa">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title> علمی و امتيازدهی اختراع :: توصيه کننده :.</title>
<link rel="stylesheet" type="text/css" href="css/nokhbegan.css">
<link rel="stylesheet" type="text/css" href="css/tooltip.css">
<link rel="stylesheet" type="text/css" href="css/Tablestylesheet.css">
<script type="text/javascript" language="javascript" src="js/farsitype.js"></script>
<script type="text/javascript" language="javascript" src="js/messages.js"></script>
<script type="text/javascript" language="javascript" src="js/form.js"></script>
<!--[if lt IE 7.]>
<script defer type="text/javascript" src="js/pngfix.js"></script>
<![endif]-->
<script src="js/jquery.js" type="text/javascript"></script>
<script src="js/jtip.js" type="text/javascript"></script>

<!--- MENUE -->
<link rel="stylesheet" href="css/styles.css">
<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.7.1/jquery.min.js"></script>
<script type="text/javascript">
			$(function() {
			
				var menu_ul = $('.menu > li > ul'),
					   menu_a  = $('.menu > li > a');
				
				menu_ul.hide();

				menu_a.click(function(e) {
					e.preventDefault();
					if(!$(this).hasClass('active')) {
						menu_a.removeClass('active');
						menu_ul.filter(':visible').slideUp('normal');
						$(this).addClass('active').next().stop(true,true).slideDown('normal');
					} else {
						$(this).removeClass('active');
						$(this).next().stop(true,true).slideUp('normal');
					}
				});
			
			});
		</script>
<!--- MENUE :: END -->
</head>

<body topmargin="1" leftmargin="0">

<div align="center">
<table border="0" cellpadding="0" style="border-collapse: collapse;" id="table2">

	<tr>
	
	<img border="0" src="images/logo.jpg">
	</tr>
	
	<!----->
		<tr>	
		<td bgcolor="#FFFFFF">
			<table id='vsTable' align = "center" >
				<tr>
					<td class='title' > توضیحات</td>
					<td class='title' > عنوان</td>
					<td class='title' > شماره</td>
				</tr>
				<?php
				session_start();

				if (! isset($_SESSION['ValidUserID']))
				{
					header('Location: /login.html');
					exit;
				}

				//echo $_SESSION['ValidUserID'];

			require('ekhtera.inc');
				
				$ekh = new ekhterat();
				$temp = $ekh->GetEkhtera($_SESSION['ValidUserID']);
				$counter = 0;
				foreach ($temp as $row)
				{
					$counter++;
					echo "<tr>";
					echo "<td>".$row['memo']."</td>";
					echo "<td>".$row['name']."</td>";
					echo "<td>".$counter."</td>";
					echo "</tr>";
				}
				?>
			</table>
			
		</td>
		
		<?php 
			require_once('Moteghazi.inc');
			require_once('Ekhtera.inc');
			//session_start();
			$mtz = new Moteghazi();
			$ekh = new ekhterat();
			
			$numEkh = $ekh->GetNumOfEkhtera($_SESSION['ValidUserID']);
			
			
			$username = $mtz->GetUsername($_SESSION['ValidUserID']);
			//$ali = $_SESSION['ValidUserID'];
			//echo "$username";
			//echo "$ali";
			//echo "$username"." خوش آمدید ";
		
		?>
		
		<td valign="top" width="180" bgcolor="#DDEDFB" dir="rtl">

			<ul class="menu">
				<li class="item5"><a href="#" align = center>شما</a>
					<ul>
						<li class="subitem1" align = center><a href="#"><?php echo "$username"." خوش آمدید "; ?></a></li>
					</ul>
				</li>
				<li class="item1"><a href="#" align = center>عملیات مخترع</a>
					<ul>
						<li class="subitem1" align = center><a href="inverntRegForm1.php">اختراع جدید</a></li>
						<li class="subitem1" align = center><a href="showEkhtera.php">کارنامه اختراعات<span><?php echo "$numEkh"; ?></span></a></li>
						<li class="subitem1" align = center><a href="inverntRegForm2.php">افزودن معرف</a></li>
					</ul>
				</li>
				<li class="item4"><a href="#" align = center>تنظیمات کاربر</a>
					<ul>
					<li class="subitem1" align = center><a href="editProfile.php">ویرایش اطلاعات شخصی</a></li>
						<li class="subitem2" align = center><a href="#">تغییر کلمه عبور</a></li>

					</ul>
				</li>
				<li class="item3"><a href="#" align = center>پیام ها<span><?php $payam = rand(0,10); echo "$payam"; ?></span></a>
					<ul>
						<li class="subitem1" align = center><a href="#">صندوق پیام ها</a></li>
						<li class="subitem2" align = center><a href="#">ارسال پبام جدید</a></li>
					</ul>
				</li>
				<li class="item2"><a href="#" align = center>خروج از سامانه<span>147</span></a>
					<ul>
						<li class="subitem1" align = center><div>آیا مطمئن هستید؟</div></li>
						<li class="subitem2" align = center><a href="logout.php">خروج</a></li>
					</ul>
				</li>
			</ul>

		</td>
		</tr>
	<tr>
		<td>
	<img border="0" src="images/bg_copyright.jpg"></td>
	</tr>
	
</table>
</div>
		
</body>