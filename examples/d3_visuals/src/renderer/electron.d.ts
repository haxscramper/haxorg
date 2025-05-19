export interface ElectronAPI {
  getWasmPaths: ()    => Promise<{jsPath : string; wasmPath : string;}>;
  checkWasmStatus: () => Promise<boolean>;
  readFile: (filePath: string) => Promise<
      {success : boolean, data?: string, error?: string}>;
}

declare global {
  interface Window {
    electronAPI: ElectronAPI;
  }
}
