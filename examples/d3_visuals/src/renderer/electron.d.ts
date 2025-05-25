export interface ElectronAPI {
  getWasmPaths: ()    => Promise<{jsPath : string; wasmPath : string;}>;
  checkWasmStatus: () => Promise<boolean>;
  readFile: (filePath: string) => Promise<
      {success : boolean, data?: string, error?: string}>;
  writeDebugHtml: (filePath: string, content: string) => Promise<boolean>;

  resolveSymlink: (path: string)        => Promise<string>;
  getDirectoryEntryList: (path: string) => Promise<string[]>;
  isRegularFile: (path: string)         => Promise<boolean>;
  isSymlink: (path: string)             => Promise<boolean>;
  isDirectory: (path: string)           => Promise<boolean>;
}

declare global {
  interface Window {
    electronAPI: ElectronAPI;
  }
}
