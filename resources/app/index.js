const sp = require('serialport')
const { exec } = require('child_process')
const fs = require('fs-extra')
const { ipcRenderer } = require("electron")

sp.list(function(err,ports) {
	localStorage.setItem("nb_com",ports.length)
	ports.forEach(function(port) {
		var opt = document.createElement('option')
		opt.value = port.comName
		opt.text = port.comName
		document.getElementById('serialport').appendChild(opt)
	})
}) 
window.addEventListener('load', function load(event) {
	$('#serialport').mouseover(function(event) {
		sp.list(function(err,ports) {
			var nbCom = localStorage.getItem("nb_com"), menu_com = document.getElementById('serialport'), menu_opt = menu_com.getElementsByTagName('option')
			if(ports.length != nbCom){
				while(menu_opt[1]) {
					menu_com.removeChild(menu_opt[1]);
				}
				ports.forEach(function(port){
					var opt = document.createElement('option')
					opt.value = port.comName
					opt.text = port.comName
					document.getElementById('serialport').appendChild(opt)
				})
				localStorage.setItem("nb_com",ports.length)
			}
		})
	})
	document.getElementById('btn_term').onclick = function(event) {
		var com = document.getElementById('serialport').value
		localStorage.setItem("com",com)
		ipcRenderer.send("prompt", "")		
	}
	document.getElementById('btn_factory').onclick = function(event) {
		ipcRenderer.send("factory", "")		
	}
	document.getElementById('btn_flash_local').onclick = function(event) {
		var file = './resources/app/outils/build/sketch.ino.hex'
		var carte = document.getElementById('board_select').value
		var com = document.getElementById('serialport').value
		if (carte=="carte"||com=="com"){
			document.getElementById('local_debug').style.color = '#ffffff'
			document.getElementById('local_debug').textContent = 'Sélectionner un port et une carte !!!'
			return
		}
		if (carte=="arduino_mega"){
			var speed = '115200'
			var cpu = 'atmega2560'
		} else if (carte=="atmegang"){
			var speed = '19200'
			var cpu = 'atmega8'
		} else if (carte=="arduino_yun"||carte=="arduino_leonardo"||carte=="arduino_micro"){
			var speed = '57600'
			var cpu = 'atmega32u4'
		} else if (carte=="pro8"||carte=="pro16"||carte=="nano"){
			var speed = '57600'
			var cpu = 'atmega328p'
		} else {
			var speed = '115200'
			var cpu = 'atmega328p'
		}
		var cmd = 'flash.bat ' + cpu + ' ' + com + ' ' + speed
		document.getElementById('local_debug').style.color = '#ffffff'
		document.getElementById('local_debug').textContent = 'téléversement : en cours...'
		exec(cmd , {cwd: './resources/app/outils'} , (err, stdout, stderr) => {
			if (err) {
				document.getElementById('local_debug').style.color = '#ff0000'
				document.getElementById('local_debug').textContent = err
				fs.unlink(file, function(err){
					if(err) return console.log(err)
				}) 
				return
			}
			document.getElementById('local_debug').style.color = '#00ff00'
			document.getElementById('local_debug').textContent = 'téléversement : OK'
			fs.unlink(file, function(err){
				if(err) return console.log(err)
			}) 
		})
	}
})
