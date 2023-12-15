#pragma once

#include <range/v3/all.hpp>


namespace rv = ranges::views;
namespace rs = ranges;
using ranges::operator|;



template <class T>
struct generator_view : rs::view_facade<generator_view<T>> {
  private:
    friend rs::range_access;
    struct Data {
        generator<T>           gen_;
        generator<T>::iterator iter;
        explicit Data(generator<T>&& gen)
            : gen_(std::move(gen)), iter(gen_.begin()) {
            ++iter;
        }
    };

    SPtr<Data> data;

    struct cursor {
      private:
        friend rs::range_access;
        using single_pass    = std::true_type;
        generator_view* rng_ = nullptr;

      public:
        cursor() = default;
        explicit cursor(generator_view* rng) : rng_(rng) {}

        void next() { rng_->next(); }
        T&   read() const noexcept { return rng_->cached(); }
        bool equal(rs::default_sentinel_t) const {
            return rng_->data->iter == rng_->data->gen_.end();
        }
    };

    void next() { ++data->iter; }

    cursor begin_cursor() { return cursor{this}; }

  public:
    generator_view() = default;
    explicit generator_view(generator<T>&& gen)
        : data(std::make_shared<Data>(std::move(gen))) {
        // ++data->iter;
    }

    T& cached() noexcept { return *data->iter; }
};

template <typename T>
generator_view<T> gen_view(generator<T>&& gen) {
    return generator_view<T>(std::move(gen));
}

template <class T>
struct owning_range : rs::view_facade<owning_range<T>> {
    using iterator = std::remove_cvref_t<
        decltype(std::declval<T>().begin())>;
    using value_type = iterator::value_type;

  private:
    friend rs::range_access;
    struct Data {
        T        gen_;
        iterator iter;
        explicit Data(T&& gen)
            : gen_(std::move(gen)), iter(gen_.begin()) {}
    };

    SPtr<Data> data;

    struct cursor {
      private:
        friend rs::range_access;
        using single_pass  = std::true_type;
        owning_range* rng_ = nullptr;

      public:
        cursor() = default;
        explicit cursor(owning_range* rng) : rng_(rng) {}

        void        next() { rng_->next(); }
        value_type& read() const noexcept { return rng_->cached(); }
        bool        equal(rs::default_sentinel_t) const {
            return rng_->data->iter == rng_->data->gen_.end();
        }
    };

    void next() { ++data->iter; }

    cursor begin_cursor() { return cursor{this}; }

  public:
    owning_range() = default;
    explicit owning_range(T&& gen)
        : data(std::make_shared<Data>(std::move(gen))) {}

    value_type& cached() noexcept { return *data->iter; }
};

template <typename T>
owning_range<T> own_view(T&& gen) {
    return owning_range<T>(std::move(gen));
}


template <class Rng>
struct transform_view
    : public rs::
          view_interface<transform_view<Rng>, rs::cardinality::finite> {

    using Collected      = std::vector<rs::range_value_t<Rng>>;
    using iterator       = typename Collected::iterator;
    using const_iterator = typename Collected::const_iterator;
    using value_type     = typename Collected::value_type;

    Collected values;
    iterator  iter;

    constexpr const_iterator begin() const noexcept {
        return values.begin();
    }

    constexpr const_iterator end() const noexcept { return values.end(); }
    constexpr iterator       begin() noexcept { return values.begin(); }
    constexpr iterator       end() noexcept { return values.end(); }
    constexpr bool           empty() const { return values.empty(); }
    constexpr auto           size() const { return values.size(); }
    void                     next() { ++iter; }
    void                     prev() { --iter; }
    constexpr auto&          advance(rs::iter_difference_t<iterator> n) {
        iter += n;
        return *this;
    }

    transform_view() = default;
    transform_view(Rng&& rng) {
        for (auto const& it : rng) {
            values.push_back(it);
        }
        iter = values.begin();
    }
};

template <class Rng>
transform_view<Rng> transform(Rng&& rng) {
    return {std::forward<Rng>(rng)};
}

template <typename Rng>
    requires rs::viewable_range<Rng>
void take_viewable_range(Rng const& r) {}

template <typename Rng>
    requires rs::bidirectional_range<Rng>
void take_bidirectional_range(Rng const& r) {}

inline auto make_collect() {
    auto tran = transform(rv::iota(1, 4));
    using T   = decltype(tran);
    take_viewable_range(tran);
    take_bidirectional_range(tran);
    rs::views::reverse(tran);

    return rs::make_pipeable([](auto&& rng) {
        auto tran = transform(rng);
        using T   = decltype(tran);
        static_assert(requires() { rs::bidirectional_range<T>; });
        static_assert(requires() { rs::viewable_range<T>; });
        return tran;
    });
}

template <typename T, typename In>
generator<T> indexed_get_iterator(
    In const&               in,
    Func<int(In const&)>    size_get,
    Func<T(In const&, int)> getter) {
    int size = size_get(in);
    for (int i = 0; i < size; ++i) {
        co_yield getter(in, i);
    }
}
