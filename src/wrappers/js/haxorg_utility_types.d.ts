export interface Optional<T> {
  has_value(): boolean;
  value(): T;
}

export interface Vec<T> {}

export interface ImmerBox<T> {}

export interface ImmIdT<T> {}

export interface ImmerFlex_vector<T> {}

export interface UnorderedMap<K, V> {}

export interface StdVariant<T1, T2 = never, T3 = never, T4 = never, T5 = never,
                            T6 = never, T7 = never, T8 = never, T9 = never,
                            T10 = never> {}

