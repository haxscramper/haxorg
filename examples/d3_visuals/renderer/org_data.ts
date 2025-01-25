
import {log} from "./org_logger.ts"

// Type definitions for service metadata
export interface ParamDefinition {
  readonly name: string;
  readonly type: string;
  readonly optional?: boolean;
  readonly default?: any;
}

export interface MethodDefinition {
  readonly name: string;
  readonly parameters: readonly ParamDefinition[];
  readonly result: string;
}

export interface ServiceDefinition {
  readonly name: string;
  readonly methods: {[key: string]: MethodDefinition;};
}

// Helper type for tuple to union conversion
type TupleToUnion<T extends readonly any[]> = T[number];

export interface ImmId {
  format: string;
  number: number;
}

export interface ImmReflPathStep {}

export interface ImmReflPath {
  path: ImmReflPathStep[];
  root: ImmId;
}

export interface ImmUniqId {
  id: ImmId;
  path: ImmReflPath;
}

// Improved type inference helpers
export type InferParamType<T extends string> =
    // clang-format off
    T extends 'string' ? string : 
    T extends 'number' ? number : 
    T extends 'bool' | 'boolean' ? boolean :
    T extends 'null' ? null :
    T extends 'undefined' ? undefined :
    T extends 'void' ? void :
    T extends 'any' ? any :
    T extends 'object' ? object :
    T extends `Array<${infer U}>` ? Array<InferParamType<U>> :
    T extends `Map<${infer K},${infer V}>` ? Map<InferParamType<K>, InferParamType<V>> :
    T extends `Set<${infer U}>` ? Set<InferParamType<U>> :
    T extends `Promise<${infer U}>` ? Promise<InferParamType<U>> :
    T extends `${infer U}[]` ? InferParamType<U>[] :
    T extends keyof GlobalTypes ? GlobalTypes[T] :
                        // clang-format on
            unknown;

export interface GlobalTypes {
  "ImmUniqId": ImmUniqId,
}

export type InferMethodParams<T extends MethodDefinition> = {
  [P in TupleToUnion<T["parameters"]>as
   P["name"]]: P["optional"] extends true ? InferParamType<P["type"]>|undefined
                                          : InferParamType<P["type"]>
};

export type InferServiceClient<T extends ServiceDefinition> = {
  [M in keyof T["methods"]]: (params: InferMethodParams<T["methods"][M]>) =>
      Promise<InferParamType<T["methods"][M]["result"]>>
};

import {data} from "./org_schema.ts";

// Example service definition
export const OrgServiceDefinition = data;

export type OrgClient = InferServiceClient<typeof OrgServiceDefinition>;

// Client implementation
export function createWebSocketClient(ws: WebSocket): OrgClient {
  // Use any temporarily to avoid index signature issue
  const client = {} as any;

  const definition = OrgServiceDefinition as ServiceDefinition;

  for (const [methodName, methodDef] of Object.entries(definition.methods)) {
    client[methodName] = async (params: any) => {
      return new Promise((resolve, reject) => {
        const id = Math.random().toString(36).substr(2, 9);

        // Convert params to expected format
        const args = {};
        // log.info(`TS params ${JSON.stringify(params)}`)
        for (const param of methodDef.parameters) {
          if (params[param.name] !== undefined) {
            args[param.name] = params[param.name];
          } else if ("default" in param) {
            args[param.name] = param.default;
          } else if (!param.optional) {
            throw new Error(`Missing required parameter: ${param.name}`);
          }
        }

        // Send request
        ws.send(JSON.stringify(
            {target : `/api/${methodName}`, id : id, body : args}));

        // Handle response
        const handler = (event: MessageEvent) => {
          const response = JSON.parse(event.data);
          if (response.id === id) {
            if (response.error) {
              log.error(
                  `ID: ${id} got response: ${JSON.stringify(response.error)}`)
            }
            ws.removeEventListener("message", handler);
            resolve(response.body);
          }
        };

        ws.addEventListener("message", handler);
      });
    };
  }

  return client as OrgClient;
}
