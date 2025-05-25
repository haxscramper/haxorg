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
  writeDebugHtml : async (filePath: string, content: string) => {
    return await ipcRenderer.invoke("file:dump_debug_html", filePath, content);
  },
  readFile : async(filePath: string) :
      Promise<{success : boolean, data?: string, error?: string}> => {
        return await ipcRenderer.invoke("file:read", filePath);
      },
  isDirectory : async(path: string) : Promise<boolean> => {
    return await ipcRenderer.invoke("file:isDirectory", path);
  },
  isSymlink : async(path: string) : Promise<boolean> => {
    return await ipcRenderer.invoke("file:isSymlink", path);
  },
  isRegularFile : async(path: string) : Promise<boolean> => {
    return await ipcRenderer.invoke("file:isRegularFile", path);
  },
  getDirectoryEntryList : async(path: string) : Promise<string[]> => {
    return await ipcRenderer.invoke("file:getEntryList", path);
  },
  resolveSymlink : async(path: string) : Promise<string> => {
    return await ipcRenderer.invoke("file:resolveSymlink", path);
  },
});
