export interface Optional<T> {
  has_value(): boolean;
  value(): T;
}
