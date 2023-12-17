export module hstd.stdlib.Func;

export import std_functional;

export {
template <typename T>
using Func = std::function<T>;
}