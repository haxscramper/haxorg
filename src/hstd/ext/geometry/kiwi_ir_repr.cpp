#include "kiwi_ir.hpp"

#include <hstd/stdlib/ColText.hpp>
#include <hstd/stdlib/Enumerate.hpp>

namespace hstd::ext::kiwi_ir {
namespace {

void repr_impl(
    hstd::ColStream&        os,
    kiwi::Expression const& e,
    int                     indent) {

    int var_size = 8;
    for (auto const& t : e.terms()) {
        var_size = std::max<int>(var_size, t.variable().name().size());
    }

    for (auto const& t : hstd::enumerator(e.terms())) {
        os.newline();
        os.indent(indent);
        os << hstd::fmt(
            "{:<{}} {}",
            t.value().variable(),
            var_size,
            t.value().coefficient());
    }
}

void repr_impl(
    hstd::ColStream&        os,
    kiwi::Constraint const& c,
    int                     indent) {
    switch (c.op()) {
        case kiwi::RelationalOperator::OP_EQ: os << "EQ"; break;
        case kiwi::RelationalOperator::OP_GE: os << "GE"; break;
        case kiwi::RelationalOperator::OP_LE: os << "LE"; break;
    }

    repr_impl(os, c.expression(), 1);
}


void repr_impl(hstd::ColStream& os, Expr::Node const& n, int indent) {
    os.newline();
    os.indent(indent);

    auto write_head = [&](Str const& h) {
        os << h;
        if (n.origin_line != -1) {
            os << hstd::fmt(" {}:{}", n.origin_function, n.origin_line);
        }
    };

    using Kind = Expr::Node::Kind;
    switch (n.kind) {
        case Kind::Constant:
            write_head(hstd::fmt("Const({})", n.constant));
            break;

        case Kind::Variable:
            write_head(hstd::fmt("Var({})", n.variable->name()));
            break;

        case Kind::KiwiExpression: {
            write_head("KiwiExpr");
            int var_size = 8;
            for (auto const& t : n.kiwi_expr->terms()) {
                var_size = std::max<int>(
                    var_size, t.variable().name().size());
            }

            for (auto const& t : hstd::enumerator(n.kiwi_expr->terms())) {
                os.newline();
                os.indent(indent + 1);
                os << hstd::fmt(
                    "{:<{}} {}",
                    t.value().variable(),
                    var_size,
                    t.value().coefficient());
            }

            os.newline();
            os.indent(indent + 1);
            os << hstd::fmt("const {}", n.kiwi_expr->constant());
            break;
        }

        case Kind::Add:
            write_head("Add");
            repr_impl(os, *n.lhs, indent + 1);
            repr_impl(os, *n.rhs, indent + 1);
            break;

        case Kind::Sub:
            write_head("Sub");
            repr_impl(os, *n.lhs, indent + 1);
            repr_impl(os, *n.rhs, indent + 1);
            break;

        case Kind::Mul:
            write_head("Mul");
            repr_impl(os, *n.lhs, indent + 1);
            repr_impl(os, *n.rhs, indent + 1);
            break;

        case Kind::Neg:
            write_head("Neg");
            repr_impl(os, *n.lhs, indent + 1);
            break;
    }
}

void repr_impl(hstd::ColStream& os, Constraint const& c, int indent) {
    os.newline();
    os.indent(indent);

    switch (c.op) {
        case kiwi::RelationalOperator::OP_EQ:
            os << "Constraint(EQ)";
            break;
        case kiwi::RelationalOperator::OP_LE:
            os << "Constraint(LE)";
            break;
        case kiwi::RelationalOperator::OP_GE:
            os << "Constraint(GE)";
            break;
    }

    if (c.origin_line != -1) {
        os << hstd::fmt(" {}:{}", c.origin_function, c.origin_line);
    }

    repr_impl(os, *c.lhs.node, indent + 1);
    repr_impl(os, *c.rhs.node, indent + 1);
}


enum class Prec : int
{
    Add   = 1,
    Mul   = 2,
    Unary = 3,
    Atom  = 4
};

static std::string wrap_if(bool cond, std::string const& s) {
    return cond ? "(" + s + ")" : s;
}

static bool is_zero(double v) { return std::abs(v) < 1e-12; }
static bool is_one(double v) { return std::abs(v - 1.0) < 1e-12; }

struct LinearForm {
    double                        constant = 0.0;
    std::map<std::string, double> terms;
};

static void add_scaled(LinearForm& dst, LinearForm const& src, double k) {
    dst.constant += src.constant * k;
    for (auto const& [name, coef] : src.terms) {
        dst.terms[name] += coef * k;
    }
}

static LinearForm scale(LinearForm const& src, double k) {
    LinearForm out;
    add_scaled(out, src, k);
    return out;
}

static bool has_vars(LinearForm const& f) { return !f.terms.empty(); }

static std::string render_affine(LinearForm const& f) {
    std::string out;
    bool        first = true;

    auto append_signed = [&](bool neg, std::string const& body) {
        if (first) {
            if (neg) { out += "-"; }
            out += body;
            first = false;
        } else {
            out += neg ? " - " : " + ";
            out += body;
        }
    };

    for (auto const& [name, coef] : f.terms) {
        if (is_zero(coef)) { continue; }
        bool   neg = coef < 0.0;
        double a   = std::abs(coef);

        if (is_one(a)) {
            append_signed(neg, name);
        } else {
            append_signed(neg, hstd::fmt("{}{}", a, name));
        }
    }

    if (!is_zero(f.constant) || first) {
        bool   neg = f.constant < 0.0;
        double a   = std::abs(f.constant);
        append_signed(neg, hstd::fmt("{}", a));
    }

    return out;
}

static LinearForm to_linear(Expr::Node const& n) {
    using Kind = Expr::Node::Kind;
    switch (n.kind) {
        case Kind::Constant: {
            LinearForm out;
            out.constant = n.constant;
            return out;
        }
        case Kind::Variable: {
            LinearForm out;
            out.terms[n.variable->name()] = 1.0;
            return out;
        }
        case Kind::KiwiExpression: {
            LinearForm out;
            out.constant = n.kiwi_expr->constant();
            for (auto const& t : n.kiwi_expr->terms()) {
                out.terms[t.variable().name()] += t.coefficient();
            }
            return out;
        }
        case Kind::Add: {
            LinearForm l = to_linear(*n.lhs);
            LinearForm r = to_linear(*n.rhs);
            add_scaled(l, r, 1.0);
            return l;
        }
        case Kind::Sub: {
            LinearForm l = to_linear(*n.lhs);
            LinearForm r = to_linear(*n.rhs);
            add_scaled(l, r, -1.0);
            return l;
        }
        case Kind::Neg: {
            return scale(to_linear(*n.lhs), -1.0);
        }
        case Kind::Mul: {
            LinearForm l = to_linear(*n.lhs);
            LinearForm r = to_linear(*n.rhs);

            if (has_vars(l) && has_vars(r)) {
                throw std::runtime_error(
                    "flat_repr(full_flatten=true): non-linear "
                    "multiplication");
            }

            if (has_vars(l)) { return scale(l, r.constant); }
            if (has_vars(r)) { return scale(r, l.constant); }

            LinearForm out;
            out.constant = l.constant * r.constant;
            return out;
        }
    }

    throw std::runtime_error("unreachable");
}

static int precedence(Expr::Node const& n) {
    using Kind = Expr::Node::Kind;
    switch (n.kind) {
        case Kind::Add:
        case Kind::Sub: return static_cast<int>(Prec::Add);
        case Kind::Mul: return static_cast<int>(Prec::Mul);
        case Kind::Neg: return static_cast<int>(Prec::Unary);
        case Kind::Constant:
        case Kind::Variable:
        case Kind::KiwiExpression: return static_cast<int>(Prec::Atom);
    }
    return static_cast<int>(Prec::Atom);
}

static void collect_add_terms(
    Expr::Node const&                               n,
    int                                             sign,
    std::vector<std::pair<int, Expr::Node const*>>& out) {
    using Kind = Expr::Node::Kind;
    switch (n.kind) {
        case Kind::Add:
            collect_add_terms(*n.lhs, sign, out);
            collect_add_terms(*n.rhs, sign, out);
            break;
        case Kind::Sub:
            collect_add_terms(*n.lhs, sign, out);
            collect_add_terms(*n.rhs, -sign, out);
            break;
        case Kind::Neg: collect_add_terms(*n.lhs, -sign, out); break;
        default: out.push_back({sign, &n}); break;
    }
}

static std::string flat_repr_impl(
    Expr::Node const& n,
    int               parent_prec,
    bool              full_flatten);

static std::string render_kiwi_expr(Expr::Node const& n) {
    LinearForm f;
    f.constant = n.kiwi_expr->constant();
    for (auto const& t : n.kiwi_expr->terms()) {
        f.terms[t.variable().name()] += t.coefficient();
    }
    return render_affine(f);
}

namespace {
bool wrap_all = false;
}

static std::string flat_repr_impl(
    Expr::Node const& n,
    int               parent_prec,
    bool              full_flatten) {
    using Kind = Expr::Node::Kind;

    if (full_flatten) { return render_affine(to_linear(n)); }

    switch (n.kind) {
        case Kind::Constant: return hstd::fmt("{}", n.constant);
        case Kind::Variable: return n.variable->name();
        case Kind::KiwiExpression: return render_kiwi_expr(n);

        case Kind::Neg: {
            auto inner = flat_repr_impl(
                *n.lhs, static_cast<int>(Prec::Unary), false);
            bool need_paren = precedence(*n.lhs)
                            < static_cast<int>(Prec::Unary);
            auto out        = "-" + wrap_if(wrap_all || need_paren, inner);
            return wrap_if(
                wrap_all || static_cast<int>(Prec::Unary) < parent_prec,
                out);
        }

        case Kind::Mul: {
            auto l = flat_repr_impl(
                *n.lhs, static_cast<int>(Prec::Mul), false);
            auto r = flat_repr_impl(
                *n.rhs, static_cast<int>(Prec::Mul), false);

            bool lp = precedence(*n.lhs) < static_cast<int>(Prec::Mul);
            bool rp = precedence(*n.rhs) < static_cast<int>(Prec::Mul);

            auto out = wrap_if(wrap_all || lp, l) + " * "
                     + wrap_if(wrap_all || rp, r);
            return wrap_if(
                wrap_all || static_cast<int>(Prec::Mul) < parent_prec,
                out);
        }

        case Kind::Add:
        case Kind::Sub: {
            std::vector<std::pair<int, Expr::Node const*>> terms;
            collect_add_terms(n, 1, terms);

            std::string out;
            bool        first = true;

            for (auto const& [sign, ptr] : terms) {
                if (ptr->kind == Kind::Constant) {
                    double v = sign * ptr->constant;
                    if (first) {
                        out += hstd::fmt("{}", v);
                        first = false;
                    } else if (v < 0.0) {
                        out += hstd::fmt(" - {}", -v);
                    } else {
                        out += hstd::fmt(" + {}", v);
                    }
                    continue;
                }

                auto body = flat_repr_impl(
                    *ptr, static_cast<int>(Prec::Add), false);

                if (first) {
                    if (sign < 0) { out += "-"; }
                    out += body;
                    first = false;
                } else {
                    out += (sign < 0) ? " - " : " + ";
                    out += body;
                }
            }

            return wrap_if(
                wrap_all || static_cast<int>(Prec::Add) < parent_prec,
                out);
        }
    }

    throw std::runtime_error("unreachable");
}

} // namespace

Str tree_repr(kiwi::Expression const& c, int indent) {
    hstd::ColStream os;
    repr_impl(os, c, indent);
    return os.toString(false);
}

Str tree_repr(kiwi::Constraint const& c, int indent) {
    hstd::ColStream os;
    repr_impl(os, c, indent);
    return os.toString(false);
}

Str tree_repr(Vec<kiwi::Constraint> const& c, int indent) {
    hstd::ColStream os;
    for (auto const& sub_c : c) { repr_impl(os, sub_c, indent); }
    return os.toString(false);
}

Anchor get_anchor(Axis axis, AnchorAxisRelative rel) {
    switch (rel) {
        case AnchorAxisRelative::MIN_POS:
            return axis == Axis::X ? Anchor::LEFT : Anchor::TOP;
        case AnchorAxisRelative::MID_POS:
            return axis == Axis::X ? Anchor::HCENTER : Anchor::VCENTER;
        case AnchorAxisRelative::MAX_POS:
            return axis == Axis::X ? Anchor::RIGHT : Anchor::BOTTOM;
    }
}


Str tree_repr(Expr const& c, int indent) {
    hstd::ColStream os;
    repr_impl(os, *c.node, indent);
    return os.toString(false);
}

Str tree_repr(Constraint const& c, int indent) {
    hstd::ColStream os;
    repr_impl(os, c, indent);
    return os.toString(false);
}

Str tree_repr(Vec<Constraint> const& c, int indent) {
    hstd::ColStream os;
    for (auto const& sub_c : c) { repr_impl(os, sub_c, indent); }
    return os.toString(false);
}

Str flat_repr(Expr const& n, bool full_flatten) {
    return flat_repr_impl(*n.node, 0, full_flatten);
}

Str flat_repr(Constraint const& c, bool full_flatten) {
    Str op;
    switch (c.op) {
        case kiwi::RelationalOperator::OP_EQ: op = "=="; break;
        case kiwi::RelationalOperator::OP_LE: op = "<="; break;
        case kiwi::RelationalOperator::OP_GE: op = ">="; break;
    }

    std::string result = hstd::fmt(
        "{} {} {}",
        flat_repr(c.lhs, full_flatten),
        op,
        flat_repr(c.rhs, full_flatten));

    if (c.origin_line != -1) {
        result += hstd::fmt(" {}:{}", c.origin_function, c.origin_line);
    }

    return result;
}


} // namespace hstd::ext::kiwi_ir
