#include <hstd/ext/geometry/kiwi_ir.hpp>
#include <gtest/gtest.h>
#include "../common.hpp"
#include <hstd/ext/geometry/hstd_geometry_test.hpp>

namespace hstd::ext::kiwi_ir {

static void write_outputs(Str const& name, Layout& layout) {
    layout.to_svg(getDebugFile(std::format("{}.svg", name)), name);
    layout.to_graphviz(getDebugFile(std::format("{}-graph", name)));
}

TEST(KiwiIr, AlignmentAndRelativePositioning) {
    Vec<Rect> rects = {
        Rect("a", 10, 20, 40, 30),
        Rect("b", std::nullopt, std::nullopt, 40, 30),
        Rect("c", std::nullopt, std::nullopt, 40, 30),
    };
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<AlignConstraint>(
            Anchor::TOP,
            Vec<AlignItem>{{"a", 0.0}, {"b", 0.0}, {"c", 0.0}}),
        std::make_shared<SeparateConstraint>(
            "b", Anchor::LEFT, "a", Anchor::RIGHT, 15),
        std::make_shared<SeparateConstraint>(
            "c", Anchor::LEFT, "b", Anchor::RIGHT, 15),
    };
    Layout layout(rects, constraints);
    layout.verify_constraints();
    auto solved = layout.solve();
    write_outputs("test_alignment_and_relative_positioning", layout);

    auto rect_a = solved.at("a").getGeometry();
    auto rect_b = solved.at("b").getGeometry();
    auto rect_c = solved.at("c").getGeometry();

    EXPECT_NEAR(rect_a.y(), rect_b.y(), 1e-6);
    EXPECT_NEAR(rect_b.y(), rect_c.y(), 1e-6);
    EXPECT_NEAR(rect_b.x(), rect_a.x() + rect_a.width() + 15, 1e-6);
    EXPECT_NEAR(rect_c.x(), rect_b.x() + rect_b.width() + 15, 1e-6);
}

TEST(KiwiIr, EvenGapShapePlacement) {
    Vec<Rect> rects = {
        Rect("a", 10, 10, 20, 20),
        Rect("b", std::nullopt, 10, 20, 20),
        Rect("c", 110, 10, 20, 20),
    };
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<EvenGapConstraint>(
            Vec<Str>{"a", "b", "c"}, Axis::X, Anchor::LEFT),
    };
    Layout layout(rects, constraints);
    auto   solved = layout.solve();
    write_outputs("test_even_gap_shape_placement", layout);

    auto rect_b = solved.at("b").getGeometry();
    EXPECT_NEAR(rect_b.x(), 60.0, 1e-6);
}

TEST(KiwiIr, ParentAndNestedRelativeConstraints) {
    Vec<Rect> rects = {
        Rect("nested1", 20, 30, 30, 10),
        Rect("nested2", 70, 60, 20, 20),
        Rect("parent"),
        Rect("inner"),
    };
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<ParentWrapConstraint>(
            /*parent_rect_id=*/"parent",
            /*nested_rect_ids=*/Vec<Str>{"nested1", "nested2"},
            /*padding_left=*/5,
            /*padding_top=*/10,
            /*padding_right=*/15,
            /*padding_bottom=*/20),
        std::make_shared<NestedRelativeToParentConstraint>(
            "inner",
            "parent",
            0.2,
            0.5,
            Anchor::HCENTER,
            Anchor::VCENTER,
            20,
            0,
            Anchor::LEFT,
            Anchor::TOP),
    };
    Layout layout(rects, constraints);
    layout.verify_constraints();
    auto solved = layout.solve();
    write_outputs("test_parent_and_nested_relative_constraints", layout);

    auto parent_rect = solved.at("parent").getGeometry();
    auto inner_rect  = solved.at("inner").getGeometry();

    EXPECT_NEAR(parent_rect.x(), 15.0, 1e-6);
    EXPECT_NEAR(parent_rect.y(), 20.0, 1e-6);
    EXPECT_NEAR(parent_rect.width(), 90.0, 1e-6);
    EXPECT_NEAR(parent_rect.height(), 80.0, 1e-6);
    EXPECT_NEAR(inner_rect.width(), parent_rect.width() * 0.2, 1e-6);
    EXPECT_NEAR(inner_rect.height(), parent_rect.height() * 0.5, 1e-6);
    EXPECT_NEAR(
        inner_rect.x(),
        parent_rect.x() + parent_rect.width() * 0.5 + 20,
        1e-6);
    EXPECT_NEAR(
        inner_rect.y(),
        parent_rect.y() + parent_rect.height() * 0.5,
        1e-6);
}

TEST(KiwiIr, LinearConstraintAndEqualSize) {
    Vec<Rect> rects = {
        Rect("a", 10, 10, 40, 25),
        Rect("b", std::nullopt, 50, std::nullopt, std::nullopt),
    };
    Rect&                           a           = rects[0];
    Rect&                           b           = rects[1];
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<EqualSizeConstraint>("a", "b", false, true),
        std::make_shared<LinearConstraint>(
            b.expr(RectAttr::X),
            Relation::EQ,
            a.expr(RectAttr::RIGHT) + 30),
        std::make_shared<LinearConstraint>(
            b.expr(RectAttr::WIDTH),
            Relation::EQ,
            a.expr(RectAttr::WIDTH) + 20),
    };
    Layout layout(rects, constraints);
    layout.verify_constraints();
    auto solved = layout.solve();
    write_outputs("test_linear_constraint_and_equal_size", layout);

    auto rect_b = solved.at("b").getGeometry();

    EXPECT_NEAR(rect_b.x(), 80.0, 1e-6);
    EXPECT_NEAR(rect_b.width(), 60.0, 1e-6);
    EXPECT_NEAR(rect_b.height(), 25.0, 1e-6);
}

TEST(KiwiIr, MultiSeparateSeveralLinesOfEvenlySpacedRectangles) {
    Vec<Rect> rects = {
        Rect("r00", 0, 0, 20, 10),
        Rect("r01", std::nullopt, 0, 20, 10),
        Rect("r02", 80, 0, 20, 10),
        Rect("r10", std::nullopt, 30, 20, 10),
        Rect("r11", std::nullopt, 30, 20, 10),
        Rect("r12", std::nullopt, 30, 20, 10),
        Rect("r20", std::nullopt, 60, 20, 10),
        Rect("r21", std::nullopt, 60, 20, 10),
        Rect("r22", std::nullopt, 60, 20, 10),
    };
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<EvenGapConstraint>(
            Vec<Str>{"r00", "r01", "r02"}, Axis::X, Anchor::LEFT),
        std::make_shared<AlignConstraint>(
            Anchor::LEFT, Vec<AlignItem>{{"r00"}, {"r10"}, {"r20"}}),
        std::make_shared<AlignConstraint>(
            Anchor::LEFT, Vec<AlignItem>{{"r01"}, {"r11"}, {"r21"}}),
        std::make_shared<AlignConstraint>(
            Anchor::LEFT, Vec<AlignItem>{{"r02"}, {"r12"}, {"r22"}}),
        std::make_shared<MultiSeparateConstraint>(
            Vec<Vec<Str>>{
                {"r00", "r01", "r02"},
                {"r10", "r11", "r12"},
                {"r20", "r21", "r22"}},
            Anchor::TOP,
            30),
    };
    Layout layout(rects, constraints);
    layout.verify_constraints();
    auto solved = layout.solve();
    write_outputs(
        "test_multi_separate_several_lines_of_evenly_spaced_rectangles",
        layout);

    auto rect_r01 = solved.at("r01").getGeometry();
    auto rect_r10 = solved.at("r10").getGeometry();
    auto rect_r20 = solved.at("r20").getGeometry();
    EXPECT_NEAR(rect_r01.x(), 40.0, 1e-6);
    EXPECT_NEAR(rect_r10.y(), 30.0, 1e-6);
    EXPECT_NEAR(rect_r20.y(), 60.0, 1e-6);
}

TEST(KiwiIr, TwoOrthogonalMultiSeparateGrid) {
    Vec<Vec<Str>> ids = {
        {"g00", "g01", "g02"},
        {"g10", "g11", "g12"},
        {"g20", "g21", "g22"},
    };
    Vec<Rect> rects = {Rect("g00", 0, 0, 10, 10)};
    for (auto const& row : ids) {
        for (auto const& rid : row) {
            if (rid != "g00") {
                rects.push_back(
                    Rect(rid, std::nullopt, std::nullopt, 10, 10));
            }
        }
    }

    Vec<hstd::SPtr<ConstraintBase>> constraints;
    constraints.push_back(
        std::make_shared<MultiSeparateConstraint>(ids, Anchor::TOP, 25));
    Vec<Vec<Str>> col_groups = {
        {ids[0][0], ids[1][0], ids[2][0]},
        {ids[0][1], ids[1][1], ids[2][1]},
        {ids[0][2], ids[1][2], ids[2][2]},
    };
    constraints.push_back(
        std::make_shared<MultiSeparateConstraint>(
            col_groups, Anchor::LEFT, 35));
    for (auto const& row : ids) {
        Vec<AlignItem> row_items;
        for (auto const& r : row) {
            row_items.push_back(AlignItem{r, 0.0});
        }
        constraints.push_back(
            std::make_shared<AlignConstraint>(Anchor::TOP, row_items));
    }
    for (auto const& col : col_groups) {
        Vec<AlignItem> col_items;
        for (auto const& r : col) {
            col_items.push_back(AlignItem{r, 0.0});
        }
        constraints.push_back(
            std::make_shared<AlignConstraint>(Anchor::LEFT, col_items));
    }

    Layout layout(rects, constraints);
    layout.verify_constraints();
    auto solved = layout.solve();
    write_outputs("test_two_orthogonal_multi_separate_grid", layout);

    auto rect_g12 = solved.at("g12").getGeometry();
    auto rect_g21 = solved.at("g21").getGeometry();

    EXPECT_NEAR(rect_g12.x(), 70.0, 1e-6);
    EXPECT_NEAR(rect_g12.y(), 25.0, 1e-6);
    EXPECT_NEAR(rect_g21.x(), 35.0, 1e-6);
    EXPECT_NEAR(rect_g21.y(), 50.0, 1e-6);
}

TEST(KiwiIr, EvenGapParentRectanglesAndNestedRelative) {
    Vec<Rect> rects = {
        Rect("p1", 0, 0, 100, 60),
        Rect("p2", std::nullopt, 0, 100, 60),
        Rect("p3", 300, 0, 100, 60),
        Rect("c1"),
        Rect("c2"),
        Rect("c3"),
    };
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<EvenGapConstraint>(
            Vec<Str>{"p1", "p2", "p3"}, Axis::X, Anchor::LEFT),
        std::make_shared<NestedRelativeToParentConstraint>(
            /*nested_rect_id=*/"c1",
            /*parent_rect_id=*/"p1",
            /*width_factor=*/0.2,
            /*height_factor=*/0.5,
            /*x_anchor=*/Anchor::HCENTER,
            /*y_anchor=*/Anchor::VCENTER,
            /*x_offset=*/10,
            /*y_offset=*/0,
            /*nested_x_anchor=*/Anchor::LEFT,
            /*nested_y_anchor=*/Anchor::TOP),
        std::make_shared<NestedRelativeToParentConstraint>(
            "c2",
            "p2",
            0.2,
            0.5,
            Anchor::HCENTER,
            Anchor::VCENTER,
            10,
            0,
            Anchor::LEFT,
            Anchor::TOP),
        std::make_shared<NestedRelativeToParentConstraint>(
            "c3",
            "p3",
            0.2,
            0.5,
            Anchor::HCENTER,
            Anchor::VCENTER,
            10,
            0,
            Anchor::LEFT,
            Anchor::TOP),
    };

    Layout layout(rects, constraints);
    layout.verify_constraints();
    auto solved = layout.solve();
    write_outputs(
        "test_even_gap_parent_rectangles_and_nested_relative", layout);

    auto rect_p2 = solved.at("p2").getGeometry();
    auto rect_c2 = solved.at("c2").getGeometry();
    EXPECT_NEAR(rect_p2.x(), 150.0, 1e-6);
    EXPECT_NEAR(rect_c2.width(), 20.0, 1e-6);
    EXPECT_NEAR(rect_c2.height(), 30.0, 1e-6);
    EXPECT_NEAR(rect_c2.x(), rect_p2.x() + 50 + 10, 1e-6);
    EXPECT_NEAR(rect_c2.y(), rect_p2.y() + 30, 1e-6);

    EXPECT_OUTCOME_OK(geometry::checkFullyCovers(rect_p2, rect_c2));
}

TEST(KiwiIr, ConstraintVerificationPassesForConsistentConstraints) {
    Vec<Rect> rects = {
        Rect("a", 0, 0, 10, 10),
        Rect("b", std::nullopt, 0, 10, 10),
    };
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<SeparateConstraint>(
            "b", Anchor::LEFT, "a", Anchor::RIGHT, 5),
    };
    Layout layout(rects, constraints);
    EXPECT_NO_THROW(layout.verify_constraints());
}

TEST(KiwiIr, ConstraintVerificationPassesForNonrequiredConflict) {
    Vec<Rect>                       rects       = {Rect("a")};
    Rect&                           a           = rects[0];
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<LinearConstraint>(
            a.expr(RectAttr::X), Relation::EQ, Expr(0), Strength::WEAK),
        std::make_shared<LinearConstraint>(
            a.expr(RectAttr::X), Relation::EQ, Expr(100), Strength::WEAK),
    };
    Layout layout(rects, constraints);
    EXPECT_NO_THROW(layout.verify_constraints());
}

TEST(
    KiwiIr,
    ConstraintVerificationFailsForConflictingRectPinAndLinearConstraint) {
    Vec<Rect> rects = {
        Rect("a", 0, std::nullopt, std::nullopt, std::nullopt)};
    Rect&                           a           = rects[0];
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<LinearConstraint>(
            a.expr(RectAttr::X), Relation::EQ, Expr(10)),
    };
    Layout layout(rects, constraints);

    try {
        layout.verify_constraints();
        FAIL() << "Expected ConstraintVerificationError";
    } catch (ConstraintVerificationError const& exc) {
        Str message = exc.what();
        EXPECT_NE(message.find("Rect(a).x == 0"), Str::npos);
        EXPECT_NE(message.find("LinearConstraint"), Str::npos);
    }
}

TEST(KiwiIr, ConstraintVerificationFailsForMutuallyExclusiveConstraints) {
    Vec<Rect>                       rects       = {Rect("a"), Rect("b")};
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<SeparateConstraint>(
            "b", Anchor::LEFT, "a", Anchor::RIGHT, 5),
        std::make_shared<SeparateConstraint>(
            "b", Anchor::LEFT, "a", Anchor::RIGHT, 7),
    };
    Layout layout(rects, constraints);

    try {
        layout.verify_constraints();
        FAIL() << "Expected ConstraintVerificationError";
    } catch (ConstraintVerificationError const& exc) {
        Str message = exc.what();
        EXPECT_NE(message.find("SeparateConstraint"), Str::npos);
        EXPECT_NE(message.find("+ 5"), Str::npos);
        EXPECT_NE(message.find("+ 7"), Str::npos);
    }
}

} // namespace hstd::ext::kiwi_ir
