const electron = require('electron')
const {ipcMain} = require('electron')
const app = electron.app
const BrowserWindow = electron.BrowserWindow
const path = require('path')
const userDataPath = app.getPath ('userData')

app.setPath ('userData', app.getAppPath());

let mainWindow
let termWindow
let factoryWindow

app.on('window-all-closed', () => {
	mainWindow.webContents.session.clearStorageData()
	mainWindow.webContents.clearHistory()
    app.quit()
})

function createWindow () {
	mainWindow = new BrowserWindow({
		width:1280,
		height:800,
		icon:'./favicon.ico'
		})
	if (process.platform == 'win32' && process.argv.length >= 2) {
		mainWindow.loadURL(path.join(__dirname, '../../www/index_electron.html?'+process.argv[1]))
	} else {
		mainWindow.loadURL(path.join(__dirname, '../../www/index_electron.html'))
	}
	mainWindow.setMenu(null);
	//mainWindow.webContents.openDevTools();
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
	
function createTerm() {
	termWindow = new BrowserWindow({
		width: 660,
		height: 660,
		'parent':mainWindow,
		resizable:false,
		movable:true,
		frame:true,
		modal:false
		}) 
	//termWindow.webContents.openDevTools();
	termWindow.loadURL(path.join(__dirname, "../../www/tools/serialconsole/term.html"))
	termWindow.setMenu(null);
	termWindow.on('closed', function () { 
		termWindow = null 
	})
}
ipcMain.on("prompt", function () {
	createTerm()       
});

function createfactory() {
	factoryWindow = new BrowserWindow({
		width:1200,
		height:800,
		'parent':mainWindow,
		resizable:true,
		movable:true,
		frame:true,
		modal:true
		}) 
	factoryWindow.loadURL(path.join(__dirname, "../../www/tools/factory/block_factory.html"))
	factoryWindow.setMenu(null);
	factoryWindow.on('closed', function () { 
		factoryWindow = null 
	})
}
ipcMain.on("factory", function () {
	createfactory()       
});