const { app, BrowserWindow } = require('electron');
const path = require('path');

let mainWindow;

function createWindow() {
  mainWindow = new BrowserWindow({
    width: 1400,
    height: 900,
    minWidth: 1024,
    minHeight: 768,
    title: 'YUGA - AI GameCraft',
    icon: path.join(__dirname, 'public', 'logo.png'),
    webPreferences: {
      nodeIntegration: false,
      contextIsolation: true,
      webSecurity: false, // Allow dev server
      allowRunningInsecureContent: true
    },
    backgroundColor: '#0f1419',
    show: false
  });

  // Load the Vite dev server
  mainWindow.loadURL('http://localhost:8080').catch(err => {
    console.error('Failed to load URL:', err);
  });

  // Show window when ready
  mainWindow.once('ready-to-show', () => {
    mainWindow.show();
  });

  // Handle loading errors
  mainWindow.webContents.on('did-fail-load', (event, errorCode, errorDescription) => {
    console.error('Failed to load:', errorCode, errorDescription);
    setTimeout(() => {
      mainWindow.loadURL('http://localhost:8080');
    }, 1000);
  });

  // Open DevTools always to see errors
  mainWindow.webContents.openDevTools();

  // Log when page loads
  mainWindow.webContents.on('did-finish-load', () => {
    console.log('Page loaded successfully');
  });

  mainWindow.on('closed', () => {
    mainWindow = null;
  });
}

app.whenReady().then(createWindow);

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
  }
});

app.on('activate', () => {
  if (BrowserWindow.getAllWindows().length === 0) {
    createWindow();
  }
});
