export interface Optional<T> {
  has_value(): boolean;
  value(): T;
}

export interface Vec<T> {
  toArray(): T[];
}

export interface ImmerBox<T> {}

export type ImmBox<T> = ImmerBox<T>;

export interface ImmIdT<T> {}

export interface ImmerFlex_vector<T> {}
export type      ImmVec<T> = ImmerFlex_vector<T>;

export interface UnorderedMap<K, V> {}

export interface StdVariant<T1, T2 = never, T3 = never, T4 = never, T5 = never,
                            T6 = never, T7 = never, T8 = never, T9 = never,
                            T10 = never, T11 = never, T12 = never, T13 = never,
                            T14 = never, T15 = never, T16 = never, T17 = never,
                            T18 = never, T19 = never, T20 = never, T21 = never,
                            T22 = never, T23 = never, T24 = never, T25 = never
                            //
                            > {}

export interface haxorg_wasm_manual {
  setOrgDirectoryFileReaderCallback(config: any,
                                    callback: (path: string) => string): void;

  setOrgDirectoryIsSymlinkCallback(config: any,
                                   callback: (path: string) => boolean): void;

  setOrgDirectoryIsRegularFileCallback(config: any,
                                       callback: (path: string) => boolean):
      void;

  setOrgDirectoryIsDirectoryCallback(config: any,
                                     callback: (path: string) => boolean): void;

  setOrgDirectoryResolveSymlinkCallback(config: any,
                                        callback: (path: string) => string):
      void;

  setOrgDirectoryGetDirectoryEntriesCallback(
      config: any, callback: (path: string) => string[]): void;
}
