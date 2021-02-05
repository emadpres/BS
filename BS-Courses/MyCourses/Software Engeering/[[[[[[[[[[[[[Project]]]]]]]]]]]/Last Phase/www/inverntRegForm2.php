<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">

<html>
<head>
		<link rel="stylesheet" href="css/styles.css">
		
		<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.7.1/jquery.min.js"></script>
		
<meta http-equiv="Content-Language" content="fa">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>.: سامانه ارزيابی علمی و امتيازدهی اختراع :: توصيه کننده :.</title>
<link rel="stylesheet" type="text/css" href="css/nokhbegan.css">
<link rel="stylesheet" type="text/css" href="css/tooltip.css">
<script type="text/javascript" language="javascript" src="js/farsitype.js"></script>
<script type="text/javascript" language="javascript" src="js/messages.js"></script>
<script type="text/javascript" language="javascript" src="js/form.js"></script>
<!--[if lt IE 7.]>
<script defer type="text/javascript" src="js/pngfix.js"></script>
<![endif]-->
<script src="js/jquery.js" type="text/javascript"></script>
<script src="js/jtip.js" type="text/javascript"></script>
<script type="text/javascript" language="javascript">
</script>
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
		
<div align="center"><img src="images/help_3.gif" border="0"></div>
<div style="width:auto; font:12px tahoma; background-color:#ff0; direction:rtl; text-align:right; padding:10px; line-height:20px">
<font color="#cc3300"><b>تذکر مهم:</b></font><br>
يكي از شرايط پذيرش تقاضا جهت ارزيابي علمي و امتيازدهي اختراع، دريافت توصيه 
نامه از يک فرد داراي شرايط زير مي باشد:<br>
الف - يکي از اعضاي هيات علمي دانشگاه ها و مراکز پژوهشي مورد تاييد وزارت 
علوم،تحقيقات و فناوري يا بهداشت،درمان و آموزش پزشکي با حداقل رتبه استادياري و 
تخصص در موضوع.<br>
ب - معاون پژوهشي و يا مسئول واحد پژوهشي سازمان مربوط براي شاغلين مراکز، موسسات، 
ادارات، کارخانجات و صنايع، به شرط آن که معاونت يا واحد مزبور مصوب و مورد تاييد 
يکي از دو وزارت مذکور باشد.<br>
روش انجام كار به اين صورت است كه مخترع ضمن هماهنگي قبلي با فرد داراي مشخصات ذکر 
شده و متخصص در موضوع اختراع، اقدام به معرفي و درج مشخصات آن فرد در قسمت زير 
نمايد. شايان ذکر است عمليات ارسال و دريافت اظهار نظر به صورت الکترونيکي و از 
طريق سازمان انجام مي شود.<br>
تذکر1: چنانچه اطلاعات مندرج در مورد توصيه کننده غير صحيح و يا تماس با ايشان غير 
ممکن باشد، بررسي در همان مرحله متوقف خواهد شد.<br>
تذكر2: نشاني الکترونيکي فرد توصيه كننده بايد خاص و متعلق به دانشگاه و يا مرکز 
پژوهشي كه در آن شاغل است، باشد.(مانند: ***@sharif.ir ، ***@Modares.ac.ir، 
***@iiees.ac.ir، ***@aut.ac.ir و ...)<br>
</div>
<div id="recommendation_msg"></div>
<form name="delete_recomm_file" method="POST" >
<input type="hidden" name="action" value="delete_recomm_file">
<input type="hidden" name="file_name" value="">
<input type="hidden" name="mellicode" value="">
<input type="hidden" name="invid" value="5937">
</form>
<div id="recommendation_div" align="center">
<table border="1" cellpadding="3" cellspacing="0" style="border-collapse: collapse" bordercolor="#CCCCCC" id="AutoNumber2" bgcolor="#FFFFFF">
<form name="recommendation" method="POST" action = "control_moaref.php">
<input type="hidden" name="action" value="recommendation">
<input type="hidden" name="invid" value="5937">

     <tr>
        <td align="right" colspan="2" bgcolor="#E6E6E6" dir="rtl">
        <p align="center"><b><span lang="en-us"><font color="#FF5B24">.:</font><font color="#3366CC"> </font>
        </span><font color="#3366CC">فرم مشخصات توصيه کننده</font> <span lang="en-us">
        <font color="#FF5B24">:.<br>
		</font></span></b><font color="#FF0000"><b>
		*<span lang="en-us"> </span></b></font><font color="#33333">پرکردن 
		فيلدهاي ستاره‌دار الزاميست.</font></td>
      </tr>
      <tr>
        
        <td dir="rtl">
  <input type="text" name="name" required="1" regexp="/^\w*$/" realname="عبارت" size="30" lang="fa"></td>
        <td dir="rtl" valign="top">نام:<font color="#FF0000"><b>*</b></font><a href="tooltip.asp?width=375&action=h26" class="jTip" id="h26" name=""><img src="images/help.gif" border="0" align="absmiddle"></a></td>
      </tr>
      <tr>
        <td dir="rtl">
  <input type="text" name="family" required="1" regexp="/^\w*$/" realname="عبارت" size="30" lang="fa"></td>
        <td dir="rtl" valign="top">نام خانوادگي:<font color="#FF0000"><b>*</b></font><a href="tooltip.asp?width=375&action=h26" class="jTip" id="h260" name=""><img src="images/help.gif" border="0" align="absmiddle"></a></td>
      </tr>
      <tr>
        <td dir="rtl">
        <textarea rows="3" name="gerayesh" required="1" regexp="/^\w*$/" realname="عبارت" cols="40" lang="fa"></textarea></td>
        <td dir="rtl" valign="top">مرتبه علمي:<font color="#FF0000"><b>*</b></font><a href="tooltip.asp?width=375&action=h27" class="jTip" id="h27" name=""><img src="images/help.gif" border="0" align="absmiddle"></a>
		<span style="font:10px tahoma; color:#999">
		مرتبه علمي از استاديار به بالا قابل قبول مي باشد.(استاد – دانشيار – استاديار)
		<span>
		</td>
      </tr>
      <tr>
        <td dir="rtl">
        <textarea rows="3" name="trend" required="1" regexp="/^\w*$/" realname="عبارت" cols="40" lang="fa"></textarea></td>
        <td dir="rtl" valign="top">گرايش تخصصي:<font color="#FF0000"><b>*</b></font>		
		</td>
      </tr>	  
      <tr>
        <td dir="rtl">
        <textarea rows="3" name="post" required="1" regexp="/^\w*$/" realname="عبارت" cols="40" lang="fa"></textarea></td>
        <td dir="rtl" valign="top">سمت:<font color="#FF0000"><b>*</b></font><a href="tooltip.asp?width=375&action=h28" class="jTip" id="h28" name=""><img src="images/help.gif" border="0" align="absmiddle"></a></td>
      </tr>
      <tr>
        <td dir="rtl" valign="top">
		<div style="font:11px tahoma; color:#000; background-color:#ff3; padding:2px; border:2px dotted #f60;">
	نشاني الکترونيکي بايد متعلق به 
		دانشگاه يا مرکز پژوهشي
		که توصيه کننده در آن شاغل است، باشد.
		</div>		
  <input type="text" name="mail" required="1" regexp="JSVAL_RX_EMAIL" realname="نشاني الکترونيکي" size="40" class="inputs" dir="ltr"></td>
        <td dir="rtl" valign="top">نشاني الکترونيکي (خاص):<font color="#FF0000"><b>*</b></font><a href="tooltip.asp?width=375&action=h29" class="jTip" id="h29" name=""><img src="images/help.gif" border="0" align="absmiddle"></a>
		</td>
      </tr>
      <tr>
        <td dir="rtl">
        <textarea rows="3" name="work_loc" required="1" regexp="/^\w*$/" realname="عبارت" cols="40" lang="fa"></textarea>
        </td>
        <td dir="rtl" valign="top">نام محل کار:<font color="#FF0000"><b>*</b></font></td>
      </tr>
      <tr>
        <td dir="rtl">
  <input type="text" name="tel" required="1" regexp="JSVAL_RX_TEL" realname="تلفن" size="20" dir="ltr" ></td>
        <td dir="rtl" valign="top">تلفن محل کار:<font color="#FF0000"><b>*</b></font><a href="tooltip.asp?width=375&action=h30" class="jTip" id="h30" name=""><img src="images/help.gif" border="0" align="absmiddle"></a>
		<span style="font:10px tahoma; color:#999">
		ابتدا کد، سپس شماره تلفن و داخلي احتمالي در داخل پرانتز درج گردد.
		<br>
		مثال براي مشهد:<br>(900)05117172654
		<span>
		</td>
      </tr>
      <tr>
        <td dir="rtl">
  <input type="text" name="mobile" size="20" dir="ltr"></td>
        <td dir="rtl" valign="top">تلفن همراه:
		</td>
      </tr>	  
      <tr>
        <td dir="rtl">
        <textarea rows="3" name="address" required="1" regexp="/^\w*$/" realname="عبارت" cols="40" lang="fa"></textarea>
        </td>
        <td dir="rtl" valign="top">نشاني محل کار:<font color="#FF0000"><b>*</b></font><a href="tooltip.asp?width=375&action=h31" class="jTip" id="h31" name=""><img src="images/help.gif" border="0" align="absmiddle"></a></td>
      </tr>
      <tr>
        <td dir="rtl" valign="top"> 
<div id="delete_peyvast_files_msg"></div>		

<div id="uploaded_file" style="display:none"></div>
<div id="attach_radio">
     <input type="radio" name="r2" value="0" onclick="document.getElementById('f1_upload_form').style.display = 'none';" checked> خير
&nbsp;<input type="radio" name="r2" required="1" value="1" onclick="document.getElementById('f1_upload_form').style.display = '';"> بلي
</div>
   <div id="f1_upload_process" style="display:none">در حال ضميمه کردن فايل...&nbsp;<img src="images/loading.gif" /><br/></div>
   <div id="f1_upload_form"  style="margin:15px 0; text-align:center; display:none">
انتخاب فايل:
<input type="file" name="attach_recomm_file" size="40">
<input type="submit" name="sub_but" class="but" value="ضميمه کن"  onClick="document.pressed='upload';"/>        
    </div>   
	
    <iframe  src="#" style="width:0;height:0;border:0px solid #fff;"></iframe>
        </td>
        <td dir="rtl" valign="top">ارسال توصيه نامه به صورت فايل ضميمه:
		<br>
		<span style="font:10px tahoma; color:#666; line-height:18px">
		- سربرگ و مهر تأئيد کننده توصيه نامه بايد با نام محل کار توصيه کننده درج شده در اين فرم مطابقت داشته باشد.<br>
		<span lang="en-us">-</span> محدوديت حجم فايل ارسالي
		حداکثر <span lang="en-us">2MB</span> ميباشد.<br>
		- تنها فايلهاي با فرمت <span lang="en-us">ZIP,PDF,DOC,GIF,JPG</span> اجازه ارسال دارند.
		</span>
		</td>
      </tr>
      <tr>
        <td align="right" colspan="2" bgcolor="#E6E6E6">
		<input type="hidden" name="file_name" value="">
        <p align="center">
	<input type="submit" value="ارسال" class="but">
		</td>
      </tr>
	 
<input type="hidden" name="but_val" value="">	  
</form>      
    </table>
    		</div>			

		</td>

		
		
		<?php 
			require_once('Moteghazi.inc');
			require_once('Ekhtera.inc');
			session_start();
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