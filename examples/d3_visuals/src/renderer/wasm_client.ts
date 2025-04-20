// src/renderer/wasm_client.ts

interface HaxorgWasmModule {
  globalAdd: (a: number, b: number) => number;
  [key: string]: any;
}

interface HaxorgWasmFactory {
  (options?: {locateFile?: (path: string, prefix: string) => string;}):
      Promise<HaxorgWasmModule>;
}

declare global {
  interface Window {
    Module: HaxorgWasmModule & {
      onRuntimeInitialized?: () => void;
      calledRun?: boolean;
      locateFile?: (path: string) => string;
    };
  }
}

let wasmModule: HaxorgWasmModule|null               = null;
let wasmInitPromise: Promise<HaxorgWasmModule>|null = null;

export async function initWasmModule(): Promise<HaxorgWasmModule> {
  if (wasmModule) {
    return wasmModule;
  }

  if (wasmInitPromise) {
    return wasmInitPromise;
  }

  wasmInitPromise = (async () => {
    try {
      const isReady = await window.electronAPI.checkWasmStatus();
      if (!isReady) {
        throw new Error('WASM service is not ready in the main process');
      }

      const { jsPath, wasmPath } = await window.electronAPI.getWasmPaths();

      // Create a Module configuration object before loading the script
      window.Module = {
        locateFile: (path: string) => {
          if (path.endsWith('.wasm')) {
            return `file://${wasmPath}`;
          }
          return path;
        }
      };

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

      // Wait for the runtime to be initialized
      if (!window.Module) {
        throw new Error('Module not defined after script load');
      }

      // Wait for runtime initialization
      await new Promise<void>((resolve) => {
        if (window.Module.calledRun) {
          // Already initialized
          console.log("Module already initialized");
          resolve();
        } else {
          // Set callback for initialization
          const originalOnRuntimeInitialized = window.Module.onRuntimeInitialized || (() => {});
          
          window.Module.onRuntimeInitialized = () => {
            console.log("Runtime initialized");
            originalOnRuntimeInitialized();
            resolve();
          };
        }
      });

      console.log("Module ready for use");
      
      // Store the module globally
      wasmModule = window.Module;
      window.haxorgWasm = window.Module;
      
      return wasmModule;
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
