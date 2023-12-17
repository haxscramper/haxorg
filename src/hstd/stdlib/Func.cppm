export module hstd.stdlib.Func;

import std;

export {
template <typename T>
using Func = std::function<T>;
}