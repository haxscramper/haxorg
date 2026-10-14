#include <cmath>
#include <memory>
#include <optional>

#include <hstd_cpp_diagram_lib/kiwi/kiwi_ir.hpp>

// Use the same using-declarations as tests/tKiwiIR.cpp
using namespace hstd;
using namespace hstd::ext;

int main() {
    auto ctx = std::make_shared<KiwiCtx>();

    ctx->use_rect("a", 10, 10, 20, 20);
    ctx->use_rect("b", std::nullopt, 10, 20, 20);
    ctx->use_rect("c", 110, 10, 20, 20);

    Vec<SPtr<ConstraintBase>> constraints = {
        std::make_shared<EvenGapConstraint>(Vec<RectSpec2Side>{
            RectSpec2Side::HorizontalRectBounds("a"),
            RectSpec2Side::HorizontalRectBounds("b"),
            RectSpec2Side::HorizontalRectBounds("c"),
        }),
    };

    Layout layout(ctx, constraints);
    layout.solve();
    auto const& solved = layout.getSolved();

    auto rect_a = solved.at("a")->getGeometry();
    auto rect_b = solved.at("b")->getGeometry();
    auto rect_c = solved.at("c")->getGeometry();

    LOGIC_ASSERTION_CHECK(
        std::abs((rect_b.x() - rect_a.x()) - (rect_c.x() - rect_b.x())) <= 1e-4,
        "Horizontal gaps between rectangles are not even");

    LOGIC_ASSERTION_CHECK(
        std::abs(rect_b.x() - 60.0) <= 1e-4,
        "Middle rectangle is not positioned at x=60");

    return 0;
}
