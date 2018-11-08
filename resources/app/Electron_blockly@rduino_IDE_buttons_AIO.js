const { exec } = require('child_process')
const fs = require('fs-extra')
const { ipcRenderer } = require("electron")

/* fake IDE code Arduino
** load: serial port list
** btn_term: open modal with serial console
** btn_factory: open modal with blocks factory
** btn_verify_local: verify and compile in hex file
** btn_flash_local: upload hex file in Arduino board
*/

document.getElementById('serialport_ide').addEventListener('mouseover', function(event) {
	var sp_ide = require('serialport')
	sp_ide.list(function(err, ports) {
		var menu_com = document.getElementById('serialport_ide')
		var menu_opt = menu_com.getElementsByTagName('option')
		var count = 0
		var scanDone = false
		if(ports.length <1) console.log('No Arduino')
		//compare old list of COM port and new one
		if(ports != localStorage.getItem('oldPorts')){
			while(menu_opt[1]) {
				menu_com.removeChild(menu_opt[1])
			}
			ports.forEach(function(port){
				count += 1
				var portManufact = port['manufacturer']
				//log all boards
				console.log(port['manufacturer'] + ' port ' + port.comName +  ' ID ' + port.vendorId + '\n')
				//only if board has Vendor Id knowed : Arduino, CH340, etc
				if (typeof portManufact !== 'undefined' && (port.vendorId == '2341' || port.vendorId == '2A03' || port.vendorId == '1A86' || port.vendorId == '0403' || port.vendorId == '10C4')) {
					var opt = document.createElement('option')
					opt.value = opt.text = port.comName
					// document.getElementById('serialport_sup').appendChild(opt)
					document.getElementById('serialport_ide').appendChild(opt)
					scanDone = true
				}
				if (count === ports.length && scanDone === false) {
					console.log('No Arduino')
				}
			})
			localStorage.setItem('oldPorts', ports)
		}
	})
}, false)

document.getElementById('serialport_sup').addEventListener('mouseover', function(event) {
	var sp_sup = require('serialport')
	sp_sup.list(function(err, ports) {
		var menu_com_sup = document.getElementById('serialport_sup')
		var menu_opt = menu_com_sup.getElementsByTagName('option')
		var count = 0
		var scanDone = false
		if(ports.length <1) console.log('No Arduino')
		//compare old list of COM port and new one
		if(ports != localStorage.getItem('oldPorts')){
			while(menu_opt[1]) {
				menu_com_sup.removeChild(menu_opt[1])
			}
			ports.forEach(function(port){
				count += 1
				var portManufact = port['manufacturer']
				//log all boards
				console.log(port['manufacturer'] + ' port ' + port.comName +  ' ID ' + port.vendorId + '\n')
				//only if board has Vendor Id knowed : Arduino, CH340, etc
				if (typeof portManufact !== 'undefined' && (port.vendorId == '2341' || port.vendorId == '2A03' || port.vendorId == '1A86' || port.vendorId == '0403' || port.vendorId == '10C4')) {
					var opt = document.createElement('option')
					opt.value = opt.text = port.comName
					document.getElementById('serialport_sup').appendChild(opt)
					// document.getElementById('serialport_ide').appendChild(opt)
					scanDone = true
				}
				if (count === ports.length && scanDone === false) {
					console.log('No Arduino')
				}
			})
			localStorage.setItem('oldPorts', ports)
		}
	})
}, false)

window.addEventListener('load', function load(event) {
	var $selects=$('#serialport_sup, #serialport_ide').change(function(){
		$selects.not(this).val( $(this).val() );
	})
	document.getElementById('btn_flash_pymata').onclick = function(event) {
		var carte = document.getElementById('board_select').value
		if (carte ==  'arduino_leonardo' || carte ==  'arduino_mega' || carte ==  'arduino_micro' || carte ==  'arduino_yun')
				var file_path = '..\\..\\tools\\FirmataPlus-32u4'
			else
				var file_path = '..\\..\\tools\\FirmataPlus'
		var com = document.getElementById('serialport_sup').value
		if (com=="no_com"){
			document.getElementById('sup_debug').style.color = '#ffffff'
			document.getElementById('sup_debug').textContent = 'Sélectionner un port !'
			return
			} else {
				document.getElementById('sup_debug').style.color = '#ffffff'
				document.getElementById('sup_debug').textContent = 'Carte ' + profile.defaultBoard['description'] + ' sur port ' + com
				var upload_arg = profile.defaultBoard['upload_arg']
		}
		var cmd = 'arduino-cli.exe upload -p ' + com + ' --fqbn ' + upload_arg + ' ' + file_path
		document.getElementById('sup_debug').textContent = 'Téléversement : en cours...\n'
		exec(cmd , {cwd: './arduino'} , (error, stdout, stderr) => {
			if (error) {
				document.getElementById('sup_debug').style.color = '#ff0000'
				document.getElementById('sup_debug').textContent = stderr
				return
			}
			document.getElementById('sup_debug').style.color = '#ffffff'
			document.getElementById('sup_debug').textContent = stdout
			document.getElementById('sup_debug').textContent = '\nTéléversement du microprogramme : OK'
		})
	}
	document.getElementById('btn_term').onclick = function(event) {
		var com = document.getElementById('serialport_ide').value
		if (com != "no_com") {
			localStorage.setItem("com",com)
			ipcRenderer.send("prompt", "")
			document.getElementById('local_debug').style.color = '#ffffff'
			document.getElementById('local_debug').textContent = ''
		} else {
			document.getElementById('local_debug').style.color = '#ffffff'
			document.getElementById('local_debug').textContent = 'Sélectionner un port COM !!!'
			return
		}
	}
	document.getElementById('btn_factory').onclick = function(event) {
		ipcRenderer.send("factory", "")		
	}
	document.getElementById('btn_verify_local').onclick = function(event) {
		try {
			fs.accessSync('.\\B@electron\\arduino\\tmp', fs.constants.W_OK)
			} catch (err) {
				fs.mkdirSync('.\\B@electron\\arduino\\tmp', { recursive: false }, (err) => {
					if (err) throw err
					})
		}
		var file_path = '.\\tmp'
		var file = '.\\B@electron\\arduino\\tmp\\tmp.ino'
		var data = $('#pre_arduino').text()
		var carte = document.getElementById('board_select').value
		if (carte != "none") {
			document.getElementById('local_debug').style.color = '#ffffff'
			document.getElementById('local_debug').textContent = 'Carte ' + profile.defaultBoard['description']
			var upload_arg = profile.defaultBoard['upload_arg']
			} else {
				document.getElementById('local_debug').style.color = '#ff0000'
				document.getElementById('local_debug').textContent = 'Sélectionner une carte !'
				return
		}
		if ($('#detailedCompilation').prop('checked'))
				var cmd = 'arduino-cli.exe --debug compile --fqbn ' + upload_arg + ' ' + file_path
			else
				var cmd = 'arduino-cli.exe compile --fqbn ' + upload_arg + ' ' + file_path
		fs.writeFile(file, data, (err) => {
			if (err) return console.log(err)
		});		
		document.getElementById('local_debug').textContent += '\nVérification : en cours...\n'
		exec(cmd , {cwd: './B@electron/arduino'} , (error, stdout, stderr) => {
			if (error) {
				document.getElementById('local_debug').style.color = '#ff0000'
				document.getElementById('local_debug').textContent += stderr
				return
			}
			document.getElementById('local_debug').style.color = '#00ff00'
			document.getElementById('local_debug').textContent += stdout
			document.getElementById('local_debug').textContent += '\nVérification : OK'
		})
	}
	document.getElementById('btn_flash_local').onclick = function(event) {
		var file_path = '.\\tmp'
		var carte = document.getElementById('board_select').value
		var com = document.getElementById('serialport_ide').value
		if (carte=="none"||com=="no_com"){
			document.getElementById('local_debug').style.color = '#ff0000'
			document.getElementById('local_debug').textContent = 'Sélectionner un port !'
			return
			} else {
				document.getElementById('local_debug').style.color = '#ffffff'
				document.getElementById('local_debug').textContent = 'Carte ' + profile.defaultBoard['description'] + ' sur port ' + com
				var upload_arg = profile.defaultBoard['upload_arg']
		}
		if ($('#detailedCompilation').prop('checked'))
				var cmd = 'arduino-cli.exe --debug upload -p ' + com + ' --fqbn ' + upload_arg + ' ' + file_path
			else
				var cmd = 'arduino-cli.exe upload -p ' + com + ' --fqbn ' + upload_arg + ' ' + file_path
		document.getElementById('local_debug').textContent = 'Téléversement : en cours...\n'
		exec(cmd , {cwd: './B@electron/arduino'} , (error, stdout, stderr) => {
			if (error) {
				document.getElementById('local_debug').style.color = '#ff0000'
				document.getElementById('local_debug').textContent += stderr
				return
			}
			document.getElementById('local_debug').style.color = '#00ff00'
			document.getElementById('local_debug').textContent += stdout
			document.getElementById('local_debug').textContent += '\nTéléversement : OK'
			const path = require('path')
			fs.readdir('.\\B@electron\\arduino\\tmp', (err, files) => {
			  if (err) throw err;
			  for (const file of files) {
				fs.unlink(path.join('.\\B@electron\\arduino\\tmp', file), err => {
				  if (err) throw err
				})
			  }
			})
		})
	}
})