import {app, BrowserWindow} from 'electron';
import * as path from 'path';

async function createWindow() {
  const mainWindow = new BrowserWindow({
    width: 1600,
    height: 1200,
    webPreferences: {
      nodeIntegration: true,
      contextIsolation: false,
      webSecurity: false,                // need this to load local files
      allowRunningInsecureContent: true  // In development
    }
  });

  await mainWindow.loadFile('renderer/index.html');
  mainWindow.webContents.openDevTools();
}

app.whenReady().then(createWindow);

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
  }
});
