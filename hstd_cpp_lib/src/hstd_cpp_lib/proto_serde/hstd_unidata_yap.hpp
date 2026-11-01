#pragma once

#include <boost/hana/at.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/yap/expression.hpp>

#include <hstd_cpp_lib/proto_serde/hstd_unidata_ops.hpp>

#include <functional>
#include <tuple>
#include <type_traits>
#include <utility>

namespace hstd::ext::unidata::expr {

struct State {
    VerifyContext const* ctx;
    EvalRuntime const*   runtime = nullptr;
};

/// All terminal payloads and expression children are stored by value.
/// UniStatic/UniDynamic copies retain their existing ownership and paths.
template <typename T>
auto value(T item) {
    using Elements = boost::hana::tuple<T>;
    return boost::yap::expression<boost::yap::expr_kind::terminal, Elements>{
        Elements{std::move(item)}};
}

template <typename Function, typename... Children>
auto node(Function function, Children... children) {
    auto elements = boost::hana::make_tuple(
        value(std::move(function)), std::move(children)...);

    return boost::yap::expression<boost::yap::expr_kind::call, decltype(elements)>{
        std::move(elements)};
}

template <typename Expression>
auto evaluate(Expression const& expression, State const& state);

namespace detail {

template <typename Expression, std::size_t... I>
auto evaluate_call(
    Expression const& expression,
    State const&      state,
    std::index_sequence<I...>) {
    auto const& function = boost::hana::at_c<0>(
        boost::hana::at_c<0>(expression.elements).elements);

    return function.eval(state, boost::hana::at_c<I + 1>(expression.elements)...);
}

/// Braced initialization sequences child evaluations left to right.
/// The resulting tuple owns the materialized arguments.
template <typename... Children>
auto evaluate_arguments(State const& state, Children const&... children) {
    return std::tuple<decltype(evaluate(children, state))...>{
        evaluate(children, state)...};
}

template <OpId Kind>
inline constexpr bool needs_runtime = Kind == OpId::WALK || Kind == OpId::IS_DERIVED
                                   || Kind == OpId::PATH_OF || Kind == OpId::TYPE_OF;

template <OpId Kind, typename Result, typename... TemplateArgs>
struct Operation {
    ExprContext context;

    template <typename... Children>
    Result eval(State const& state, Children const&... children) const {
        auto arguments = evaluate_arguments(state, children...);

        return std::apply(
            [&](auto const&... args) -> Result {
                if constexpr (needs_runtime<Kind>) {
                    return eval_op<Kind, Result, TemplateArgs...>(
                        context, *state.runtime, args...);
                } else {
                    return eval_op<Kind, Result, TemplateArgs...>(context, args...);
                }
            },
            arguments);
    }
};

template <OpId Kind, typename Result, int Index>
struct IndexedOperation {
    ExprContext context;

    template <typename... Children>
    Result eval(State const& state, Children const&... children) const {
        auto arguments = evaluate_arguments(state, children...);

        return std::apply(
            [&](auto const&... args) -> Result {
                return eval_op<Kind, Result, Index>(context, args...);
            },
            arguments);
    }
};

template <typename Result, typename Native>
struct Constant {
    Native      stored;
    std::string text;

    Result eval(State const&) const { return Result::FromConst(stored, text); }
};

template <OpId Kind>
struct Scope {
    ExprContext context;

    template <typename Child>
    auto eval(State const& state, Child const& child) const {
        UNIDATA_SCOPE(context.ctx, context.file_basename, context.file_line, Kind);

        return evaluate(child, state);
    }
};

template <OpId Kind>
struct Logic {
    static_assert(Kind == OpId::AND || Kind == OpId::OR);

    template <typename... Children>
    S<bool> eval(State const& state, Children const&... children) const {
        constexpr bool is_and = Kind == OpId::AND;

        auto result = S<bool>::FromConst(is_and, is_and ? "true" : "false");

        auto consume = [&](auto const& child) {
            bool const current = get_stored_value(result);

            if (is_and ? current : !current) {
                set_value(result, evaluate(child, state));
            }
        };

        (consume(children), ...);
        return result;
    }
};

template <typename Result>
struct Conditional {
    template <typename Condition, typename Then, typename Else>
    Result eval(
        State const&     state,
        Condition const& condition,
        Then const&      then_expression,
        Else const&      else_expression) const {
        auto tested = evaluate(condition, state);

        if (get_stored_value(tested)) { return evaluate(then_expression, state); }

        return evaluate(else_expression, state);
    }
};

template <typename Body>
struct Let {
    Body body;

    template <typename Bound>
    auto eval(State const& state, Bound const& bound) const {
        auto materialized = evaluate(bound, state);
        auto expression   = body(materialized);
        return evaluate(expression, state);
    }
};

/// Converts a generated expression-producing lambda into an ordinary
/// materialized-value callback accepted by the existing collection operations.
template <typename Body>
struct Closure {
    Body body;

    auto eval(State const& state) const {
        return [state, body = body](auto const&... args) {
            auto expression = body(args...);
            return evaluate(expression, state);
        };
    }
};

template <typename Target, typename Body>
struct TypeCase {
    using target_type = Target;
    Body body;
};

template <typename Result, bool Optional>
struct TypeConditional {
    ExprContext context;
    std::string unmatched_message;

    template <typename Slot, typename Subject, typename CaseExpression>
    bool try_case(
        State const&          state,
        Slot&                 slot,
        Subject const&        subject,
        CaseExpression const& expression) const {
        auto branch  = evaluate(expression, state);
        using Branch = std::remove_cvref_t<decltype(branch)>;

        auto candidate = state.runtime->template try_as<typename Branch::target_type>(
            subject);

        if (!candidate.has_value()) { return false; }

        auto body   = branch.body(*candidate);
        auto result = evaluate(body, state);
        set_value(slot, result);
        return true;
    }

    template <typename Subject, typename... Cases>
    Result eval(
        State const&   state,
        Subject const& subject_expression,
        Cases const&... cases) const {
        auto subject = evaluate(subject_expression, state);

        if constexpr (Optional) {
            auto slot = Result::FromConst(std::nullopt, "std::nullopt");

            bool const matched = (false || ... || try_case(state, slot, subject, cases));

            static_cast<void>(matched);
            return slot;
        } else {
            using Slot = S<UniOpt<Result>>;

            auto slot = Slot::FromConst(std::nullopt, "std::nullopt");

            bool const matched = (false || ... || try_case(state, slot, subject, cases));

            if (!matched) { throw std::runtime_error{unmatched_message}; }

            return get_value_ref(slot);
        }
    }
};

/// Record-level CASE_IS/CASE_WHICH accessors operate on the stored record,
/// not on UniStatic itself.
template <OpId Kind, typename Result, typename Method>
struct MemberOperation {
    ExprContext context;
    Method      method;
    std::string name;

    template <typename Source>
    Result eval(State const& state, Source const& expression) const {
        auto source = evaluate(expression, state);

        return eval_op_traced<Kind, Result>(
            context,
            [&]() -> Result {
                return source.CallResult(std::invoke(method, *source.get()), name);
            },
            source);
    }
};

} // namespace detail

template <typename Expression>
auto evaluate(Expression const& expression, State const& state) {
    using E = std::remove_cvref_t<Expression>;

    if constexpr (E::kind == boost::yap::expr_kind::terminal) {
        return boost::hana::at_c<0>(expression.elements);
    } else {
        static_assert(
            E::kind == boost::yap::expr_kind::call,
            "Unsupported unidata expression node");

        constexpr std::size_t size = decltype(boost::hana::length(
            expression.elements))::value;

        return detail::evaluate_call(
            expression, state, std::make_index_sequence<size - 1>{});
    }
}

template <OpId Kind, typename Result, typename... TemplateArgs, typename... Children>
auto op(ExprContext context, Children... children) {
    return node(
        detail::Operation<Kind, Result, TemplateArgs...>{context},
        std::move(children)...);
}

template <OpId Kind, typename Result, int Index, typename... Children>
auto indexed_op(ExprContext context, Children... children) {
    return node(
        detail::IndexedOperation<Kind, Result, Index>{context}, std::move(children)...);
}

template <typename Result, typename Native>
auto constant(Native stored, std::string text) {
    return node(
        detail::Constant<Result, Native>{
            std::move(stored),
            std::move(text),
        });
}

template <OpId Kind, typename Child>
auto scoped(ExprContext context, Child child) {
    return node(detail::Scope<Kind>{context}, std::move(child));
}

template <OpId Kind, typename... Children>
auto logic(Children... children) {
    return node(detail::Logic<Kind>{}, std::move(children)...);
}

template <typename Result, typename Condition, typename Then, typename Else>
auto conditional(Condition condition, Then then_expression, Else else_expression) {
    return node(
        detail::Conditional<Result>{},
        std::move(condition),
        std::move(then_expression),
        std::move(else_expression));
}

template <typename Bound, typename Body>
auto let(Bound bound, Body body) {
    return node(detail::Let<Body>{std::move(body)}, std::move(bound));
}

template <typename Body>
auto closure(Body body) {
    return node(detail::Closure<Body>{std::move(body)});
}

template <typename Target, typename Body>
auto type_case(Body body) {
    return value(detail::TypeCase<Target, Body>{std::move(body)});
}

template <typename Result, bool Optional, typename Subject, typename... Cases>
auto type_conditional(
    ExprContext context,
    Subject     subject,
    std::string unmatched_message,
    Cases... cases) {
    return node(
        detail::TypeConditional<Result, Optional>{
            context,
            std::move(unmatched_message),
        },
        std::move(subject),
        std::move(cases)...);
}

template <OpId Kind, typename Result, typename Source, typename Method>
auto member(ExprContext context, Source source, Method method, std::string name) {
    return node(
        detail::MemberOperation<Kind, Result, Method>{
            context,
            method,
            std::move(name),
        },
        std::move(source));
}

template <typename Condition, typename Message>
VerifyResult verify(
    State const&     state,
    Condition const& condition,
    Message const&   message) {
    auto result = evaluate(condition, state);

    if (get_stored_value(result)) { return VerifyResult::Ok(); }

    auto diagnostic = evaluate(message, state);
    return VerifyResult::Error(get_stored_value(diagnostic));
}

} // namespace hstd::ext::unidata::expr
