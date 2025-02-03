import { useState, useContext, useEffect, useRef, React } from "react";
import { OrgEditor } from "./Editor.tsx";
import { createContext } from "react";

const EditorContext = createContext<OrgEditor | null>(null);

function EditorUI() {
  const containerRef = useRef<HTMLDivElement>(null);
  const editor = useContext(EditorContext);

  useEffect(() => {
    if (editor && containerRef.current) {
      editor.initializeEditor(containerRef.current);
    }
    return () => editor?.destroyEditor();
  }, [editor]);

  return (
    <div className="editor-container">
      <div ref={containerRef} className="blocknote-editor"
        style={{ height: "100vh", width: "100vw" }} />
    </div>
  );
}

export function App() {
  const [editor] = useState(() => new OrgEditor());

  return (
    <EditorContext.Provider value={editor}>
      <EditorUI />
    </EditorContext.Provider>
  );
}
