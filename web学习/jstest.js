'use strict';
//实现：密码验证，图像预览，异步执行

var checkRegisterForm = function () {
    var usernameReg = /^[0-9a-z]{3,10}$/i;
	var passwordReg = /^\w{6,20}$/;
	var input_un = document.getElementById('username');
	var input_pw = document.getElementById('password');
	var input_pw2 = document.getElementById('password-2');
	if(!usernameReg.test(input_un.value)){
	 alert('账号必须为3-10位的英文字母或数字');
	 return false;
	}
	if(!passwordReg.test(input_pw.value)){
	 alert('密码必须是6-20位字母或数字');
	 return false;
	}
	if(input_pw.value !== input_pw2.value){
	 alert('两次输入的口令必须一致');
	 return false;
	}
	return true;
}

// 实现图像预览
var fileInput = document.getElementById("file-input");
var info = document.getElementById("test-file-info");
var imageDis = document.getElementById("test-image-file");

fileInput.addEventListener('change',function () {
	imageDis.style.backgroundImage = '';
	if(!fileInput.value) {
		info.innerHTML = '没有选择文件';
		return;
	}
	
	var file=fileInput.files[0];
	
	info.innerHTML = '文件' + file.name + '<br/>大小' + file.size + '<br/>';
	if(file.type !== 'image/jpeg' && file.type !== 'image/png' && file.type !== 'image/gif') {
		alert('不是有效的图片文件！');
		return;
	}
	
	var reader = new FileReader();
	reader.onload = function(e) {
		var data = e.target.result;
		imageDis.style.backgroundSize='contain';
		imageDis.style.backgroundImage='url('+data+')';
	};
	
	reader.readAsDataURL(file);
});

// Promise对象
var tricktime = 0;
function trickGetPrice() {
	var p = new Promise(getPrice);
	var div = document.getElementById("test-promise");
	var lastp;
	if (tricktime<=0){
		lastp = document.createElement('p');
		lastp.innerHTML = "骗你的，什么都不会发生啦...";
		div.appendChild(lastp);
		tricktime++;
	}else{
		lastp = div.getElementsByTagName('p');
		lastp = lastp[lastp.length-1];
		lastp.innerHTML = "多点"+ (++tricktime) + "次这么好玩吗？";
	}
	
	p.then(
		function (results){
			lastp.innerHTML = "好啦，其实是真的："+results;
		}
	).catch(
		function (reason) {
			lastp.innerHTML = "不会吧，真失败了= =";
		}
	)
}

function getPrice(resolve,reject){
	console.log("正在执行getPrice()...");
	setTimeout(resolve,2000,"上证：1000.0");
}