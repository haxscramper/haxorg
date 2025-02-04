import { useState, useContext, useEffect, useRef, React } from "react";
import { OrgEditor } from "./Editor.tsx";
import { createContext } from "react";

// const EditorContext = createContext<OrgEditor | null>(null);

// function EditorUI() {
//   // Creates a new editor instance.
//   const editor = useCreateBlockNote();
 
//   // Renders the editor instance using a React component.
//   return <BlockNoteView editor={editor} />;
// }

export function App() {
  return (
    // <EditorContext.Provider value={editor}>
      <OrgEditor />
    // </EditorContext.Provider>
  );
}
