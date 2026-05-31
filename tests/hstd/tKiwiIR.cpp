#include <hstd/ext/geometry/kiwi_ir.hpp>
#include <gtest/gtest.h>

#include <filesystem>

namespace hstd::ext::kiwi_ir {

static void assert_close(double a, double b, double eps = 1e-6) {
    EXPECT_NEAR(a, b, eps);
}

static void write_outputs(std::string const& name, Layout& layout) {
    hstd::fs::path out_dir = "/tmp/kiwi-place";
    std::filesystem::create_directories(out_dir);
    layout.to_svg(out_dir / std::format("{}.svg", name), name);
    layout.to_graphviz(out_dir / std::format("{}-graph", name));
}

TEST(KiwiIr, AlignmentAndRelativePositioning) {
    std::vector<Rect> rects = {
        Rect("a", 10, 20, 40, 30),
        Rect("b", std::nullopt, std::nullopt, 40, 30),
        Rect("c", std::nullopt, std::nullopt, 40, 30),
    };
    std::vector<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<AlignConstraint>(
            Anchor::TOP,
            std::vector<AlignItem>{{"a", 0.0}, {"b", 0.0}, {"c", 0.0}}),
        std::make_shared<SeparateConstraint>(
            "b", Anchor::LEFT, "a", Anchor::RIGHT, 15),
        std::make_shared<SeparateConstraint>(
            "c", Anchor::LEFT, "b", Anchor::RIGHT, 15),
    };
    Layout layout(rects, constraints);
    layout.verify_constraints();
    auto solved = layout.solve();
    write_outputs("test_alignment_and_relative_positioning", layout);

    assert_close(solved.at("a").y.value(), solved.at("b").y.value());
    assert_close(solved.at("b").y.value(), solved.at("c").y.value());
    assert_close(
        solved.at("b").x.value(),
        solved.at("a").x.value() + solved.at("a").width.value() + 15);
    assert_close(
        solved.at("c").x.value(),
        solved.at("b").x.value() + solved.at("b").width.value() + 15);
}

TEST(KiwiIr, EvenGapShapePlacement) {
    std::vector<Rect> rects = {
        Rect("a", 10, 10, 20, 20),
        Rect("b", std::nullopt, 10, 20, 20),
        Rect("c", 110, 10, 20, 20),
    };
    std::vector<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<EvenGapConstraint>(
            std::vector<std::string>{"a", "b", "c"},
            Axis::X,
            Anchor::LEFT),
    };
    Layout layout(rects, constraints);
    auto   solved = layout.solve();
    write_outputs("test_even_gap_shape_placement", layout);

    assert_close(solved.at("b").x.value(), 60.0);
}

TEST(KiwiIr, ParentAndChildRelativeConstraints) {
    std::vector<Rect> rects = {
        Rect("child1", 20, 30, 30, 10),
        Rect("child2", 70, 60, 20, 20),
        Rect("parent"),
        Rect("inner"),
    };
    std::vector<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<ParentWrapConstraint>(
            "parent",
            std::vector<std::string>{"child1", "child2"},
            5,
            10,
            15,
            20),
        std::make_shared<ChildRelativeToParentConstraint>(
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
    write_outputs("test_parent_and_child_relative_constraints", layout);

    assert_close(solved.at("parent").x.value(), 15.0);
    assert_close(solved.at("parent").y.value(), 20.0);
    assert_close(solved.at("parent").width.value(), 90.0);
    assert_close(solved.at("parent").height.value(), 80.0);
    assert_close(
        solved.at("inner").width.value(),
        solved.at("parent").width.value() * 0.2);
    assert_close(
        solved.at("inner").height.value(),
        solved.at("parent").height.value() * 0.5);
    assert_close(
        solved.at("inner").x.value(),
        solved.at("parent").x.value()
            + solved.at("parent").width.value() * 0.5 + 20);
    assert_close(
        solved.at("inner").y.value(),
        solved.at("parent").y.value()
            + solved.at("parent").height.value() * 0.5);
}

TEST(KiwiIr, LinearConstraintAndEqualSize) {
    std::vector<Rect> rects = {
        Rect("a", 10, 10, 40, 25),
        Rect("b", std::nullopt, 50, std::nullopt, std::nullopt),
    };
    Rect&                                   a           = rects[0];
    Rect&                                   b           = rects[1];
    std::vector<hstd::SPtr<ConstraintBase>> constraints = {
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

    assert_close(solved.at("b").x.value(), 80.0);
    assert_close(solved.at("b").width.value(), 60.0);
    assert_close(solved.at("b").height.value(), 25.0);
}

TEST(KiwiIr, MultiSeparateSeveralLinesOfEvenlySpacedRectangles) {
    std::vector<Rect> rects = {
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
    std::vector<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<EvenGapConstraint>(
            std::vector<std::string>{"r00", "r01", "r02"},
            Axis::X,
            Anchor::LEFT),
        std::make_shared<AlignConstraint>(
            Anchor::LEFT,
            std::vector<AlignItem>{{"r00"}, {"r10"}, {"r20"}}),
        std::make_shared<AlignConstraint>(
            Anchor::LEFT,
            std::vector<AlignItem>{{"r01"}, {"r11"}, {"r21"}}),
        std::make_shared<AlignConstraint>(
            Anchor::LEFT,
            std::vector<AlignItem>{{"r02"}, {"r12"}, {"r22"}}),
        std::make_shared<MultiSeparateConstraint>(
            std::vector<std::vector<std::string>>{
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

    assert_close(solved.at("r01").x.value(), 40.0);
    assert_close(solved.at("r10").y.value(), 30.0);
    assert_close(solved.at("r20").y.value(), 60.0);
}

TEST(KiwiIr, TwoOrthogonalMultiSeparateGrid) {
    std::vector<std::vector<std::string>> ids = {
        {"g00", "g01", "g02"},
        {"g10", "g11", "g12"},
        {"g20", "g21", "g22"},
    };
    std::vector<Rect> rects = {Rect("g00", 0, 0, 10, 10)};
    for (auto const& row : ids) {
        for (auto const& rid : row) {
            if (rid != "g00") {
                rects.push_back(
                    Rect(rid, std::nullopt, std::nullopt, 10, 10));
            }
        }
    }

    std::vector<hstd::SPtr<ConstraintBase>> constraints;
    constraints.push_back(
        std::make_shared<MultiSeparateConstraint>(ids, Anchor::TOP, 25));
    std::vector<std::vector<std::string>> col_groups = {
        {ids[0][0], ids[1][0], ids[2][0]},
        {ids[0][1], ids[1][1], ids[2][1]},
        {ids[0][2], ids[1][2], ids[2][2]},
    };
    constraints.push_back(
        std::make_shared<MultiSeparateConstraint>(
            col_groups, Anchor::LEFT, 35));
    for (auto const& row : ids) {
        std::vector<AlignItem> row_items;
        for (auto const& r : row) {
            row_items.push_back(AlignItem{r, 0.0});
        }
        constraints.push_back(
            std::make_shared<AlignConstraint>(Anchor::TOP, row_items));
    }
    for (auto const& col : col_groups) {
        std::vector<AlignItem> col_items;
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

    assert_close(solved.at("g12").x.value(), 70.0);
    assert_close(solved.at("g12").y.value(), 25.0);
    assert_close(solved.at("g21").x.value(), 35.0);
    assert_close(solved.at("g21").y.value(), 50.0);
}

TEST(KiwiIr, EvenGapParentRectanglesAndChildrenRelative) {
    std::vector<Rect> rects = {
        Rect("p1", 0, 0, 100, 60),
        Rect("p2", std::nullopt, 0, 100, 60),
        Rect("p3", 300, 0, 100, 60),
        Rect("c1"),
        Rect("c2"),
        Rect("c3"),
    };
    std::vector<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<EvenGapConstraint>(
            std::vector<std::string>{"p1", "p2", "p3"},
            Axis::X,
            Anchor::LEFT),
        std::make_shared<ChildRelativeToParentConstraint>(
            "c1",
            "p1",
            0.2,
            0.5,
            Anchor::HCENTER,
            Anchor::VCENTER,
            10,
            0,
            Anchor::LEFT,
            Anchor::TOP),
        std::make_shared<ChildRelativeToParentConstraint>(
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
        std::make_shared<ChildRelativeToParentConstraint>(
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
        "test_even_gap_parent_rectangles_and_children_relative", layout);

    assert_close(solved.at("p2").x.value(), 150.0);
    assert_close(solved.at("c2").width.value(), 20.0);
    assert_close(solved.at("c2").height.value(), 30.0);
    assert_close(
        solved.at("c2").x.value(), solved.at("p2").x.value() + 50 + 10);
    assert_close(
        solved.at("c2").y.value(), solved.at("p2").y.value() + 30);
}

TEST(KiwiIr, ConstraintVerificationPassesForConsistentConstraints) {
    std::vector<Rect> rects = {
        Rect("a", 0, 0, 10, 10),
        Rect("b", std::nullopt, 0, 10, 10),
    };
    std::vector<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<SeparateConstraint>(
            "b", Anchor::LEFT, "a", Anchor::RIGHT, 5),
    };
    Layout layout(rects, constraints);
    EXPECT_NO_THROW(layout.verify_constraints());
}

TEST(KiwiIr, ConstraintVerificationPassesForNonrequiredConflict) {
    std::vector<Rect>                       rects       = {Rect("a")};
    Rect&                                   a           = rects[0];
    std::vector<hstd::SPtr<ConstraintBase>> constraints = {
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
    std::vector<Rect> rects = {
        Rect("a", 0, std::nullopt, std::nullopt, std::nullopt)};
    Rect&                                   a           = rects[0];
    std::vector<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<LinearConstraint>(
            a.expr(RectAttr::X), Relation::EQ, Expr(10)),
    };
    Layout layout(rects, constraints);

    try {
        layout.verify_constraints();
        FAIL() << "Expected ConstraintVerificationError";
    } catch (ConstraintVerificationError const& exc) {
        std::string message = exc.what();
        EXPECT_NE(message.find("Rect(a).x == 0"), std::string::npos);
        EXPECT_NE(message.find("LinearConstraint"), std::string::npos);
    }
}

TEST(KiwiIr, ConstraintVerificationFailsForMutuallyExclusiveConstraints) {
    std::vector<Rect>                       rects = {Rect("a"), Rect("b")};
    std::vector<hstd::SPtr<ConstraintBase>> constraints = {
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
        std::string message = exc.what();
        EXPECT_NE(message.find("SeparateConstraint"), std::string::npos);
        EXPECT_NE(message.find("+ 5"), std::string::npos);
        EXPECT_NE(message.find("+ 7"), std::string::npos);
    }
}

} // namespace hstd::ext::kiwi_ir
