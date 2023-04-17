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

    template <typename T>
    void recVisit(CR<Opt<sem::Wrap<T>>> value) {
        if (value) {
            recVisit(value.value());
        }
    }

    template <typename T>
    void recVisit(CR<Vec<sem::Wrap<T>>> value) {
        for (const auto& it : value) {
            recVisit(it);
        }
    }

    template <typename T>
    void recVisit(CR<sem::Wrap<T>> value) {
        if constexpr (std::is_same_v<T, sem::Subtree>) {
            recVisit(value->title);
            recVisit(value->completion);
            recVisit(value->tags);
            recVisit(value->description);
            recVisit(value->logbook);
            recVisit(value->closed);
            recVisit(value->deadline);
            recVisit(value->scheduled);
        } else if constexpr (std::is_same_v<T, sem::TimeRange>) {
            recVisit(value->from);
            recVisit(value->to);
        }

        for (const auto& sub : value->subnodes) {
            recVisit(sub);
        }
    }


#define __define(Kind)                                                    \
    virtual Wrap<ExporterResult> export##Kind(sem::Wrap<sem::Kind> arg) { \
        recVisit(arg);                                                    \
        return nullptr;                                                   \
    };

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
