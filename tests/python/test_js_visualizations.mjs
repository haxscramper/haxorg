import fs from "fs";
import { JSDOM } from "jsdom";
import * as d3 from "d3";

// Process command-line arguments
const args = process.argv.slice(2);
const modulePath = args.find(arg => arg.startsWith("--module-path=")).split("=")[1];
const inputFile = args.find(arg => arg.startsWith("--input-file=")).split("=")[1];
const outputFile = args.find(arg => arg.startsWith("--output-file=")).split("=")[1];

// Setup jsdom environment
const { window } = new JSDOM();
global.window = window;
global.document = window.document;
global.d3 = d3;

// Dynamically import the module under test
import(modulePath).then(module => {
    const data = JSON.parse(fs.readFileSync(inputFile, "utf-8"));
    
    // Assuming the module exposes an onLoadAll function
    module.evalTest(data);

    // Save the SVG to a file
    fs.writeFileSync(outputFile, window.document.body.innerHTML);
});
