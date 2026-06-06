#include <hstd/ext/geometry/kiwi_ir.hpp>
#include <gtest/gtest.h>
#include "../common.hpp"
#include <hstd/ext/geometry/hstd_geometry_test.hpp>

namespace hstd::ext::kiwi_ir {

static void write_outputs(Layout& layout, Opt<Str> name_r = std::nullopt) {
    auto name = name_r.value_or(
        std::string{getDebugFile().filename().c_str()});
    writeFile(
        getDebugFile(std::format("{}.svg", name)),
        layout.to_svg(name).to_string(2));
    layout.to_graphviz(getDebugFile(std::format("{}-graph", name)));
}

TEST(KiwiIr, AlignAndSeparate) {
    Vec<Rect> rects = {
        Rect("a", 10, 20, 40, 30),
        Rect("b", std::nullopt, std::nullopt, 40, 30),
        Rect("c", std::nullopt, std::nullopt, 40, 30),
    };
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<AlignConstraint>(Vec<AlignItem>{
            {"a", AlignSpec{.anchor = Anchor::TOP}},
            {"b", AlignSpec{.anchor = Anchor::TOP}},
            {"c", AlignSpec{.anchor = Anchor::TOP}}}),
        std::make_shared<SeparateConstraint>(
            "b", Anchor::LEFT, "a", Anchor::RIGHT, 15),
        std::make_shared<SeparateConstraint>(
            "c", Anchor::LEFT, "b", Anchor::RIGHT, 15),
    };
    Layout layout(rects, constraints);
    layout.verify_constraints();
    auto solved = layout.solve();
    write_outputs(layout);

    auto rect_a = solved.at("a").getGeometry();
    auto rect_b = solved.at("b").getGeometry();
    auto rect_c = solved.at("c").getGeometry();

    EXPECT_NEAR(rect_a.y(), rect_b.y(), 1e-6);
    EXPECT_NEAR(rect_b.y(), rect_c.y(), 1e-6);
    EXPECT_NEAR(rect_b.x(), rect_a.x() + rect_a.width() + 15, 1e-6);
    EXPECT_NEAR(rect_c.x(), rect_b.x() + rect_b.width() + 15, 1e-6);
    EXPECT_OUTCOME_OK(checkAlignedHorizontally(rect_a, rect_b));
    EXPECT_OUTCOME_OK(checkAlignedHorizontally(rect_b, rect_c));
}

TEST(KiwiIr, EvenGapX) {
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
    write_outputs(layout);

    auto rect_a = solved.at("a").getGeometry();
    auto rect_b = solved.at("b").getGeometry();
    auto rect_c = solved.at("c").getGeometry();
    EXPECT_NEAR(rect_b.x() - rect_a.x(), rect_c.x() - rect_b.x(), 1e-6);
    EXPECT_NEAR(rect_b.x(), 60.0, 1e-6);
}

TEST(KiwiIr, ParentWrapAndRelative) {
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
            geometry::Padding(
                /*top=*/10,
                /*bottom=*/20,
                /*left=*/5,
                /*right=*/15)),
        std::make_shared<RelativeConstraint>(
            /*nested_rect_id=*/"inner",
            /*parent_rect_id=*/"parent",
            /*x_dim=*/
            RelDimensionSpec{.size_factor = 0.2, .absolute_offset = 20},
            /*y_dim=*/
            RelDimensionSpec{.size_factor = 0.5},
            /*anchor_relative=*/AnchorSpec::UpperLeft(),
            /*anchor_fixed=*/AnchorSpec::CenterCenter()),
    };
    Layout layout(rects, constraints);
    layout.verify_constraints();
    auto solved = layout.solve();
    write_outputs(layout);

    auto rect_parent = solved.at("parent").getGeometry();
    auto rect_inner  = solved.at("inner").getGeometry();

    EXPECT_NEAR(rect_parent.x(), 15.0, 1e-6);
    EXPECT_NEAR(rect_parent.y(), 20.0, 1e-6);
    EXPECT_NEAR(rect_parent.width(), 90.0, 1e-6);
    EXPECT_NEAR(rect_parent.height(), 80.0, 1e-6);
    EXPECT_NEAR(rect_inner.width(), rect_parent.width() * 0.2, 1e-6);
    EXPECT_NEAR(rect_inner.height(), rect_parent.height() * 0.5, 1e-6);
    EXPECT_NEAR(
        rect_inner.x(),
        rect_parent.x() + rect_parent.width() * 0.5 + 20,
        1e-6);
    EXPECT_NEAR(
        rect_inner.y(),
        rect_parent.y() + rect_parent.height() * 0.5,
        1e-6);
    EXPECT_OUTCOME_OK(checkFullyCovers(rect_parent, rect_inner));
}

TEST(KiwiIr, LinearAndEqualSize) {
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
    write_outputs(layout);

    auto rect_a = solved.at("a").getGeometry();
    auto rect_b = solved.at("b").getGeometry();

    EXPECT_NEAR(rect_b.x(), 80.0, 1e-6);
    EXPECT_NEAR(rect_b.width(), 60.0, 1e-6);
    EXPECT_NEAR(rect_b.height(), 25.0, 1e-6);
    EXPECT_OUTCOME_OK(checkSameHeight(rect_a, rect_b));
}

TEST(KiwiIr, MultiSeparateAndEvenGapRows) {
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
    auto                            la = AlignSpec{.anchor = Anchor::LEFT};
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<EvenGapConstraint>(
            Vec<Str>{"r00", "r01", "r02"}, Axis::X, Anchor::LEFT),
        std::make_shared<AlignConstraint>(
            Vec<AlignItem>{{"r00", la}, {"r10", la}, {"r20", la}}),
        std::make_shared<AlignConstraint>(
            Vec<AlignItem>{{"r01", la}, {"r11", la}, {"r21", la}}),
        std::make_shared<AlignConstraint>(
            Vec<AlignItem>{{"r02", la}, {"r12", la}, {"r22", la}}),
        std::make_shared<MultiSeparateConstraint>(
            /*groups=*/
            Vec<Vec<Str>>{
                {"r00", "r01", "r02"},
                {"r10", "r11", "r12"},
                {"r20", "r21", "r22"}},
            /*anchor=*/Anchor::TOP,
            /*step=*/30),
    };
    Layout layout(rects, constraints);
    layout.verify_constraints();
    auto solved = layout.solve();
    write_outputs(layout);

    auto rect_r01 = solved.at("r01").getGeometry();
    auto rect_r10 = solved.at("r10").getGeometry();
    auto rect_r20 = solved.at("r20").getGeometry();
    EXPECT_NEAR(rect_r01.x(), 40.0, 1e-6);
    EXPECT_NEAR(rect_r10.y(), 30.0, 1e-6);
    EXPECT_NEAR(rect_r20.y(), 60.0, 1e-6);

    auto rect_r00 = solved.at("r00").getGeometry();
    auto rect_r02 = solved.at("r02").getGeometry();
    EXPECT_OUTCOME_OK(checkSameHeight(rect_r00, rect_r02));
}

TEST(KiwiIr, MultiSeparateGrid) {
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
            row_items.push_back(
                AlignItem{r, AlignSpec{.anchor = Anchor::TOP}});
        }
        constraints.push_back(
            std::make_shared<AlignConstraint>(row_items));
    }
    for (auto const& col : col_groups) {
        Vec<AlignItem> col_items;
        for (auto const& r : col) {
            col_items.push_back(
                AlignItem{r, AlignSpec{.anchor = Anchor::LEFT}});
        }
        constraints.push_back(
            std::make_shared<AlignConstraint>(col_items));
    }

    Layout layout(rects, constraints);
    layout.verify_constraints();
    auto solved = layout.solve();
    write_outputs(layout);

    auto rect_g12 = solved.at("g12").getGeometry();
    auto rect_g21 = solved.at("g21").getGeometry();

    EXPECT_NEAR(rect_g12.x(), 70.0, 1e-6);
    EXPECT_NEAR(rect_g12.y(), 25.0, 1e-6);
    EXPECT_NEAR(rect_g21.x(), 35.0, 1e-6);
    EXPECT_NEAR(rect_g21.y(), 50.0, 1e-6);
    EXPECT_OUTCOME_OK(checkSameWidth(rect_g12, rect_g21));
    EXPECT_OUTCOME_OK(checkSameHeight(rect_g12, rect_g21));
}

TEST(KiwiIr, EvenGapParentsAndRelative) {
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
        std::make_shared<RelativeConstraint>(
            /*nested_rect_id=*/"c1",
            /*parent_rect_id=*/"p1",
            RelDimensionSpec{.size_factor = 0.2, .absolute_offset = 10},
            RelDimensionSpec{.size_factor = 0.5},
            /*anchor_relative=*/AnchorSpec::UpperLeft(),
            /*anchor_fixed=*/AnchorSpec::CenterCenter()),
        std::make_shared<RelativeConstraint>(
            /*nested_rect_id=*/"c2",
            /*parent_rect_id=*/"p2",
            RelDimensionSpec{.size_factor = 0.2, .absolute_offset = 10},
            RelDimensionSpec{.size_factor = 0.5},
            /*anchor_relative=*/AnchorSpec::UpperLeft(),
            /*anchor_fixed=*/AnchorSpec::CenterCenter()),
        std::make_shared<RelativeConstraint>(
            /*nested_rect_id=*/"c3",
            /*parent_rect_id=*/"p3",
            RelDimensionSpec{.size_factor = 0.2, .absolute_offset = 10},
            RelDimensionSpec{.size_factor = 0.5},
            /*anchor_relative=*/AnchorSpec::UpperLeft(),
            /*anchor_fixed=*/AnchorSpec::CenterCenter()),
    };

    Layout layout(rects, constraints);
    layout.verify_constraints();
    auto solved = layout.solve();
    write_outputs(layout);

    auto rect_p2 = solved.at("p2").getGeometry();
    auto rect_c2 = solved.at("c2").getGeometry();
    EXPECT_NEAR(rect_p2.x(), 150.0, 1e-6);
    EXPECT_NEAR(rect_c2.width(), 20.0, 1e-6);
    EXPECT_NEAR(rect_c2.height(), 30.0, 1e-6);
    EXPECT_NEAR(rect_c2.x(), rect_p2.x() + 50 + 10, 1e-6);
    EXPECT_NEAR(rect_c2.y(), rect_p2.y() + 30, 1e-6);

    EXPECT_OUTCOME_OK(checkFullyCovers(rect_p2, rect_c2));
}

TEST(KiwiIr, VerifyPass) {
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

TEST(KiwiIr, VerifyPassWeakConflict) {
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

TEST(KiwiIr, VerifyFailPinConflict) {
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

TEST(KiwiIr, VerifyFailMutuallyExclusiveSeparate) {
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

// Additional tests

TEST(KiwiIr, EvenGapWithMultiSeparateChangeDistance) {
    Vec<Rect> rects = {
        Rect("a", 0, 0, 10, 10),
        Rect("b", std::nullopt, 0, 10, 10),
        Rect("c", std::nullopt, 0, 10, 10),
        Rect("d", std::nullopt, 0, 10, 10),
        Rect("e", std::nullopt, 0, 10, 10),
        Rect("f", std::nullopt, 0, 10, 10),
    };
    double                          step        = 40.0;
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<EvenGapConstraint>(
            Vec<Str>{"a", "b", "c", "d", "e", "f"}, Axis::X, Anchor::LEFT),
        std::make_shared<MultiSeparateConstraint>(
            /*groups=*/Vec<Vec<Str>>{{"a"}, {"c"}, {"e"}},
            /*anchor=*/Anchor::LEFT,
            /*step=*/step),
    };
    Layout layout(rects, constraints);
    layout.verify_constraints();
    auto solved = layout.solve();
    write_outputs(layout, "run1");

    auto rect_a = solved.at("a").getGeometry();
    auto rect_b = solved.at("b").getGeometry();
    auto rect_c = solved.at("c").getGeometry();
    auto rect_d = solved.at("d").getGeometry();
    auto rect_e = solved.at("e").getGeometry();
    auto rect_f = solved.at("f").getGeometry();

    double expected_gap = step / 2.0; // because even gap forces 2 gaps per
                                      // step
    EXPECT_NEAR(rect_b.x() - rect_a.x(), expected_gap, 1e-6);
    EXPECT_NEAR(rect_c.x() - rect_b.x(), expected_gap, 1e-6);
    EXPECT_NEAR(rect_d.x() - rect_c.x(), expected_gap, 1e-6);
    EXPECT_NEAR(rect_e.x() - rect_d.x(), expected_gap, 1e-6);
    EXPECT_NEAR(rect_f.x() - rect_e.x(), expected_gap, 1e-6);
    EXPECT_NEAR(rect_c.x() - rect_a.x(), step, 1e-6);
    EXPECT_NEAR(rect_e.x() - rect_c.x(), step, 1e-6);

    // Change step and verify new layout
    double new_step = 60.0;
    constraints[1]  = std::make_shared<MultiSeparateConstraint>(
        Vec<Vec<Str>>{{"a"}, {"c"}, {"e"}}, Anchor::LEFT, new_step);
    Layout layout2(rects, constraints);
    layout2.verify_constraints();
    auto solved2 = layout2.solve();
    write_outputs(layout2, "run2");
    auto rect_a2 = solved2.at("a").getGeometry();
    auto rect_b2 = solved2.at("b").getGeometry();
    auto rect_c2 = solved2.at("c").getGeometry();
    auto rect_d2 = solved2.at("d").getGeometry();
    auto rect_e2 = solved2.at("e").getGeometry();
    auto rect_f2 = solved2.at("f").getGeometry();

    double new_gap = new_step / 2.0;
    EXPECT_NEAR(rect_b2.x() - rect_a2.x(), new_gap, 1e-6);
    EXPECT_NEAR(rect_c2.x() - rect_a2.x(), new_step, 1e-6);
    EXPECT_NEAR(rect_e2.x() - rect_c2.x(), new_step, 1e-6);
}

TEST(KiwiIr, ConflictingMultiSeparate) {
    Vec<Rect> rects = {
        Rect("x", 0, 0, 10, 10),
        Rect("y", std::nullopt, 0, 10, 10),
        Rect("z", std::nullopt, 0, 10, 10),
    };
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<MultiSeparateConstraint>(
            /*groups=*/Vec<Vec<Str>>{{"x"}, {"y"}, {"z"}},
            /*anchor=*/Anchor::LEFT,
            /*step=*/20),
        std::make_shared<MultiSeparateConstraint>(
            /*groups=*/Vec<Vec<Str>>{{"x"}, {"y"}},
            /*anchor=*/Anchor::LEFT,
            /*step=*/30),
    };
    Layout layout(rects, constraints);
    try {
        layout.verify_constraints();
        FAIL() << "Expected constraint conflict";
    } catch (ConstraintVerificationError const& e) {
        Str msg = e.what();
        EXPECT_NE(msg.find("MultiSeparateConstraint"), Str::npos);
    }
}

TEST(KiwiIr, PinNodeLocation) {
    Vec<Rect> rects = {Rect("pinned", 42, 10, 30, 20)};
    Layout    layout(rects, {});
    layout.verify_constraints();
    auto solved = layout.solve();
    write_outputs(layout);
    auto rect_p = solved.at("pinned").getGeometry();
    EXPECT_NEAR(rect_p.x(), 42, 1e-6);
    EXPECT_NEAR(rect_p.y(), 10, 1e-6);
    EXPECT_NEAR(rect_p.width(), 30, 1e-6);
    EXPECT_NEAR(rect_p.height(), 20, 1e-6);
}

TEST(KiwiIr, PinAndLeftOf) {
    Vec<Rect> rects = {
        Rect("static", 100, 0, 20, 20),
        Rect("movable", std::nullopt, 0, 15, 15),
    };
    Rect&                           s           = rects[0];
    Rect&                           m           = rects[1];
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<LinearConstraint>(
            m.expr(RectAttr::X) + m.expr(RectAttr::WIDTH),
            Relation::LE,
            s.expr(RectAttr::X)),
    };
    Layout layout(rects, constraints);
    layout.verify_constraints();
    auto solved = layout.solve();
    write_outputs(layout);
    auto rect_s = solved.at("static").getGeometry();
    auto rect_m = solved.at("movable").getGeometry();
    EXPECT_OUTCOME_OK(checkLeftOf(rect_s, rect_m));
    EXPECT_LE(rect_m.x() + rect_m.width(), rect_s.x() + 1e-6);
}

TEST(KiwiIr, LeftOfAndBelow) {
    Vec<Rect> rects = {
        Rect("leftStatic", 0, 0, 20, 20),
        Rect("rightStatic", 100, 0, 20, 20),
        Rect("target", std::nullopt, std::nullopt, 15, 15),
    };
    Rect&                           ls          = rects[0];
    Rect&                           rs          = rects[1];
    Rect&                           t           = rects[2];
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<LinearConstraint>(
            t.expr(RectAttr::X) + t.expr(RectAttr::WIDTH),
            Relation::LE,
            rs.expr(RectAttr::X)),
        std::make_shared<LinearConstraint>(
            t.expr(RectAttr::Y),
            Relation::GE,
            ls.expr(RectAttr::Y) + ls.expr(RectAttr::HEIGHT)),
    };
    Layout layout(rects, constraints);
    layout.verify_constraints();
    auto solved = layout.solve();
    write_outputs(layout);
    auto rect_ls = solved.at("leftStatic").getGeometry();
    auto rect_rs = solved.at("rightStatic").getGeometry();
    auto rect_t  = solved.at("target").getGeometry();
    EXPECT_OUTCOME_OK(checkLeftOf(rect_rs, rect_t));
    EXPECT_OUTCOME_OK(checkBelow(rect_ls, rect_t));
}

TEST(KiwiIr, BoundedAllSides) {
    Vec<Rect> rects = {
        Rect("leftWall", 0, 0, 10, 100),
        Rect("rightWall", 200, 0, 10, 100),
        Rect("topWall", 0, 0, 210, 10),
        Rect("bottomWall", 0, 150, 210, 10),
        Rect("center", std::nullopt, std::nullopt, 30, 30),
    };
    Rect&                           lw          = rects[0];
    Rect&                           rw          = rects[1];
    Rect&                           tw          = rects[2];
    Rect&                           bw          = rects[3];
    Rect&                           c           = rects[4];
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<LinearConstraint>(
            c.expr(RectAttr::X),
            Relation::GE,
            lw.expr(RectAttr::X) + lw.expr(RectAttr::WIDTH)),
        std::make_shared<LinearConstraint>(
            c.expr(RectAttr::X) + c.expr(RectAttr::WIDTH),
            Relation::LE,
            rw.expr(RectAttr::X)),
        std::make_shared<LinearConstraint>(
            c.expr(RectAttr::Y),
            Relation::GE,
            tw.expr(RectAttr::Y) + tw.expr(RectAttr::HEIGHT)),
        std::make_shared<LinearConstraint>(
            c.expr(RectAttr::Y) + c.expr(RectAttr::HEIGHT),
            Relation::LE,
            bw.expr(RectAttr::Y)),
    };
    Layout layout(rects, constraints);
    layout.verify_constraints();
    auto solved = layout.solve();
    write_outputs(layout);
    auto rect_c  = solved.at("center").getGeometry();
    auto rect_lw = solved.at("leftWall").getGeometry();
    auto rect_rw = solved.at("rightWall").getGeometry();
    auto rect_tw = solved.at("topWall").getGeometry();
    auto rect_bw = solved.at("bottomWall").getGeometry();
    EXPECT_OUTCOME_OK(checkRightOf(rect_lw, rect_c));
    EXPECT_OUTCOME_OK(checkLeftOf(rect_rw, rect_c));
    EXPECT_OUTCOME_OK(checkBelow(rect_tw, rect_c));
    EXPECT_OUTCOME_OK(checkAbove(rect_bw, rect_c));
}

TEST(KiwiIr, RelativeOutsideParent) {
    Vec<Rect> rects = {
        Rect("parent", 50, 50, 100, 100),
        Rect("child"),
    };
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<RelativeConstraint>(
            /*nested_rect_id=*/"child",
            /*parent_rect_id=*/"parent",
            RelDimensionSpec{.absolute_offset = -20},
            RelDimensionSpec{.absolute_offset = -30}),
    };
    Layout layout(rects, constraints);
    layout.verify_constraints();
    auto solved = layout.solve();
    write_outputs(layout);
    auto rect_parent = solved.at("parent").getGeometry();
    auto rect_child  = solved.at("child").getGeometry();
    EXPECT_NEAR(rect_child.x(), rect_parent.x() - 20, 1e-6);
    EXPECT_NEAR(rect_child.y(), rect_parent.y() - 30, 1e-6);
    EXPECT_TRUE(rect_child.x() < rect_parent.x());
    EXPECT_TRUE(rect_child.y() < rect_parent.y());
}

TEST(KiwiIr, RelativeVariations) {
    Vec<Rect> rects = {
        Rect("p", 0, 0, 100, 80),
        Rect("c"),
    };
    // width factor 0.5, height factor 0.6, right-bottom anchors on both
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<RelativeConstraint>(
            /*nested_rect_id=*/"c",
            /*parent_rect_id=*/"p",
            RelDimensionSpec{.size_factor = 0.5},
            RelDimensionSpec{.size_factor = 0.6},
            /*anchor_relative=*/AnchorSpec::LowerRight(),
            /*anchor_fixed=*/AnchorSpec::LowerRight()),
    };
    Layout layout(rects, constraints);
    layout.verify_constraints();
    auto solved = layout.solve();
    write_outputs(layout);
    auto rect_p = solved.at("p").getGeometry();
    auto rect_c = solved.at("c").getGeometry();
    EXPECT_NEAR(rect_c.width(), rect_p.width() * 0.5, 1e-6);
    EXPECT_NEAR(rect_c.height(), rect_p.height() * 0.6, 1e-6);
    EXPECT_NEAR(
        rect_c.x() + rect_c.width(), rect_p.x() + rect_p.width(), 1e-6);
    EXPECT_NEAR(
        rect_c.y() + rect_c.height(), rect_p.y() + rect_p.height(), 1e-6);
}

TEST(KiwiIr, EqualSizeWithParentWrap) {
    Vec<Rect> rects = {
        Rect("parent"),
        Rect("nested"),
        Rect("other", std::nullopt, 0, 10, 10),
    };
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<ParentWrapConstraint>(
            /*parent_rect_id=*/"parent",
            /*nested_rect_ids=*/Vec<Str>{"nested"}),
        std::make_shared<EqualSizeConstraint>(
            "nested",
            "other",
            /*match_width=*/true,
            /*match_height=*/true),
    };
    Layout layout(rects, constraints);
    layout.verify_constraints();
    auto solved = layout.solve();
    write_outputs(layout);
    auto rect_parent = solved.at("parent").getGeometry();
    auto rect_nested = solved.at("nested").getGeometry();
    auto rect_other  = solved.at("other").getGeometry();
    EXPECT_OUTCOME_OK(checkSameSize(rect_nested, rect_other));
    EXPECT_OUTCOME_OK(checkSameSize(rect_parent, rect_nested));
}

} // namespace hstd::ext::kiwi_ir
