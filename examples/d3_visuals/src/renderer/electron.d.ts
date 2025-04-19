interface ElectronAPI {
  getWasmPaths: ()    => Promise<{jsPath : string; wasmPath : string;}>;
  checkWasmStatus: () => Promise<boolean>;
}

declare global {
  interface Window {
    electronAPI: ElectronAPI;
  }
}
