import {app, BrowserWindow, ipcMain} from "electron";
import * as fs from "fs";
import * as path from "path";

let mainWindow: BrowserWindow|null = null;

const wasmJsPath
    = "/home/haxscramper/workspace/haxorg/build/haxorg_debug_emscripten/haxorg_wasm.js";
const wasmBinaryPath
    = "/home/haxscramper/workspace/haxorg/build/haxorg_debug_emscripten/haxorg_wasm.wasm";

async function createWindow() {
  mainWindow = new BrowserWindow({
    width : 1600,
    height : 1200,
    webPreferences : {
      nodeIntegration : true,
      contextIsolation : true,
      webSecurity : false,                // need this to load local files
      allowRunningInsecureContent : true, // In development
      preload : path.join(__dirname, "..", "preload.js")
    }
  });

  mainWindow.webContents.openDevTools();

  await mainWindow.loadFile("../renderer/index.html");

  process.on("SIGUSR1", () => {
    console.log("Got user signal for reload");
    if (mainWindow) {
      mainWindow.reload();
    }
  });
}

function setupIpcHandlers() {
  console.log("setup IPC handlers");
  ipcMain.handle("wasm:getFilePaths", () => {
    console.log("Requested WASM path");
    return {
      jsPath : wasmJsPath,
      wasmPath : wasmBinaryPath,
    };
  });

  ipcMain.handle("wasm:checkStatus", () => {
    console.log("Check WASM status");
    console.log(`${wasmJsPath} exists sync ${fs.existsSync(wasmJsPath)}`)
    console.log(
        `${wasmBinaryPath} exists sync ${fs.existsSync(wasmBinaryPath)}`)
    return fs.existsSync(wasmJsPath) && fs.existsSync(wasmBinaryPath);
  });
}

app.whenReady().then(() => {
  setupIpcHandlers();
  createWindow();
});

app.on("window-all-closed", () => {
  if (process.platform !== "darwin") {
    app.quit();
  }
});

app.on("activate", () => {
  if (BrowserWindow.getAllWindows().length === 0) {
    createWindow();
  }
});
