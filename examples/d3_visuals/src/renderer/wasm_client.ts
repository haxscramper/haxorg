// src/renderer/wasm_client.ts

import { haxorg_wasm_module } from "../../../../src/wrappers/js/haxorg_wasm_types";
import { ElectronAPI } from "./electron";

declare global {
  interface Window {
    module: haxorg_wasm_module & {
      onRuntimeInitialized?: () => void;
      calledRun?: boolean;
      locateFile?: (path: string) => string;
    };
    haxorg_wasm: Function;
  }
}

let wasmModule: haxorg_wasm_module|null               = null;
let wasmInitPromise: Promise<haxorg_wasm_module>|null = null;


export async function initWasmModule(): Promise<haxorg_wasm_module> {
  if (wasmModule) {
    return wasmModule;
  }

  if (wasmInitPromise) {
    return wasmInitPromise;
  }

  wasmInitPromise = (async () => {
    try {
      console.log("Started loading WASM module");
      const isReady = await window.electronAPI.checkWasmStatus();
      if (isReady) {
        console.log("Wasm is ready"); 
      } else {
        throw new Error('WASM service is not ready in the main process');
      }

      const { jsPath, wasmPath } = await window.electronAPI.getWasmPaths();

      // Load the JS file
      await new Promise<void>((resolve, reject) => {
        console.log(`Using JS path ${jsPath}`);
        const script = document.createElement('script');
        script.src = `file://${jsPath}`;
        script.onload = () => {
          console.log("Script loaded successfully");
          resolve();
        };
        script.onerror = (err) => {
          console.error("Script load error:", err);
          reject(new Error('Failed to load WASM JS file'));
        };
        document.head.appendChild(script);
      });

      // Check if the factory function exists
      if (typeof window.haxorg_wasm !== 'function') {
        throw new Error('haxorg_wasm factory function not found after script load');
      }

      console.log("Initializing WASM module with factory function");
      
      // Call the factory function with configuration
      const moduleInstance = await window.haxorg_wasm({
        locateFile: (path: string) => {
          if (path.endsWith('.wasm')) {
            return `file://${wasmPath}`;
          }
          return path;
        },
        // Optional: Add any other Module configuration here
        print: (text: string) => console.log(`WASM stdout: ${text}`),
        printErr: (text: string) => console.error(`WASM stderr: ${text}`)
      });

      console.log("Module initialized successfully");
      
      // Store the module globally
      wasmModule = moduleInstance;
      window.module = moduleInstance;
      
      return moduleInstance;
    } catch (error) {
      console.error('Failed to initialize WASM module:', error);
      wasmInitPromise = null;
      throw error;
    }
  })();

  return wasmInitPromise;
}

// Initialize at the earliest opportunity
if (typeof window !== "undefined" && typeof document !== "undefined") {
  if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", () => {
      initWasmModule().catch(
          err => console.error("Failed to initialize WASM:", err));
    });
  } else {
    initWasmModule().catch(
        err => console.error("Failed to initialize WASM:", err));
  }
}
