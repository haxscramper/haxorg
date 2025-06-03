import {ElectronAPI} from "./electron";
declare global {
  interface Window {
    electronAPI: ElectronAPI;
  }
}

export function dump_html() {
  window.electronAPI.writeDebugHtml(
      "/tmp/d3_js_output.html",
      document.documentElement.outerHTML //
  );
}
