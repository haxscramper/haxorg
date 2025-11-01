package com.example.elk;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import org.eclipse.elk.core.RecursiveGraphLayoutEngine;
import org.eclipse.elk.core.util.BasicProgressMonitor;
import org.eclipse.elk.graph.ElkNode;
import org.eclipse.elk.graph.json.ElkGraphJson;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class ElkLayoutCli {
    
    public static void main(String[] args) {
        String inputFile = null;
        String outputFile = null;
        
        // Parse command line arguments
        for (String arg : args) {
            if (arg.startsWith("--input=")) {
                inputFile = arg.substring("--input=".length());
            } else if (arg.startsWith("--output=")) {
                outputFile = arg.substring("--output=".length());
            } else if (arg.equals("--help") || arg.equals("-h")) {
                printUsage();
                System.exit(0);
            }
        }
        
        // Validate arguments
        if (inputFile == null || outputFile == null) {
            System.err.println("Error: Both --input and --output parameters are required.");
            printUsage();
            System.exit(1);
        }
        
        try {
            performLayout(inputFile, outputFile);
            System.out.println("Layout completed successfully.");
            System.out.println("Input: " + inputFile);
            System.out.println("Output: " + outputFile);
        } catch (Exception e) {
            System.err.println("Error performing layout: " + e.getMessage());
            e.printStackTrace();
            System.exit(1);
        }
    }
    
    private static void performLayout(String inputFilePath, String outputFilePath) throws IOException {
        // Read input JSON file
        Path inputPath = Paths.get(inputFilePath);
        if (!Files.exists(inputPath)) {
            throw new IOException("Input file does not exist: " + inputFilePath);
        }
        
        String inputJson = Files.readString(inputPath);
        
        // Parse and process the graph
        JsonObject jsonGraph;
        try {
            jsonGraph = JsonParser.parseString(inputJson).getAsJsonObject();
        } catch (Exception e) {
            throw new IOException("Invalid JSON in input file: " + e.getMessage(), e);
        }
        
        // Convert to ELK graph and perform layout
        ElkNode elkGraph = ElkGraphJson.forGraph(jsonGraph).toElk();
        RecursiveGraphLayoutEngine layoutEngine = new RecursiveGraphLayoutEngine();
        BasicProgressMonitor monitor = new BasicProgressMonitor();
        
        layoutEngine.layout(elkGraph, monitor);
        
        // Convert back to JSON
        String outputJson = ElkGraphJson.forGraph(elkGraph)
            .prettyPrint(true)
            .toJson();
        
        // Write output JSON file
        Path outputPath = Paths.get(outputFilePath);
        
        // Create parent directories if they don't exist
        Path parentDir = outputPath.getParent();
        if (parentDir != null && !Files.exists(parentDir)) {
            Files.createDirectories(parentDir);
        }
        
        Files.writeString(outputPath, outputJson, 
            StandardOpenOption.CREATE, 
            StandardOpenOption.WRITE, 
            StandardOpenOption.TRUNCATE_EXISTING);
    }
    
    private static void printUsage() {
        System.out.println("ELK Graph Layout CLI");
        System.out.println();
        System.out.println("Usage: java -jar elk-layout-cli.jar --input=<input-file> --output=<output-file>");
        System.out.println();
        System.out.println("Options:");
        System.out.println("  --input=<file>   Path to input JSON file containing ELK graph");
        System.out.println("  --output=<file>  Path to output JSON file for layouted graph");
        System.out.println("  --help, -h       Show this help message");
        System.out.println();
        System.out.println("Example:");
        System.out.println("  java -jar elk-layout-cli.jar --input=graph.json --output=layout.json");
    }
}
