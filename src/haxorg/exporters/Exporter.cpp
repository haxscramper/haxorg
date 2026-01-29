#include <haxorg/exporters/ExporterBase.hpp>

using namespace hstd;
using namespace org::algo;

template <typename V, typename R>
void Exporter<V, R>::visit(
    R&                                             res,
    CR<Variant<In<sem::Time>, In<sem::TimeRange>>> range) {
    std::visit(
        [&, this](const auto& it) {
            _this()->visitField(res, "range", it);
        },
        range);
}

template <typename V, typename R>
template <typename T, typename Kind>
void Exporter<V, R>::visitVariants(R& res, Kind kind, CR<T> var) {
    std::string fieldName = std::format("{}", kind);
    _this()->visitField(res, "kind", kind);
    std::visit(
        [&, this](const auto& it) {
            _this()->visitField(res, fieldName.c_str(), it);
        },
        var);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<UserTime> time) {}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<sem::OrgJson> time) {}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, CR<org::parse::SourceLoc> time) {}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, float const& time) {}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, org::parse::SourceFileId const& time) {}

#include "Exporter.tcc"
