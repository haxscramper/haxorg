#ifndef EXPORTERTREE_HPP
#define EXPORTERTREE_HPP

#include <hstd/stdlib/ColText.hpp>
#include <exporters/Exporter.hpp>

class ExporterTree : public Exporter<ExporterTree, int> {
  public:
    using Base = Exporter<ExporterTree, int>;

#define __ExporterBase Base
    EXPORTER_USING();
#undef __ExporterBase

    struct TreeReprConf {
        bool withLineCol    = true;
        bool withOriginalId = true;
        bool withSubnodeIdx = true;

        SemSet skipNodes;
        SemSet skipSubnodesOf;

        bool doSkipSubnodesOf(sem::Org const* org) const {
            return skipSubnodesOf.contains(org->getKind());
        }

        bool doSkip(sem::Org const* org) const {
            return skipNodes.contains(org->getKind());
        }
    };

    struct TreeReprCtx {
        int level      = 0;
        int subnodeIdx = -1;
    };


    ColStream&       os;
    TreeReprConf     conf;
    Vec<TreeReprCtx> stack;

    void pushIndent() {
        stack.push_back({.level = stack.empty() ? 0 : stack.size()});
    }

    void popIndent() { stack.pop_back(); }
    void pushVisit(int&, sem::Wrap<sem::Org> org) { pushIndent(); }
    void popVisit(int&, sem::Wrap<sem::Org> org) { popIndent(); }
    void visitDispatchHook(int&, sem::Wrap<sem::Org> const org) {
        init(org);
    }
    void indent() { os << QString("  ").repeated(stack.back().level); }

    struct ScopedField {
        ExporterTree* exp;
        ScopedField(ExporterTree* exp) : exp(exp) { exp->pushIndent(); }
        ~ScopedField() { exp->popIndent(); }
    };

#define __scope() ScopedField CONCAT(close, __COUNTER__){this};


    template <typename T>
    int newRes(CR<T>) {
        return 0;
    }


    void init(sem::Wrap<sem::Org> org) {
        auto ctx = stack.back();
        indent();
        os << os.green() << to_string(org->getKind()) << os.end();

        if (conf.withSubnodeIdx && ctx.subnodeIdx != -1) {
            os << " [" << ctx.subnodeIdx << "]";
        }

        if (conf.withOriginalId) {
            os << " ID:" << org->original.id.getUnmasked();
        }

        if (conf.withLineCol && org->loc.has_value()) {
            auto& [line, col] = org->loc.value();
            os << " " << os.cyan() << line << ":" << col << os.end();
        }
        os << "\n";
    }

    template <typename T>
    void visit(int& arg, CR<Vec<T>> const& value) {
        __scope();
        if (value.empty()) {
            indent();
            os << os.cyan() << "<empty>" << os.end() << "\n";
        } else {
            for (const auto& it : value) {
                visit(arg, it);
            }
        }
    }

    template <typename T>
    void visit(int& arg, CR<Opt<T>> opt) {
        __scope();
        if (opt) {
            visit(arg, *opt);
        } else {
            indent();
            os << os.cyan() << "<none>" << os.end() << "\n";
        }
    }

    template <typename K, typename V>
    void visit(int& arg, CR<UnorderedMap<K, V>> opt) {
        // TODO
    }

    template <typename T>
    void visitField(int& arg, const char* name, CR<T> value) {
        __scope();
        indent();
        os << name << " (" << os.green() << demangle(typeid(T).name())
           << os.end() << ")";
        if constexpr (std::is_same_v<T, int>) {
            os << " = " << os.cyan() << value << os.end() << "\n";
        } else if constexpr (std::is_same_v<T, Str>) {
            os << " = " << os.yellow() << escape_literal(value) << os.end()
               << "\n";
        } else {
            os << "\n";
            visit(arg, value);
        }
    }

    void visitField(int& arg, const char* name, sem::Wrap<sem::Org> org) {
        __scope();
        indent();
        os << name << ":"
           << "\n";
        Base::visitField(arg, name, org);
    }


    ExporterTree(ColStream& os) : os(os) {}
};

#endif // EXPORTERTREE_HPP
