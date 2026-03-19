#include <haxorg/exporters/ExporterBase.hpp>

using namespace hstd;
using namespace org::algo;

template <typename V, typename R>
void Exporter<V, R>::visit(
    R&                                                res,
    Variant<In<sem::Time>, In<sem::TimeRange>> const& range) {
    std::visit(
        [&, this](auto const& it) {
            _this()->visitField(res, "range", it);
        },
        range);
}

template <typename V, typename R>
template <typename T, typename Kind>
void Exporter<V, R>::visitVariants(R& res, Kind kind, T const& var) {
    std::string fieldName = std::format("{}", kind);
    _this()->visitField(res, "kind", kind);
    std::visit(
        [&, this](auto const& it) {
            _this()->visitField(res, fieldName.c_str(), it);
        },
        var);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, UserTime const& time) {}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::OrgJson const& time) {}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, org::parse::SourceLoc const& time) {}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, float const& time) {}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, org::parse::SourceFileId const& time) {}

#include "Exporter.tcc"
