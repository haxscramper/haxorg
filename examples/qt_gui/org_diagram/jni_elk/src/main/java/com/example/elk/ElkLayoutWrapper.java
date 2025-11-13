package com.example.elk;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import org.eclipse.elk.core.RecursiveGraphLayoutEngine;
import org.eclipse.elk.core.util.BasicProgressMonitor;
import org.eclipse.elk.graph.ElkNode;
import org.eclipse.elk.graph.json.ElkGraphJson;

public class ElkLayoutWrapper {
    
    public static String performLayout(String inputJson) {
        JsonObject jsonGraph = JsonParser.parseString(inputJson).getAsJsonObject();
        ElkNode elkGraph = ElkGraphJson.forGraph(jsonGraph).toElk();
        RecursiveGraphLayoutEngine layoutEngine = new RecursiveGraphLayoutEngine();
        BasicProgressMonitor monitor = new BasicProgressMonitor();
        layoutEngine.layout(elkGraph, monitor);
        return ElkGraphJson.forGraph(elkGraph).prettyPrint(true).toJson();
    }
}
