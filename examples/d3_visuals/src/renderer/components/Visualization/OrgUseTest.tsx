import React from "react";
import { useState, useEffect, useRef } from 'react';
import * as d3 from 'd3';
import { initWasmModule } from "../../wasm_client";
import { ElectronAPI } from "../../electron";

type FileType = 'file' | 'directory' | 'symlink';

class FileEntry {
  name: string;
  path: string;
  type: 'file' = 'file';
  content?: string;

  constructor(name: string, path: string, content?: string) {
    this.name = name;
    this.path = path;
    this.content = content;
  }
}

class DirectoryEntry {
  name: string;
  path: string;
  type: 'directory' = 'directory';
  children: DirectoryContent[];

  constructor(name: string, path: string, children: DirectoryContent[] = []) {
    this.name = name;
    this.path = path;
    this.children = children;
  }
}

class SymlinkEntry {
  name: string;
  path: string;
  type: 'symlink' = 'symlink';
  target: string;

  constructor(name: string, path: string, target: string) {
    this.name = name;
    this.path = path;
    this.target = target;
  }
}

type DirectoryContent = FileEntry | DirectoryEntry | SymlinkEntry;

class DirectoryStructure {
  root: DirectoryEntry;

  constructor(root: DirectoryEntry) {
    this.root = root;
  }
}

async function buildDirectoryStructure(rootPath: string): Promise<DirectoryStructure> {
  const root = await buildDirectoryEntry(rootPath, rootPath.split('/').pop() || 'root');
  return new DirectoryStructure(root);
}

async function buildDirectoryEntry(path: string, name: string): Promise<DirectoryEntry> {
  const entries = await window.electronAPI.getDirectoryEntryList(path);
  const children: DirectoryContent[] = [];

  for (const entryName of entries) {
    const entryPath = `${entryName}`;

    if (await window.electronAPI.isSymlink(entryPath)) {
      const target = await window.electronAPI.resolveSymlink(entryPath);
      children.push(new SymlinkEntry(entryName, entryPath, target));
    } else if (await window.electronAPI.isDirectory(entryPath)) {
      children.push(await buildDirectoryEntry(entryPath, entryName));
    } else if (await window.electronAPI.isRegularFile(entryPath) && entryName.endsWith('.org')) {
      const fileResult = await window.electronAPI.readFile(entryPath);
      children.push(new FileEntry(entryName, entryPath, fileResult.success ? fileResult.data : undefined));
    }
  }

  return new DirectoryEntry(name, path, children);
}

async function test_directory_read() {
  console.log("Test directory read");
  await initWasmModule();
  const test_directory = "/home/haxscramper/tmp/org_test_dir";
  var directory_opts = new window.module.OrgDirectoryParseParameters();
  const directory_structure: DirectoryStructure = await buildDirectoryStructure(test_directory);
  console.log(directory_structure); 

  function read_file_content(path: string): string {
    const entry = findEntryByPath(directory_structure.root, path, test_directory);
    if (entry instanceof FileEntry && entry.content !== undefined) {
      console.log(`Read file content ${path}`);
      return entry.content;
    } else {
      return "";
    }
  }

  function is_directory_impl(path: string): boolean {
    const entry = findEntryByPath(directory_structure.root, path, test_directory);
    const result =  entry instanceof DirectoryEntry;
    // console.log(`Is directory impl ${path} -> ${result}`);
    return result;
  }

  function is_regular_file(path: string): boolean {
    const entry = findEntryByPath(directory_structure.root, path, test_directory);
    const result = entry instanceof FileEntry;
    // console.log(`Is regular file ${path} -> ${result}`);
    return result; 
  }

  function is_symlink(path: string): boolean {
    const entry = findEntryByPath(directory_structure.root, path, test_directory);
    const result = entry instanceof SymlinkEntry;
    // console.log(`Is symlink ${path} -> ${result}`);
    return result; 
  }

  function get_entry_list(input: string): string[] {
    // console.log(`${input}`);
    const entry = findEntryByPath(directory_structure.root, input, test_directory);
    if (entry instanceof DirectoryEntry) {
      return entry.children.map(child => child.name);
    } else {
      return [];
    }
  }

  function resolve_symllink(input: string): string {
    console.log(`${input}`);
    const entry = findEntryByPath(directory_structure.root, input, test_directory);
    if (entry instanceof SymlinkEntry) {
      return entry.target;
    } else {
      return "";
    }
  }

  function findEntryByPath(root: DirectoryEntry, targetPath: string, basePath: string): DirectoryContent | null {
    // console.log(`findEntryByPath called with targetPath: ${targetPath}, basePath: ${basePath}`);
    
    if (targetPath === basePath) {
      // console.log(`Target path matches base path, returning root`);
      return root;
    }
    
    if (!targetPath.startsWith(basePath + '/')) {
      // console.warn(`Target path does not start with basePath + '/', returning null`);
      return null;
    }
    
    const relativePath = targetPath.substring(basePath.length + 1);
    // console.log(`Relative path: ${relativePath}`);
    
    const pathParts = relativePath.split('/');
    // console.log(`Path parts:`, pathParts);
    
    let current: DirectoryContent = root;
    
    for (let i = 0; i < pathParts.length; i++) {
      const part = pathParts[i];
      // console.log(`Processing part ${i}: ${part}, current entry type: ${current.type}, name: ${current.name}`);
      
      if (current instanceof DirectoryEntry) {
        // console.log(`Current is directory with ${current.children.length} children, children paths:`, current.children.map(child => child.path));
        
        const found = current.children.find(child => child.path === current.path + '/' + part);
        if (!found) {
          // console.warn(`Part ${part} not found in children, returning null`);
          return null;
        }
        // console.log(`Found child: ${found.name}, type: ${found.type}`);
        current = found;
      } else {
        // console.warn(`Current is not directory, cannot traverse further, returning null`);
        return null;
      }
    }
    
    // console.log(`Final result: ${current.name}, type: ${current.type}`);
    return current;
  }

  window.module.setOrgDirectoryIsDirectoryCallback(directory_opts, is_directory_impl);
  window.module.setOrgDirectoryIsRegularFileCallback(directory_opts, is_regular_file);
  window.module.setOrgDirectoryIsSymlinkCallback(directory_opts, is_symlink);
  window.module.setOrgDirectoryFileReaderCallback(directory_opts, read_file_content);
  window.module.setOrgDirectoryGetDirectoryEntriesCallback(directory_opts,
    get_entry_list);
  window.module.setOrgDirectoryResolveSymlinkCallback(directory_opts,
    resolve_symllink);

  console.log("Running directory parsing");
  const recursive_node
    = window.module.parseDirectoryOpts(test_directory, directory_opts);
  console.log("Recursive node done");
}


export function OrgUseText() {
  const containerRef = useRef<HTMLDivElement>(null);
  const vizRef = useRef<CollapsibleTreeVisualization | null>(null);
  

  useEffect(() => {
    if (!containerRef.current) return;
    test_directory_read();
    

  }, []);

  return (
    <div>
      <div id="visualization" ref={containerRef} />
    </div>
  )
}
