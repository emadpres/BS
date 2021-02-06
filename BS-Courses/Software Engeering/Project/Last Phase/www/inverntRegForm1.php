<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">

<html>
<head>
	
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

<link rel="stylesheet" href="css/styles.css">
<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.7.1/jquery.min.js"></script>
		
<script type="text/javascript" language="javascript">
   <!--     
function chk_chkbox(form_item,input_name)
{
if (form_item.checked) 
{
document.getElementById(input_name+'_1').disabled = false; 
document.getElementById(input_name+'_2').disabled = false;
} 

else  
{
document.getElementById(input_name+'_1').checked = false; 
document.getElementById(input_name+'_2').checked = false; 
document.getElementById(input_name+'_1').disabled = true; 
document.getElementById(input_name+'_2').disabled = true;}
}

function addEvent_Div(div_name,input_name) {
	
switch (div_name) {
case "myDiv":
  var ni = document.getElementById(div_name);
  var numi = document.getElementById(input_name);
  var num = (document.getElementById(input_name).value -1)+ 2;
  numi.value = num;
  //var divIdName = "my"+num+"Div";
  var divIdName = "myDiv"+num;
  var newdiv = document.createElement('div');
  newdiv.setAttribute("id",divIdName);  
  //newdiv.innerHTML = "Element Number " + num + " has been added! <a href=\"javascript:;\" onclick=\"removeElement(\'"+divIdName+"\')\">Remove the element &quot;"+divIdName+"&quot;</a>";
  newdiv.innerHTML = "نام:<input id='fnameh"+num+"' name='fnameh' type='text' size='8'>	نام خانوادگی:<input id='lnameh"+num+"' name='lnameh' type='text' size='8'>&nbsp;کدملی:<input name='melli_codeh' type='text' size='8'>[<a href=\"javascript:;\" onclick=\"removeElement(\'"+div_name+"\',\'"+input_name+"\',\'"+divIdName+"\')\">حذف</a>]";
  ni.appendChild(newdiv);
	  new FarsiType.KeyObject(document.getElementById('fnameh'+num),  num );
	  new FarsiType.KeyObject(document.getElementById('lnameh'+num),  num );	  
break;      

case "db_sites_o_Div":
  var ni = document.getElementById(div_name);
  var numi = document.getElementById(input_name);
  var num = (document.getElementById(input_name).value -1)+ 2;
  numi.value = num;
  //var divIdName = "my"+num+"Div";
  var divIdName = "db_sites_o_Div"+num;
  var newdiv = document.createElement('div');
  newdiv.setAttribute("id",divIdName);  
  newdiv.innerHTML = "<input type='text' name='db_sites_o' size='60' dir='ltr' value=''  style='margin:0 5px 0 0;'>[<a href=\"javascript:;\" onclick=\"removeElement(\'"+div_name+"\',\'"+input_name+"\',\'"+divIdName+"\')\">حذف</a>]";  
  ni.appendChild(newdiv);
break;   
}
}

function removeElement(div_name,input_name,divNum) {
 //document.getElementById(input_name).value--;
  var d = document.getElementById(div_name);  
  var olddiv = document.getElementById(divNum);
  d.removeChild(olddiv);  
}
	
    //-->
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
		
<div align="center"><img src="images/help_2.gif" border="0"></div>

<div id="invention" align="center">
<form  method="POST" action = "control_Ekhtera.php" >
<table border="1" cellpadding="2" cellspacing="0" style="border-collapse: collapse" bordercolor="#CCCCCC" id="AutoNumber2" bgcolor="#FFFFFF" width="100%">
<input type="hidden" name="action" value="invention_preview">
     <tr>
        <td align="right" colspan="2" bgcolor="#E6E6E6" dir="rtl">
        <p align="center"><b><span lang="en-us"><font color="#FF5B24">.:</font><font color="#3366CC"> </font>
        </span><font color="#3366CC">کاربرگ مشخصات اختراع</font> <span lang="en-us">
        <font color="#FF5B24">:.</font></span></b><font color="#cc3300"><br></font><font color="#FF0000"><b>
		*<span lang="en-us"> </span></b></font><font color="#33333">پرکردن 
		فيلدهاي ستاره‌دار الزاميست.</font></td>
      </tr>
      <tr>
        
        <td dir="rtl" valign="top">
        <textarea rows="4" name="name" required="1" regexp="/^\w*$/" realname="عبارت" cols="50" lang="fa"></textarea></td>
        <td dir="rtl" valign="top" width="35%"> عنوان اختراع :<font color="#FF0000"><b>*</b></font><a href="tooltip.asp?width=375&action=h10" class="jTip" id="h10" name=""><img src="images/help.gif" border="0" align="absmiddle"></a></td>
      </tr>
     
      <tr>
        <td dir="rtl" valign="top">
		<input type="text" name="reg_id" required="1" regexp="/^\w*$/" realname="عبارت" size="30" dir="ltr"></td>
        <td dir="rtl" valign="top">شماره ثبت اختراع:<font color="#FF0000"><b>*</b></font><a href="tooltip.asp?width=375&action=h12" class="jTip" id="h12" name=""><img src="images/help.gif" border="0" align="absmiddle"></a></td>
      </tr>
      <tr>
        <td dir="rtl" valign="top">
  <select size="1" name="reg_rooz" dir="rtl" required="1" exclude="-1" realname="روز">
  <option value="-1">روز</option>
  <option value="1">1</option><option value="2">2</option><option value="3">3</option><option value="4">4</option><option value="5">5</option><option value="6">6</option><option value="7">7</option><option value="8">8</option><option value="9">9</option><option value="10">10</option><option value="11">11</option><option value="12">12</option><option value="13">13</option><option value="14">14</option><option value="15">15</option><option value="16">16</option><option value="17">17</option><option value="18">18</option><option value="19">19</option><option value="20">20</option><option value="21">21</option><option value="22">22</option><option value="23">23</option><option value="24">24</option><option value="25">25</option><option value="26">26</option><option value="27">27</option><option value="28">28</option><option value="29">29</option><option value="30">30</option><option value="31">31</option>  
  </select><span lang="en-us"> / </span>
	<select size="1" name="reg_mah" dir="rtl" required="1" exclude="-1" realname="ماه">
  <option value="-1">ماه</option>
  <option value="1">1</option><option value="2">2</option><option value="3">3</option><option value="4">4</option><option value="5">5</option><option value="6">6</option><option value="7">7</option><option value="8">8</option><option value="9">9</option><option value="10">10</option><option value="11">11</option><option value="12">12</option>	
	</select><span lang="en-us"> / </span>
	<select size="1" name="reg_sal" dir="rtl" required="1" exclude="-1" realname="سال">
  <option value="-1">سال</option>
  <option value="1391">1391</option><option value="1390">1390</option><option value="1389">1389</option><option value="1388">1388</option><option value="1387">1387</option><option value="1386">1386</option><option value="1385">1385</option><option value="1384">1384</option><option value="1383">1383</option><option value="1382">1382</option>
	
		</select>        
		</td>
        <td dir="rtl" valign="top">تاريخ ثبت اختراع:<font color="#FF0000"><b>*</b></font><a href="tooltip.asp?width=375&action=h13" class="jTip" id="h13" name=""><img src="images/help.gif" border="0" align="absmiddle"></a></td>
      </tr>
      <tr>
        <td dir="rtl" style="line-height:35px" valign="top">
<div style="font:11px tahoma; color:#000; background-color:#ff3; padding:2px; border:2px dotted #f60;">
		در صورتيکه نام اشخاصی حقوقی بعنوان ديگر مخترعان در گواهي ثبت اختراع ذکر شده است، نام آنها را در قسمت <span style="color:#f00;">نام</span> وارد نموده و قسمتهای <span style="color:#f00;">نام خانوادگی</span> و <span style="color:#f00;">کد ملی</span> را با خط فاصله (-) پر کنيد.
		</div>		
		نام:<input lang="fa" name="fnameh" type="text" size="8">
		نام خانوادگي:<input lang="fa" name="lnameh" type="text" size="8">
		کدملي:<input name="melli_codeh" type="text" size="8">
		<input type="hidden" value="0" id="theValue" />
		<div id="myDiv"> </div>
		[<a href="javascript:addEvent_Div('myDiv','theValue');">اضافه نمودن مخترع</a>]
        </td>
        <td dir="rtl" valign="top">ديگر مخترعان:<a href="tooltip.asp?width=375&action=h14" class="jTip" id="h14" name=""><img src="images/help.gif" border="0" align="absmiddle"></a>
		</td>
      </tr>
      <tr>
        <td dir="rtl" valign="top">
<input type="hidden" name="basis_pre" value="">
  <select size="1" name="basis" dir="rtl" required="1" exclude="-1" realname="گروه تخصصي" style="margin:0 0 5px 0" onchange="document.invention.basis_pre.value=this.form.basis.options[this.form.basis.selectedIndex].text;">
  <option value="-1">انتخاب کنيد</option>
  <option value="1">مهندسي برق و كامپيوتر</option><option value="2">مهندسي مكانيك</option><option value="3">شيمي و مهندسي شيمي</option><option value="4">مهندسي مواد و متالوژي</option><option value="5">انرژيهاي نو</option><option value="6">كشاورزي</option><option value="7">بيوتكنولوژي</option><option value="8">ساير</option>  
  </select>
</td>
        <td dir="rtl" valign="top">گروه تخصصي اختراع ارائه شده:<font color="#FF0000"><b>*</b></font><a href="tooltip.asp?width=500&action=h15" class="jTip" id="h15" name=""><img src="images/help.gif" border="0" align="absmiddle"></a></td>
      </tr>
      <tr>
        <td dir="rtl" valign="top">
        <textarea rows="12" name="memo" required="1" regexp="/^\w*$/" realname="عبارت" cols="60" lang="fa"></textarea></td>
        <td dir="rtl" valign="top">خلاصه اختراع:<font color="#FF0000"><b>*</b></font><a href="tooltip.asp?width=375&action=h16" class="jTip" id="h16" name=""><img src="images/help.gif" border="0" align="absmiddle"></a></td>
      </tr>
      <tr>
        <td dir="rtl" valign="top">
        <textarea rows="3" name="keywords" required="1" regexp="/^\w*$/" realname="عبارت" cols="40" lang="fa"></textarea></td>
        <td dir="rtl" valign="top">کليد واژه‌ها:<font color="#FF0000"><b>*</b></font><a href="tooltip.asp?width=375&action=h17" class="jTip" id="h17" name=""><img src="images/help.gif" border="0" align="absmiddle"></a></td>
      </tr>

      <tr>
        <td dir="rtl" valign="top">
        <textarea rows="12" name="sci_abs" required="1" regexp="/^\w*$/" realname="عبارت" cols="60" lang="fa"></textarea></td>
        <td dir="rtl" valign="top">شرح علمي و مشخصات فني اختراع را بطور کامل 
		بيان نمائيد:<font color="#FF0000"><b>*</b></font><a href="tooltip.asp?width=375&action=h19" class="jTip" id="h19" name=""><img src="images/help.gif" border="0" align="absmiddle"></a></td>
      </tr>

           <tr>
        <td dir="rtl" valign="top">        
        		     <input type="radio" name="r2" value="0" onclick="document.getElementById('db_site_o').style.display = 'none';" checked> 
						خير<span lang="en-us">
		</span>&nbsp;<input type="radio" name="r2" required="1" value="1" onclick="document.getElementById('db_site_o').style.display = '';"> 
						بلي
<div id="db_site_o" style="margin:5px 0; display:none">
مشخص کنيد:<br>
[<font size="1" color="#808080">مثال: http://www.irandoc.ac.ir يا http://www.google.com/patents</font>]<br>
<input type="text" name="db_sites_o" size="60" dir="ltr" value="" style="margin:0 5px 0 0;">
		<input type="hidden" value="0" id="db_sites_o_Value" />
		<div id="db_sites_o_Div" style="margin:5px;"> </div>
		[<a href="javascript:addEvent_Div('db_sites_o_Div','db_sites_o_Value');">اضافه نمودن سايت</a>]

</div>		     
        </td>
        <td dir="rtl" valign="top">آيا پايگاههاي اطلاعاتي (داخلي و خارجي) بمنظور 
		اطمينان از نو بودن موضوع اختراع مورد جستجو قرار گرفته‌اند؟<font color="#FF0000"><b>*</b></font><a href="tooltip.asp?width=375&action=h23" class="jTip" id="h23" name=""><img src="images/help.gif" border="0" align="absmiddle"></a></td>
      </tr>

      <tr>
        <td dir="rtl" valign="top">
        <div style="margin:5px 0"><input type="checkbox" name="c1" value="0" onchange="chk_chkbox(this,'c1');">&nbsp;توليد 
			محصول&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; (&nbsp;<input type="checkbox" name="c1" value="1"  id="c1_1" disabled>&nbsp;در 
			داخل کشور&nbsp;/&nbsp;<input type="checkbox" name="c1" value="2" id="c1_2" disabled>&nbsp;در خارج 
			کشور&nbsp;)</div>
        <div style="margin:5px 0"><input type="checkbox" name="c2" value="0" onchange="chk_chkbox(this,'c2');">&nbsp;فروش 
			محصول&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; (&nbsp;<input type="checkbox" name="c2" value="1" id="c2_1" disabled>&nbsp;در 
			داخل کشور&nbsp;/&nbsp;<input type="checkbox" name="c2" value="2" id="c2_2" disabled>&nbsp;در خارج 
			کشور&nbsp;)</div>
        
        <td dir="rtl" valign="top">اختراع در کدام يک از مراحل ذيل قرار دارد؟ با 
		ارائه مدارک و مستندات مشخص فرمائيد.<a href="tooltip.asp?width=375&action=h24" class="jTip" id="h24" name=""><img src="images/help.gif" border="0" align="absmiddle"></a></td>
      </tr>

      <tr>
        <td dir="rtl" valign="top" colspan="2">
        <div style="border: 1px solid #FF0000; background-color: #FFE88A; padding:5px">
        <input type="checkbox" name="agreement" value="" onclick="document.getElementById('plz').disabled = (this.checked)? false:true;">&nbsp; 
		اينجانب با اطلاع کامل از رويه‌ها و ضوابط ارائه اختراع، اين پرسشنامه را 
		تکميل نموده و کليه اطلاعات مندرج در آن را تأئيد مي‌نمايم. مسئوليت هرگونه 
		نقص يا اشتباه در اطلاعات ارسالي به عهده اينجانب است.</div>
        </td>
      </tr>

      <tr>
        <td align="right" colspan="2" bgcolor="#E6E6E6">
        <p align="center">
		<input name="send_but" type="submit" value="پيش نمايش" class="but"></td>
      </tr>      
    </table>
</form>	
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