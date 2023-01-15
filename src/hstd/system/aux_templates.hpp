template <int N, int M>
struct pow_v {
    enum
    {
        res = N * pow_v<N, M - 1>::res
    };
};


template <int N>
struct pow_v<N, 0> {
    enum
    {
        res = 1
    };
};
