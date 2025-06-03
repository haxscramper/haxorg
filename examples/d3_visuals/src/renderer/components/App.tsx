import { useState, useContext, useEffect, useRef, React } from "react";
import { OrgEditor } from "./Editor.tsx";
import { createContext } from "react";
import {WasmUserTest} from "./WasmUserTest.tsx"

import { FlameGraph } from "./Visualization/FlameGraph.tsx";
import { CollapsibleTree } from "./Visualization/CollapsibleTree.tsx";
import { Stack } from '@mui/material';
import { OrgUseText } from "./Visualization/OrgUseTest.tsx";

export function App() {
  return (
    <Stack>
      {/* <OrgEditor /> */}
      {/* <FlameGraph /> */}
      {/* <CollapsibleTree /> */}

      <OrgUseText />
    </Stack>
  );
}
