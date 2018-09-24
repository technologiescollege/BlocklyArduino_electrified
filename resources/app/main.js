const electron = require('electron')
const {ipcMain} = require('electron')
const app = electron.app
const BrowserWindow = electron.BrowserWindow
const path = require('path')
let mainWindow
let termWindow

function createWindow () {
	mainWindow = new BrowserWindow({width:1120,height:700,icon:'./favicon.ico'})
	if (process.platform == 'win32' && process.argv.length >= 2) {
		mainWindow.loadURL(path.join(__dirname, 'index_electron.html?url='+process.argv[1]))
	} else {
		mainWindow.loadURL(path.join(__dirname, 'index_electron.html'))
	}
	mainWindow.setMenu(null);
	mainWindow.webContents.openDevTools();
	mainWindow.on('closed', function () {
		mainWindow = null
	})
}
app.on('ready', createWindow)
app.on('activate', function () {
	if (mainWindow === null) {
		createWindow()
	}
})
app.on('window-all-closed', function () {
	if (process.platform !== 'darwin') {
		app.quit()
	}
})
function createTerm() {
	termWindow = new BrowserWindow({width:640,height:560,'parent':mainWindow,resizable:false,movable:false,frame:false,modal:true}) 
	termWindow.loadURL(path.join(__dirname, "./tools/serialconsole/term.html"))
	termWindow.setMenu(null);
	termWindow.on('closed', function () { 
		termWindow = null 
	})
}
ipcMain.on("prompt", function () {
	createTerm()       
});
function createfactory() {
	termWindow = new BrowserWindow({width:1066,height:700,'parent':mainWindow,resizable:false,movable:false,frame:false,modal:true}) 
	termWindow.loadURL(path.join(__dirname, "./tools/factory/index.html"))
	termWindow.setMenu(null);
	termWindow.on('closed', function () { 
		termWindow = null 
	})
}
ipcMain.on("factory", function () {
	createfactory()       
});