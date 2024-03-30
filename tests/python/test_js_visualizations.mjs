import fs from "fs";
import puppeteer from "puppeteer";

const args = process.argv.slice(2);
const modulePath =
    args.find(arg => arg.startsWith("--module-path=")).split("=")[1];
const outputFile =
    args.find(arg => arg.startsWith("--output-file=")).split("=")[1];

(async () => {
  const browser = await puppeteer.launch();
  const page = await browser.newPage();

  page.on("console",
          msg => { console.log(`PAGE LOG [${msg.type()}]: ${msg.text()}`); });

  await page.setRequestInterception(true);
  
//   page.on("request", request => {
//     if (request.url().endsWith("/favicon.ico")) {
//       request.abort();
//     } else {
//       request.continue();
//     }
//   });

  page.on("requestfailed", request => {
    console.error(`[Request failed]: ${request.url()} - Reason: ${
        request.failure().errorText}`);
  });

  await page.goto(`http://localhost:9876/${modulePath}`,
                  {waitUntil : "networkidle0"});

  await page.evaluate(() => { return window.evalTest(); });

  const svgContent = await page.$eval("svg", e => e.outerHTML);
  fs.writeFileSync(outputFile, svgContent);

  await browser.close();
})();
