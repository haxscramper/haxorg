// src/renderer/components/WasmUserTest.tsx
import React, { useState, useEffect } from 'react';
import { initWasmModule } from '../wasm_client';

export const WasmUserTest: React.FC = () => {
  const [isWasmReady, setIsWasmReady] = useState(!!window.haxorgWasm);
  const [result, setResult] = useState<number | null>(null);

  useEffect(() => {
    if (!isWasmReady) {
      initWasmModule()
        .then(() => setIsWasmReady(true))
        .catch(err => console.error('Failed to load WASM in component:', err));
    }
  }, [isWasmReady]);

  const handleCalculate = () => {
    if (!window.haxorgWasm) {
      console.error('WASM not ready');
      return;
    }

    console.log("Parse string")
    // Direct synchronous call
    const node = window.haxorgWasm.parseString("text");
    setResult(1231);
  };

  return (
    <div>
      <h2>WASM Test Component</h2>
      <button disabled={!isWasmReady} onClick={handleCalculate}>
        {isWasmReady ? 'Calculate 5 + 10' : 'Loading WASM...'}
      </button>
      {result !== null && <p>Result: {result}</p>}
    </div>
  );
};

export default WasmUserTest;
