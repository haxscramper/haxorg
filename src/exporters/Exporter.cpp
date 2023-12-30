#include <exporters/ExporterBase.hpp>

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
void Exporter<V, R>::visit(R& res, CR<UserTime> time) {
    //    visitVariants(res, time.getKind(), time.time);
}

template <typename V, typename R>
void Exporter<V, R>::visit(
    R&                                  res,
    CR<sem::DocumentOptions::TocExport> prop) {
    visitVariants(res, static_cast<int>(prop.index()), prop);
}

#include "Exporter.tcc"
