"use strict";


function paint() {
	var canvas = document.getElementById('test-canvas');
	var context = canvas.getContext('2d');
	
	context.beginPath();
	context.moveTo(100,100);
	context.arcTo(200,100,400,300,200);
	context.strokeStyle = 'black';
	context.width = 6;
	context.lineCap = 'round';
	context.stroke();
}

window.onload = function (){
	var canvas = document.getElementById('test-canvas');
	canvas.width = screen.availWidth;
	var context = canvas.getContext('2d');
	context.fillStyle = 'white';
	context.fillRect(0,0,canvas.width, canvas.height);
	
}
window.loadStockData = function (r) {
    var
        NUMS = 30,
        data = r.data;
    if (data.length > NUMS) {
        data = data.slice(data.length - NUMS);
    }
    data = data.map(function (x) {
        return {
            date: x[0],
            open: x[1],
            close: x[2],
            high: x[3],
            low: x[4],
            vol: x[5],
            change: x[6]
        };
    });
    window.drawStock(data);
}

window.drawStock = function (data) {
	var canvas = getElementById('test-canvas'), width=canvas.width, height=canvas.height;
    	
	
}

function drawChatBox(context,x0,y0,x1,y1, extend){
	context.beginPath();
	context.moveTo(x0,y0);
	
}
