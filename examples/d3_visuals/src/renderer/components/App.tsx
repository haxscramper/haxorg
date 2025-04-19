import { useState, useContext, useEffect, useRef, React } from "react";
import { OrgEditor } from "./Editor.tsx";
import { createContext } from "react";
import {WasmUserTest} from "./WasmUserTest.tsx"

import { FlameGraph } from "./Visualization/FlameGraph.tsx";
import { Stack } from '@mui/material';

export function App() {
  return (
    <Stack>
      <WasmUserTest/>
      <OrgEditor />
      <FlameGraph />
    </Stack>
  );
}
