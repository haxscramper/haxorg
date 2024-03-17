#include <exporters/Exporter.hpp>

struct ExporterUltraplain
    : public Exporter<ExporterUltraplain, std::string> {
#define __ExporterBase Exporter<ExporterUltraplain, std::string>
    EXPORTER_USING()
#undef __ExporterBase

    static std::string toStr(sem::SemId<sem::Org> node);

    void visitLink(std::string& res, In<sem::Link> link);

    template <sem::NotOrg T>
    void visit(std::string& res, CR<T> value) {}

    void visitTimeRange(std::string& res, In<sem::TimeRange> range) {
        visit(res, range->from);
        res += "--";
        visit(res, range->to);
    }

    void visitTime(std::string& res, In<sem::Time> time) {
        if (time->isStatic()) { res += time->getStatic().time.format(); }
    }

    template <typename T>
    void visit(std::string& res, CVec<T> values) {
        for (const auto& value : values) { visit(res, value); }
    }

    template <typename T>
    void visit(std::string& res, CR<Opt<T>> opt) {
        if (opt) { visit(res, *opt); }
    }

    template <typename T>
    void visitField(std::string& res, const char* name, CR<T> field) {
        visit(res, field);
    }

#define __visit(__Kind)                                                   \
    void visit##__Kind(std::string& res, In<sem::__Kind> leaf) {          \
        res += leaf->text;                                                \
    }

    __visit(Word);
    __visit(Punctuation);
    __visit(BigIdent);
    __visit(Placeholder);
    __visit(RawText);
    __visit(Newline);

    void visitSpace(std::string& res, In<sem::Space> leaf) { res += " "; }


#undef __visit
};

extern template class Exporter<ExporterUltraplain, std::string>;
