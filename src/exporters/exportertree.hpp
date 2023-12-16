#ifndef EXPORTERTREE_HPP
#define EXPORTERTREE_HPP

import std.stdlib.ColText;
#include <exporters/Exporter.hpp>

struct QFileInfo;

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

    static void treeRepr(sem::SemId org);
    static void treeRepr(
        sem::SemId                   org,
        const std::filesystem::path& path);
    static void treeRepr(sem::SemId org, CR<TreeReprConf> conf);

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
    void indent() { os << Str("  ").repeated(stack.back().level); }

    struct ScopedField {
        ExporterTree* exp;
        ScopedField(ExporterTree* exp) : exp(exp) { exp->pushIndent(); }
        ~ScopedField() { exp->popIndent(); }
    };

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
    void visit(int& arg, CR<Vec<T>> value);

    template <typename T>
    void visit(int& arg, CR<Opt<T>> opt);

    template <typename T>
    std::string typeName() {
        return Str(demangle(typeid(T).name())).replaceAll("sem::", "");
    }

    template <typename T>
    void visit(int& arg, CR<T> opt);

    template <typename K, typename V>
    void visit(int& arg, CR<UnorderedMap<K, V>> opt) {
        // TODO
    }

    void visitField(int& i, const char* name, CVec<sem::SemId> org);


    template <typename T>
    void visitField(int& arg, const char* name, CR<T> value);

    void visitField(int& arg, const char* name, sem::SemId org);

    template <typename T>
    void visitField(int& arg, const char* name, sem::SemIdT<T> org);

    template <typename T>
    void visit(int& arg, sem::SemIdT<T> org);

    ExporterTree(ColStream& os) : os(os) {}
};

extern template class Exporter<ExporterTree, int>;

#endif // EXPORTERTREE_HPP
