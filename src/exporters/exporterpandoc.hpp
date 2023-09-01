#pragma once

#include <exporters/Exporter.hpp>
#include <hstd/stdlib/Json.hpp>

struct PandocRes {
    Vec<json> unpacked;
    json      toJson() const {
        json res = json::array();
        for (auto const& it : unpacked) {
            res.push_back(it);
        }
        return res;
    }
    PandocRes() {}
    PandocRes(CVec<json> values) : unpacked(values) {}
    PandocRes(json value) : unpacked({value}) {}
};

struct ExporterPandoc : public Exporter<ExporterPandoc, PandocRes> {
    using Base = Exporter<ExporterPandoc, PandocRes>;
#define __ExporterBase Base
    EXPORTER_USING()
#undef __ExporterBase

    template <typename T>
    PandocRes newRes(CVec<T>) {
        return json::array();
    }

    template <typename T>
    PandocRes newRes(CR<T>) {
        return json::object();
    }

    template <typename T>
    void visitField(PandocRes& res, const char* name, CR<T> field) {
        res = json("FIELD" + QString(name));
    }

    template <typename T>
    PandocRes visit(CR<T> arg) {
        PandocRes res = newRes(arg);
        visit(res, arg);
        return res;
    }

    PandocRes newRes(sem::SemId org);

    template <typename T>
    PandocRes newRes(sem::SemIdT<T> org) {
        return newRes(org.toId());
    }

    json content(sem::SemId id, SemSet const& skip = SemSet{});

#define __case(__Kind)                                                    \
    void visit##__Kind(PandocRes& res, In<sem::__Kind> doc);

    EACH_SEM_ORG_KIND(__case)

#undef __case
};
