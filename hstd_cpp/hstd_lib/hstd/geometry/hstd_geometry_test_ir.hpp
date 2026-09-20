#pragma once

#if ORG_BUILD_WITH_PROTOBUF

#    include <boost/outcome/result.hpp>
#    include <hstd/geometry/hstd_geometry_test.hpp>
#    include <hstd/stdlib/containers/Vec.hpp>
#    include <src/hstd/ext/geometry/hstd_geometry_test_ir.pb.h>

#    include <cstddef>
#    include <string>
#    include <variant>

namespace hstd::ext::geometry {

using GeometryElementShape = std::variant<Rect, Point, Path>;

struct GeometryElement {
    std::string          id;
    GeometryElementShape shape;
    DESC_FIELDS(GeometryElement, (id, shape));
};

using GeometryElementList       = hstd::Vec<GeometryElement>;
using GeometryElementListResult = hstd::Result<GeometryElementList, GeometryError>;

struct GeometryValidationError {
    std::size_t          checkIndex;
    std::string          checkId;
    proto::GeometryCheck check;
    GeometryCheckResult  result;
    DESC_FIELDS(GeometryValidationError, (checkIndex, checkId, check, result));
};

using GeometryValidationErrors = hstd::Vec<GeometryValidationError>;

GeometryElementListResult geometryElements(proto::GeometryValidationSpec const& spec);

GeometryValidationErrors validateGeometry(
    GeometryElementListResult const& elements,
    ::google::protobuf::RepeatedPtrField<
        ::hstd::ext::geometry::proto::GeometryCheck> const& checks);

GeometryValidationErrors validateGeometry(proto::GeometryValidationSpec const& spec);

} // namespace hstd::ext::geometry

#endif
