import {contextBridge, ipcRenderer} from "electron";
import * as fs from "fs";
import * as path from "path";

console.log("preload.ts execution");

// Expose safe APIs to the renderer process
contextBridge.exposeInMainWorld("electronAPI", {
  getWasmPaths : async () => {
    console.log("Requested wasm path");
    return await ipcRenderer.invoke("wasm:getFilePaths");
  },
  checkWasmStatus : async () => {
    console.log("Running ICP request to check wasm status");
    return await ipcRenderer.invoke("wasm:checkStatus");
  },
  readFile : async(filePath: string) :
      Promise<{success : boolean, data?: string, error?: string}> => {
        return await ipcRenderer.invoke("file:read", filePath);
      },
});
