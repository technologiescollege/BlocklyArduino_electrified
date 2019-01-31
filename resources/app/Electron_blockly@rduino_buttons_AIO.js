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

window.addEventListener('load', function load(event) {
	document.getElementById('btn_saveConfigGlobale').onclick = function(event) {
		var fileSettings = "./Blockly@rduino.json"
		var Settings = window.location.search
		fs.writeFileSync(fileSettings, JSON.stringify(Settings, 'w'), (err) => {
			if(err){
				console.log("An error ocurred creating the file "+ err.message)
			}                    
			console.log("The file has been succesfully saved")
		})
	}
	document.getElementById('btn_flash_pymata').onclick = function(event) {
		$('#message').modal('show');
		var com = 'COM' + fs.readFileSync('COMport.txt')
		if ((com == "no_com")||(com === "")||(com === "0")){
			document.getElementById('messageDIV').style.color = '#ff0000'
			document.getElementById('messageDIV').textContent  = 'Sélectionner un port !'
			return
			} else {
				document.getElementById('messageDIV').style.color = '#000000'
				document.getElementById('messageDIV').textContent = 'Carte ' + profile.defaultBoard['description'] + ' sur port ' + com
				var upload_arg = profile.defaultBoard['upload_arg']
				var carte = document.getElementById('board_select').value
				if (carte ==  'arduino_leonardo' || carte ==  'arduino_mega' || carte ==  'arduino_micro' || carte ==  'arduino_yun')
						var file_path = '..\\..\\tools\\FirmataPlus-32u4'
					else
						var file_path = '..\\..\\tools\\FirmataPlus'
		}
		var cmd = 'arduino-cli.exe upload -p ' + com + ' --fqbn ' + upload_arg + ' ' + file_path
		document.getElementById('messageDIV').textContent += '\n\nTéléversement : en cours...\n'
		exec(cmd , {cwd: './B@electron/arduino'} , (error, stdout, stderr) => {
			if (error) {
				document.getElementById('messageDIV').style.color = '#ff0000'
				document.getElementById('messageDIV').textContent = stderr
				return
			}
			document.getElementById('messageDIV').style.color = '#00ff00'
			document.getElementById('messageDIV').textContent += stdout
			document.getElementById('messageDIV').textContent += '\nTéléversement du microprogramme : OK'
		})
	}
	document.getElementById('btn_term').onclick = function(event) {
		var com = 'COM' + fs.readFileSync('COMport.txt')
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
		var com = 'COM' + fs.readFileSync('COMport.txt')
		console.log("Asynchronous read2: " + com.toString())
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
		document.getElementById('local_debug').textContent = 'Carte ' + profile.defaultBoard['description'] + ' sur port ' + com
		document.getElementById('local_debug').textContent += 'Téléversement : en cours...\n'
		console.log(cmd)
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