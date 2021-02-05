var mypath = "/";
isIE=document.all;
isNN=!document.all&&document.getElementById;
isN4=document.layers;

function hideMe(param){
  if (isIE||isNN) document.getElementById("form_output_msg").style.visibility="hidden";
  else if (isN4) document.form_output_msg.visibility="hide";
  if (param.length>1)
  location.href = param;
}

function hidePre(){
if (isIE||isNN) document.getElementById("preview_inv").style.visibility="hidden";
else if (isN4) document.preview_inv.visibility="hide";
document.getElementById("preview_inv").innerHTML = "";
}

function keyPressHandler(e) {
e = e? e : window.event;
var keycode = e.keyCode? e.keyCode : e.which? e.which : null;
return (keycode==27)? true:false;         
 }
 
 function trim(str) {
	str = str.replace(/^\s+/, '');
	for (var i = str.length - 1; i >= 0; i--) {
		if (/\S/.test(str.charAt(i))) {
			str = str.substring(0, i + 1);
			break;
		}
	}
	return str;
}


function diving_msg(msg_txt,msg_type,locs)
{
if (msg_txt)
{
var div_start = "<div dir=\"rtl\" id=\"form_output_msg\"><a href=\"javascript:;\" onClick=\"hideMe('" + locs + "');return false\">&nbsp;<b>x ???? ??? ?????</b></a><br><br>";
var div_err = div_start + "<div id=\"into\"><img src=\"" +  mypath + "images/stop.png\" border=\"0\"><br><br>";
var div_ok  = div_start + "<div id=\"into\"><img src=\"" + mypath + "images/check.gif\" border=\"0\"><br><br>";
var div_end = "</div></div>";

var msg_err = div_err + eval(msg_txt) + div_end;
var msg_ok = div_ok + eval(msg_txt) + div_end;

document.onkeypress = function () {
//if (keyPressHandler && document.getElementById('form_output_msg')) {
if (keyPressHandler) {
if (document.getElementById('form_output_msg'))
document.getElementById('form_output_msg').style.visibility="hidden";
if (locs.length>1)
{
document.location.href = locs;
return false;
}
return true;
}
}
return (msg_type == 1)? msg_ok:msg_err;
}
else
location.href = locs;
}


function logoff(formname)
{
if (confirm("??? ????? ??????\n\nAre You Sure?\n"))
{
if (document.forms[formname].onsubmit())
	document.forms[formname].submit();
}
else
return false;
}

function xmlhttpPost(strURL,formname,responsediv,responsemsg) {
    var xmlHttpReq = false;
    var self = this;
    // Xhr per Mozilla/Safari/Ie7
    if (window.XMLHttpRequest) {
        self.xmlHttpReq = new XMLHttpRequest();
    }
    // per tutte le altre versioni di IE
    else if (window.ActiveXObject) {
        self.xmlHttpReq = new ActiveXObject("Microsoft.XMLHTTP");
    }
    self.xmlHttpReq.open('POST', strURL, true);
    self.xmlHttpReq.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
    self.xmlHttpReq.onreadystatechange = function() {
        if (self.xmlHttpReq.readyState == 4) {
			// Quando pronta, visualizzo la risposta del form
            updatepage(self.xmlHttpReq.responseText,responsediv);
        }
		else{
			// In attesa della risposta del form visualizzo il msg di attesa
			updatepage(responsemsg,responsediv);

		}
    }
    self.xmlHttpReq.send(getquerystring(formname));
}

function getquerystring(formname) {
    var form = document.forms[formname];
	var qstr = "";

    function GetElemValue(name, value) {
        qstr += (qstr.length > 0 ? "&" : "")
            + escape(name).replace(/\+/g, "%2B") + "="
            + escape(value ? value : "").replace(/\+/g, "%2B");
			//+ escape(value ? value : "").replace(/\n/g, "%0D");
    }
	
	var elemArray = form.elements;
    for (var i = 0; i < elemArray.length; i++) {
        var element = elemArray[i];
        var elemType = element.type.toUpperCase();
        var elemName = element.name;
        if (elemName) {
            if (elemType == "TEXT"
                    || elemType == "TEXTAREA"
                    || elemType == "PASSWORD"
					|| elemType == "BUTTON"
					|| elemType == "RESET"
					|| elemType == "SUBMIT"
					|| elemType == "FILE"
					|| elemType == "IMAGE"
                    || elemType == "HIDDEN")
                GetElemValue(elemName, element.value);
            else if (elemType == "CHECKBOX" && element.checked)
                GetElemValue(elemName, 
                    element.value ? element.value : "On");
            else if (elemType == "RADIO" && element.checked)
                GetElemValue(elemName, element.value);
            else if (elemType.indexOf("SELECT") != -1)
                for (var j = 0; j < element.options.length; j++) {
                    var option = element.options[j];
                    if (option.selected)
                        GetElemValue(elemName,
                            option.value ? option.value : option.text);
                }
        }
    }
    return qstr;
}
function updatepage(str,responsediv){
var div_msg="";
switch (str){
case "err_register_again":
case "err_register_mistake_captcha":
case "err_login_mistake_mail_or_pass":
case "err_login_not_active_user":
case "err_change_pass_mistake_password":
case "err_admin_login_mistake_mail_or_pass":
case "err_admin_forget_pass_not_exist_mail":
case "err_admin_change_pass_mistake_password":
case "err_documents_is_incomplete":
case "err_recommand_mistake_pass":
case "err_expert_referee_result_isnot_ok_comments":
case "err_setad_login_mistake_mail_or_pass":
case "err_forget_pass_not_exist_mail":
case "err_invention_user_register_more_than_one":
case "err_invention_register_again":
case "err_complete_registering":
case "err_no_attachment_exist":	
case "err_select_atleast_one_item":
case "err_hamkaran_info_is_faculty":
case "err_select_marja_or_select_no":
case "err_insert_site_address_or_select_no":
case "err_repeat_mail":
case "err_q1_not_response":
case "err_q1_comment_not_response":
case "err_q2_not_response":
case "err_q2_comment_not_response":
case "err_q3_not_response":
case "err_q3_comment_not_response":
case "err_q4_not_response":
case "err_q4_comment_not_response":
case "err_q5_comment_not_response":
case "err_q6_not_response":
case "err_q6_comment_not_response":
case "err_q7_not_response":
case "err_q7_comment_not_response":
case "err_q8_not_response":
case "err_q8_comment_not_response":
case "err_insert_valid_num":
case "err_insert_valid_num_for_score":
case "err_score_is_out_of_range":
case "err_sell_score_is_out_of_range":
div_msg = diving_msg(str,0,"");
//1: success msg 0: error msg
//document.getElementById('emtiaz11').focus();
//document.getElementById('emtiaz11').select();
break;

case "msg_register_success":
case "msg_forget_pass_send_success":
case "msg_change_pass_success":
case "msg_admin_forget_pass_send_success":
case "msg_admin_change_pass_success":
case "msg_expert_mail_to_referee":
case "msg_setad_alert_send_successfully":
case "msg_faq_new_q_insert_success":
case "msg_expert_sending_mail_to_inventor":
case "msg_expert_recommend_inventor_alert_mail":
case "msg_expert_permit_inv_change_recomm":
case "msg_delete_recomm_files":
case "msg_hami_ok_establish":
case "msg_register_davar_success":
case "msg_davar_saved_info":
div_msg = diving_msg(str,1,"");
break;

case "err_invention_invalid_user":
case "err_recommandation_invalid_user":
case "err_recommend_access_closed":
div_msg = diving_msg(str,0,mypath);
break;

case "msg_recommandation_success":
div_msg = diving_msg(str,1,mypath+'inv_log.asp');
break;

case "msg_inventor_registering_data_updated":
case "msg_complete_registering":
case "msg_invention_register_success":
div_msg = diving_msg(str,1,mypath+'register.asp');
break;

case "user_logoff_success":
div_msg = diving_msg('',0,mypath+'register.asp');
break;

case "msg_item_delete_success":
case "success_login":
case "bonyad_success_login":
case "bonyad_success_logoff":
case "expert_success_login":
case "expert_success_logoff":
case "referee_logoff_success":
case "site_admin_success_login":
case "site_admin_success_logoff":
case "setad_success_login":
case "setad_success_logoff":
case "recomm_success_login":
case "expert_virtual_delete_success":
location.href = location.href;
break;

case "msg_recommand_send_success":
case "msg_user_edit_form_and_edit_peyvast":
case "msg_user_edit_form":
case "msg_delete_peyvast_files":
case "msg_new_expert_registered":
case "msg_expert_register_form_updated":
case "msg_new_site_admin_registered":
case "msg_site_admin_form_updated":
case "msg_setad_data_updated":
case "msg_site_admin_faq_insert_success":
case "msg_site_admin_faq_update_success":
case "msg_site_admin_links_insert_success":
case "msg_site_admin_links_update_success":
case "msg_admin_subject_add_success":
case "msg_admin_subject_edit_success":
case "msg_site_admin_ayeen_insert_success":
case "msg_site_admin_ayeen_update_success":
case "msg_new_q_answered_success":
case "msg_new_q_add_to_faq_success":
case "msg_admin_send_mail_to_recommand_success":
case "msg_documents_is_complete":
case "msg_documents_is_incomplete_open_edit":
case "msg_expert_select_referee":
case "msg_expert_referee_result_is_ok":
case "msg_referee_again":
case "msg_request_is_no_accept_and_send_to_setad":
case "msg_expert_jump_to_next_level":
case "msg_expert_veto_inv_send_setad":
case "msg_expert_send_reject_inv_to_setad":
case "msg_expert_change_referee":
case "msg_documents_is_incomplete_from_setad_to_expert":
case "msg_invention_send_to_bonyad":
case "msg_complete_editing_registering":	
case "msg_create_list":
case "msg_score_registered":
case "msg_hami_center_registered":
case "msg_hami_center_updated":
case "msg_referee_registering_data_updated":
case "msg_referee_accept_invention":
case "msg_referee_donot_accept_invention":
case "msg_referee_result_updated":
div_msg = diving_msg(str,1,location.href);
break;

default:
div_msg = str;

}
document.getElementById(responsediv).innerHTML = div_msg;
//for (var j=0;j<document.getElementsByTagName('DIV').length; ++j)
//if (document.getElementsByTagName('DIV')[j].id == 'form_output_msg')
//	document.getElementsByTagName('DIV')[j].focus();
}

function validateCompleteForm(objForm,strErrorClass){
return _validateInternal(objForm,strErrorClass,0);
};
function validateStandard(objForm,strErrorClass,flg,formname,strURL,responsediv,responsemsg){
return _validateInternal(objForm,strErrorClass,1,flg,formname,strURL,responsediv,responsemsg);
};
function _validateInternal(form,strErrorClass,nErrorThrowType, flg,formname,strURL,responsediv,responsemsg){
var strErrorMessage="";var objFirstError=null;
if(nErrorThrowType==0){
strErrorMessage=(form.err)?form.err:_getLanguageText("err_form");
};
var fields=_GenerateFormFields(form);
for(var i=0;i<fields.length;++i){
var field=fields[i];
if(!field.IsValid(fields)){
field.SetClass(strErrorClass);
if(nErrorThrowType==1){
_throwError(field);
return false;
}else{
if(objFirstError==null){
objFirstError=field;
}
strErrorMessage=_handleError(field,strErrorMessage);
bError=true;
}
}else{
field.ResetClass();
}
};
if(objFirstError!=null){
alert(strErrorMessage);
objFirstError.element.focus();
return false;
};

if (!flg)
{
xmlhttpPost(strURL,formname,responsediv,responsemsg);
return false;
}
else
return true;

};
function _getLanguageText(id){
objTextsInternal=new _jsVal_Language();
objTexts=null;
try{
objTexts=new jsVal_Language();
}catch(ignored){};
switch(id){
case "err_form":strResult=(!objTexts||!objTexts.err_form)?objTextsInternal.err_form:objTexts.err_form;break;
case "err_enter":strResult=(!objTexts||!objTexts.err_enter)?objTextsInternal.err_enter:objTexts.err_enter;break;
case "err_select":strResult=(!objTexts||!objTexts.err_select)?objTextsInternal.err_select:objTexts.err_select;break;
};
return strResult;
};
function _GenerateFormFields(form){
var arr=new Array();
for(var i=0;i<form.length;++i){
var element=form.elements[i];
var index=_getElementIndex(arr,element);
if(index==-1){
arr[arr.length]=new Field(element,form);
}else{
arr[index].Merge(element)
};
};
return arr;
};
function _getElementIndex(arr,element){
if(element.name){
var elementName=element.name.toLowerCase();
for(var i=0;i<arr.length;++i){
if(arr[i].element.name){
if(arr[i].element.name.toLowerCase()==elementName){
return i;
}
};
};
}
return -1;
};
function _jsVal_Language(){
this.err_form="???? ???? ???????? ??? ????? ????? ??????/???? ????:\n\n";
this.err_select="???? ?? ???? ?? \"%FIELDNAME%\" ?? ?????? ????";
this.err_enter="???? \"%FIELDNAME%\" ????? ???? ????.";
};
function Field(element,form){
this.type=element.type;
this.element=element;
this.exclude=element.exclude||element.getAttribute('exclude');
this.err=element.err||element.getAttribute('err');
this.required=_parseBoolean(element.required||element.getAttribute('required'));
this.realname=element.realname||element.getAttribute('realname');
this.elements=new Array();
switch(this.type){
case "textarea":
case "password":
case "text":
case "file":
this.value=trim(element.value);
this.minLength=element.minlength||element.getAttribute('minlength');
this.maxLength=element.maxlength||element.getAttribute('maxlength');
this.regexp=this._getRegEx(element);
this.minValue=element.minvalue||element.getAttribute('minvalue');
this.maxValue=element.maxvalue||element.getAttribute('maxvalue');
this.equals=element.equals||element.getAttribute('equals');
this.callback=element.callback||element.getAttribute('callback');
break;
case "select-one":
case "select-multiple":
this.values=new Array();
for(var i=0;i<element.options.length;++i){
if(element.options[i].selected&&(!this.exclude||element.options[i].value!=this.exclude)){
this.values[this.values.length]=element.options[i].value;
}
}
this.min=element.min||element.getAttribute('min');
this.max=element.max||element.getAttribute('max');
this.equals=element.equals||element.getAttribute('equals');
break;
case "checkbox":
this.min=element.min||element.getAttribute('min');
this.max=element.max||element.getAttribute('max');
case "radio":
this.required=_parseBoolean(this.required||element.getAttribute('required'));
this.values=new Array();
if(element.checked){
this.values[0]=element.value;
}
this.elements[0]=element;
break;
};
};
Field.prototype.Merge=function(element){
var required=_parseBoolean(element.getAttribute('required'));
if(required){
this.required=true;
};
if(!this.err){
this.err=element.getAttribute('err');
};
if(!this.equals){
this.equals=element.getAttribute('equals');
};
if(!this.callback){
this.callback=element.getAttribute('callback');
};
if(!this.realname){
this.realname=element.getAttribute('realname');
};
if(!this.max){
this.max=element.getAttribute('max');
};
if(!this.min){
this.min=element.getAttribute('min');
};
if(!this.regexp){
this.regexp=this._getRegEx(element);
};
if(element.checked){
this.values[this.values.length]=element.value;
};
this.elements[this.elements.length]=element;
};
Field.prototype.IsValid=function(arrFields){
switch(this.type){
case "textarea":
case "password":
case "text":
case "file":
return this._ValidateText(arrFields);
case "select-one":
case "select-multiple":
case "radio":
case "checkbox":
return this._ValidateGroup(arrFields);
default:
return true;
};
};
Field.prototype.SetClass=function(newClassName){
if((newClassName)&&(newClassName!="")){
if((this.elements)&&(this.elements.length>0)){
for(var i=0;i<this.elements.length;++i){
if(this.elements[i].className!=newClassName){
this.elements[i].oldClassName=this.elements[i].className;
this.elements[i].className=newClassName;
}
}
}else{
if(this.element.className!=newClassName){
this.element.oldClassName=this.element.className;
this.element.className=newClassName;
}
};
}
};
Field.prototype.ResetClass=function(){
if((this.type!="button")&&(this.type!="submit")&&(this.type!="reset")){
if((this.elements)&&(this.elements.length>0)){
for(var i=0;i<this.elements.length;++i){
if(this.elements[i].oldClassName){
this.elements[i].className=this.elements[i].oldClassName;
}
else{
this.element.className="";
}
}
}else{
if(this.elements.oldClassName){
this.element.className=this.element.oldClassName;
}
else{
this.element.className="";
}
};
};
};
Field.prototype._getRegEx=function(element){
regex=element.regexp||element.getAttribute('regexp')
if(regex==null)return null;
retype=typeof(regex);
if(retype.toUpperCase()=="FUNCTION")
return regex;
else if((retype.toUpperCase()=="STRING")&&!(regex=="JSVAL_RX_EMAIL")&&!(regex=="JSVAL_RX_TEL")
&&!(regex=="JSVAL_RX_PC")&&!(regex=="JSVAL_RX_ZIP")&&!(regex=="JSVAL_RX_MONEY")
&&!(regex=="JSVAL_RX_CREDITCARD")&&!(regex=="JSVAL_RX_POSTALZIP"))
{
nBegin=0;nEnd=0;
if(regex.charAt(0)=="/")nBegin=1;
if(regex.charAt(regex.length-1)=="/")nEnd=0;
return new RegExp(regex.slice(nBegin,nEnd));
}
else{
return regex;
};
};
Field.prototype._ValidateText=function(arrFields){
if((this.required)&&(this.callback)){
nCurId=this.element.id?this.element.id:"";
nCurName=this.element.name?this.element.name:"";
eval("bResult = "+this.callback+"('"+nCurId+"', '"+nCurName+"', '"+this.value+"');");
if(bResult==false){
return false;
};
}else{
if(this.required&&!this.value){
return false;
};
if(this.value&&(this.minLength&&this.value.length<this.minLength)){
return false;
};
if(this.value&&(this.maxLength&&this.value.length>this.maxLength)){
return false;
};
if(this.regexp){
if(!_checkRegExp(this.regexp,this.value))
{
if(!this.required&&this.value){
return false;
}
if(this.required){
return false;
}
}
else
{
return true;
};
};
if(this.equals){
for(var i=0;i<arrFields.length;++i){
var field=arrFields[i];
if((field.element.name==this.equals)||(field.element.id==this.equals)){
if(field.element.value!=this.value){
return false;
};
break;
};
};
};
if(this.required){
var fValue=parseFloat(this.value);
if((this.minValue||this.maxValue)&&isNaN(fValue)){
return false;
};
if((this.minValue)&&(fValue<this.minValue)){
return false;
};
if((this.maxValue)&&(fValue>this.maxValue)){
return false
};
};
}
return true;
};
Field.prototype._ValidateGroup=function(arrFields){
if(this.required&&this.values.length==0){
return false;
};
if(this.required&&this.min&&this.min>this.values.length){
return false;
};
if(this.required&&this.max&&this.max<this.values.length){
return false;
};
return true;
};
function _handleError(field,strErrorMessage){
var obj=field.element;
strNewMessage=strErrorMessage+((field.realname)?field.realname:((obj.id)?obj.id:obj.name))+"\n";
return strNewMessage;
};
function _throwError(field){
var obj=field.element;
switch(field.type){
case "text":
case "password":
case "textarea":
case "file":
alert(_getError(field,"err_enter"));
try{
obj.focus();
}
catch(ignore){}
break;
case "select-one":
case "select-multiple":
case "radio":
case "checkbox":
alert(_getError(field,"err_select"));
try{
obj.focus();
}
catch(ignore){}
break;
};
};
function _getError(field,str){
var obj=field.element;
strErrorTemp=(field.err)?field.err:_getLanguageText(str);
idx=strErrorTemp.indexOf("\\n");
while(idx>-1){
strErrorTemp=strErrorTemp.replace("\\n","\n");
idx=strErrorTemp.indexOf("\\n");
};
return strErrorTemp.replace("%FIELDNAME%",(field.realname)?field.realname:((obj.id)?obj.id:obj.name));
};
function _parseBoolean(value){
return !(!value||value==0||value=="0"||value=="false");
};
function _checkRegExp(regx,value){
switch(regx){
case "JSVAL_RX_EMAIL":
//return((/^([\w]+)(\.[\w]+)*@([\w\-]+)(\.[\w]{2,7})(\.[a-z]{2})?$/i).test(value));
//return((/^.+\@(\[?)[a-zA-Z0-9\-\.]+\.([a-zA-Z]{2,3}|[0-9]{1,3})(\]?)$/i).test(value));
return((/^[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4}$/).test(value));
case "JSVAL_RX_TEL":
//return((/\d+/).test(value));
return((/^ *[0-9]+ *$/).test(value));
//return((/\^[1-9]{1}[0-9]/).test(value));
case "JSVAL_RX_PC":
return((/^[a-z]\d[a-z]?\d[a-z]\d$/i).test(value));
case "JSVAL_RX_ZIP":
return((/^\d{5}$/).test(value));
case "JSVAL_RX_MONEY":
return((/^\d+([\.]\d\d)?$/).test(value));
case "JSVAL_RX_CREDITCARD":
return(!isNaN(value));
case "JSVAL_RX_POSTALZIP":
if(value.length==6||value.length==7)
return((/^[a-zA-Z]\d[a-zA-Z] ?\d[a-zA-Z]\d$/).test(value));
if(value.length==5||value.length==10)
return((/^\d{5}(\-\d{4})?$/).test(value));
break;
default:
return(regx.test(value));
};
};

function send_inv(){
hidePre('');
document.invention.action.value='invention';
if (document.invention.onsubmit())
	document.invention.submit();
}

function send_recommand(){
hidePre('');
document.expert_recommand_agree.action.value='expert_recommand_agree';
if (document.expert_recommand_agree.onsubmit())
	document.expert_recommand_agree.submit();
}

function makeObject1(){
var x;
var browser = navigator.appName;
if(browser == "Microsoft Internet Explorer"){
x = new ActiveXObject("Microsoft.XMLHTTP");
}else{
x = new XMLHttpRequest();
}
return x;
}

function GotoDownloadPage(mcode,invid,filename){
var request = makeObject1();
request.open('POST', mypath+'form_action.asp');
request.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
request.onreadystatechange = function(){
 if(request.readyState == 4){
	location.href = "/download.asp?"+escape(filename);
}
}
request.send('action=downloadfile&mcode=' + mcode + '&invid=' + invid + '&filename=' + filename);
}