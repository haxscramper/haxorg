import {execSync} from "child_process";
import * as fs from "fs";

export function dump_html() {
  const html: string = document.documentElement.outerHTML;
  const fileName     = "/tmp/d3_js_output.html"
  fs.writeFileSync(fileName, html, "utf-8");
  try {
    execSync(`tidy -q -m -i -w 120 --show-warnings no ${fileName}`);
  } catch (e) {
  }
}
