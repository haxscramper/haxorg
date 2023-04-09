#include <sem/SemOrg.hpp>

struct Exporter {
    template <typename T>
    using Wrap = std::shared_ptr<T>;

    struct ExporterResult
        : public std::enable_shared_from_this<ExporterResult> {
        template <typename T>
        Wrap<T> as() {
            Wrap<T> result = std::static_pointer_cast<T>(
                shared_from_this());
            Q_CHECK_PTR(result);

            return result;
        }
    };


#define __define(Kind)                                                    \
    virtual Wrap<ExporterResult> export##Kind(sem::Wrap<sem::Kind>) = 0;

    EACH_SEM_ORG_KIND(__define);

#undef __define

    inline virtual Wrap<ExporterResult> exportNode(
        sem::Wrap<sem::Org> node) {
        Wrap<ExporterResult> result;

#define __case(Kind)                                                      \
    case OrgSemKind::Kind:                                                \
        result = export##Kind(node->as<sem::Kind>());                     \
        break;


        switch (node->getKind()) { EACH_SEM_ORG_KIND(__case); }

#undef __case

        return result;
    }
};
