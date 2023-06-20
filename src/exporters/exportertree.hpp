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
        bool withLineCol     = true;
        bool withOriginalId  = true;
        bool withSubnodeIdx  = true;
        bool skipEmptyFields = true;
        int  startLevel      = 0;

        SemSet skipNodes;
        SemSet skipSubnodesOf;

        bool doSkipSubnodesOf(sem::Org const* org) const {
            return skipSubnodesOf.contains(org->getKind());
        }

        bool doSkip(sem::Org const* org) const {
            return skipNodes.contains(org->getKind());
        }

        TreeReprConf& withSkippedSubnodesOf(OrgSemKind kind) {
            skipSubnodesOf.incl(kind);
            return *this;
        }
    };

    static void treeRepr(sem::SemId org) {
        ColStream os{qcout};
        ExporterTree(os).visitTop(org);
    }


    static void treeRepr(sem::SemId org, CR<TreeReprConf> conf) {
        ColStream    os{qcout};
        ExporterTree exporter{os};
        exporter.conf = conf;
        exporter.visitTop(org);
    }


    struct TreeReprCtx {
        int level      = 0;
        int subnodeIdx = -1;
    };


    ColStream&       os;
    TreeReprConf     conf;
    Vec<TreeReprCtx> stack;

    void pushIndent() {
        stack.push_back(
            {.level = stack.empty() ? conf.startLevel : stack.size()});
    }

    void popIndent() { stack.pop_back(); }
    void pushVisit(int&, sem::SemId org) { pushIndent(); }
    void popVisit(int&, sem::SemId org) { popIndent(); }
    void visitDispatchHook(int&, sem::SemId org) { init(org); }
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


    void init(sem::SemId org);

    template <typename T>
    bool skipAsEmpty(CR<Opt<T>> opt) {
        return conf.skipEmptyFields && !opt;
    }

    template <typename T>
    bool skipAsEmpty(CVec<T> vec) {
        return conf.skipEmptyFields && vec.empty();
    }

    template <typename T>
    bool skipAsEmpty(CR<T> value) {
        return false;
    }

    template <typename T>
    void visit(int& arg, CR<Vec<T>> value) {
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

    template <typename T>
    void visit(int& arg, CR<T> opt)
        requires(std::is_enum<T>::value)
    {
        __scope();
        indent();
        os << os.red() << to_string(opt) << os.end() << "\n";
    }

    template <typename T>
    void visit(int& arg, CR<T> opt)
        requires(!std::is_enum<T>::value)
    {
        __scope();
        indent();
        os << os.red() << demangle(typeid(T).name()) << os.end() << "\n";
    }

    template <typename K, typename V>
    void visit(int& arg, CR<UnorderedMap<K, V>> opt) {
        // TODO
    }

    void visitField(int& i, const char* name, CVec<sem::SemId> org);


    template <typename T>
    void visitField(int& arg, const char* name, CR<T> value) {
        if (skipAsEmpty(value)) {
            return;
        }

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

    void visitField(int& arg, const char* name, sem::SemId org);


    ExporterTree(ColStream& os) : os(os) {}
};

#endif // EXPORTERTREE_HPP
