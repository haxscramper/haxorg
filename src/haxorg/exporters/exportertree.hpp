#pragma once

#include <hstd/stdlib/ColText.hpp>
#include <haxorg/exporters/Exporter.hpp>

namespace org::algo {
struct QFileInfo;

class ExporterTree : public Exporter<ExporterTree, int> {
  public:
    using Base = Exporter<ExporterTree, int>;

#define __ExporterBase Base
    EXPORTER_USING();
#undef __ExporterBase

    struct TreeReprConf {
        bool withLineCol         = true;
        bool withOriginalId      = true;
        bool withSubnodeIdx      = true;
        bool withTypeAnnotations = false;
        bool skipEmptyFields     = true;
        int  startLevel          = 0;
        int  maxTreeDepth        = 40;

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

    static hstd::ColText treeRepr(sem::SemId<sem::Org> org);
    static void          treeRepr(
                 sem::SemId<sem::Org>         org,
                 const std::filesystem::path& path);
    static hstd::ColText treeRepr(
        sem::SemId<sem::Org> org,
        TreeReprConf const&  conf);

    struct TreeReprCtx {
        int level      = 0;
        int subnodeIdx = -1;
    };


    hstd::ColStream&       os;
    TreeReprConf           conf;
    hstd::Vec<TreeReprCtx> stack;

    void pushIndent() {
        stack.push_back(
            {.level = stack.empty() ? conf.startLevel : stack.size()});
    }

    void popIndent() { stack.pop_back(); }
    void pushVisit(int&, sem::SemId<sem::Org> org) { pushIndent(); }
    void popVisit(int&, sem::SemId<sem::Org> org) { popIndent(); }
    void visitDispatchHook(int&, sem::SemId<sem::Org> org) { init(org); }
    void indent() {
        if (stack.back().level != 0) {
            hstd::Str value = hstd::Str("  ").repeated(stack.back().level);
            os << value;
        }
    }

    struct ScopedField {
        ExporterTree* exp;
        ScopedField(ExporterTree* exp) : exp(exp) { exp->pushIndent(); }
        ~ScopedField() { exp->popIndent(); }
    };

    template <typename T>
    int newRes(T const&) {
        return 0;
    }


    void init(sem::SemId<sem::Org> org);

    bool skipAsTooNested() const;

    template <typename T>
    bool skipAsEmpty(hstd::Opt<T> const& opt) {
        return conf.skipEmptyFields && !opt;
    }

    template <typename T>
    bool skipAsEmpty(hstd::CVec<T> vec) {
        return conf.skipEmptyFields && vec.empty();
    }

    template <typename T>
    bool skipAsEmpty(T const& value) {
        return false;
    }

    void writeSkip(
        hstd::Str const& message,
        hstd::Str const& trail    = "",
        int              line     = __builtin_LINE(),
        char const*      function = __builtin_FUNCTION());

    template <typename T>
    void visit(int& arg, hstd::Vec<T> const& value);

    template <typename T>
    void visit(int& arg, hstd::Opt<T> const& opt);

    template <typename T>
    void visit(int& arg, T const& opt);

    template <typename K, typename V>
    void visit(int& arg, hstd::UnorderedMap<K, V> const& opt) {
        // TODO
    }

    template <typename V>
    void visit(int& arg, hstd::UnorderedMap<hstd::Str, V> const& opt);

    void visitField(
        int&                             i,
        const char*                      name,
        hstd::CVec<sem::SemId<sem::Org>> org);


    template <typename T>
    void visitField(int& arg, const char* name, T const& value);

    void visitField(int& arg, const char* name, sem::SemId<sem::Org> org);

    template <typename T>
    void visitField(int& arg, const char* name, sem::SemId<T> org);

    template <typename T>
    void visit(int& arg, sem::SemId<T> org);

    ExporterTree(hstd::ColStream& os) : os(os) {}
};

extern template class Exporter<ExporterTree, int>;
} // namespace org::algo
