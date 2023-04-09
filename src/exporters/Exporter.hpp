#include <sem/SemOrg.hpp>

struct Exporter {
    using Wrap = std::shared_ptr<T>;

    struct ExporterResult {};


#define __define(Kind)
    virtual Wrap<ExporterResult> export##Kind(sem::Wrap<Kind>) = 0;

    EACH_SEM_ORG_KIND(__define);

#undef __define

    inline virtual Wrap<ExporterResult> exportNode(sem::Wrap<Org> node) {
        Wrap<ExporterResult> result;
#define __case(Kind)                                                      \
    case OrgSemKind::Kind: result = export##Kind(node.as<Kind>()); break;

        switch (node->getKind()) { EACH_SEM_ORG_KIND(__case); }

#undef __case

        return result;
    }
};
