#pragma once

#include <coroutine>
#include <type_traits>
#include <optional>

template <typename T>
struct generator {
    struct promise_type {
        std::optional<T>    current_value;
        std::suspend_always yield_value(T value) {
            this->current_value = value;
            return {};
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        generator get_return_object() { return generator{this}; };
        void      unhandled_exception() { std::terminate(); }
        void      return_void() {}
    };

    class iterator {
        std::coroutine_handle<promise_type> coro;
        bool                                done;

      public:
        iterator(std::coroutine_handle<promise_type> _coro, bool _done)
            : coro(_coro), done(_done) {}

        bool operator==(iterator const& _right) const {
            return done == _right.done;
        }
        bool operator!=(iterator const& _right) const {
            return !(*this == _right);
        }
        T const& operator*() const {
            return coro.promise().current_value.value();
        }
        T& operator*() { return coro.promise().current_value.value(); }

        iterator& operator++() {
            coro.resume();
            done = coro.done();
            return *this;
        }

        // T* requires !std::is_lvalue_reference_v<T> operator->() {
        //     return &(operator*());
        // }
        // T const* requires !std::is_lvalue_reference_v<T> operator->()
        //     const {
        //     return &(operator*());
        // }
    };

    iterator begin() {
        p.resume();
        return {p, p.done()};
    }
    iterator end() { return {p, true}; }
    generator(generator const&) = delete;
    generator(generator&& rhs) : p(rhs.p) { rhs.p = nullptr; }
    ~generator() {
        if (p) {
            p.destroy();
        }
    }

  private:
    explicit generator(promise_type* p)
        : p(std::coroutine_handle<promise_type>::from_promise(*p)) {}

    std::coroutine_handle<promise_type> p;
};
