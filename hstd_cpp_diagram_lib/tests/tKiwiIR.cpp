#include <gtest/gtest.h>
#include <hstd_cpp_lib/ext/geometry/kiwi_ir.hpp>
#include <hstd_cpp_lib/extra/error_format/gtest_utils.hpp>
#include <hstd_cpp_lib/geometry/hstd_geometry_test.hpp>

namespace hstd::ext::kiwi_ir {

static void write_outputs(Layout& layout, Opt<Str> name_r = std::nullopt) {
    auto name = name_r.value_or(std::string{getDebugFile().filename().c_str()});
    writeFile(
        getDebugFile(fmt::format("{}.svg", name)), layout.to_svg(name).to_string(2));
    layout.to_graphviz(getDebugFile(fmt::format("{}-graph.png", name)));
}

TEST(KiwiIr, AlignAndSeparate) {
    auto ctx = std::make_shared<KiwiCtx>();
    ctx->use_rect("a", 10, 20, 40, 30);
    ctx->use_rect("b", std::nullopt, std::nullopt, 40, 30);
    ctx->use_rect("c", std::nullopt, std::nullopt, 40, 30);
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<AlignConstraint>(Vec<AlignItem>{
            {"a", AlignSpec{.anchor = Anchor::TOP}},
            {"b", AlignSpec{.anchor = Anchor::TOP}},
            {"c", AlignSpec{.anchor = Anchor::TOP}}}),
        std::make_shared<SeparateConstraint>(
            RectSpec1Side("b", Anchor::LEFT), RectSpec1Side("a", Anchor::RIGHT), 15),
        std::make_shared<SeparateConstraint>(
            RectSpec1Side("c", Anchor::LEFT), RectSpec1Side("b", Anchor::RIGHT), 15),
    };
    Layout layout(ctx, constraints);
    layout.verify_constraints();
    layout.solve();
    write_outputs(layout);

    auto const& solved = layout.getSolved();

    auto rect_a = solved.at("a")->getGeometry();
    auto rect_b = solved.at("b")->getGeometry();
    auto rect_c = solved.at("c")->getGeometry();

    EXPECT_NEAR(rect_a.y(), rect_b.y(), 1e-6);
    EXPECT_NEAR(rect_b.y(), rect_c.y(), 1e-6);
    EXPECT_NEAR(rect_b.x(), rect_a.x() + rect_a.width() + 15, 1e-6);
    EXPECT_NEAR(rect_c.x(), rect_b.x() + rect_b.width() + 15, 1e-6);
    EXPECT_OUTCOME_OK(checkAlignedHorizontally(rect_a, rect_b));
    EXPECT_OUTCOME_OK(checkAlignedHorizontally(rect_b, rect_c));
}

TEST(KiwiIr, EvenGapX) {
    auto ctx = std::make_shared<KiwiCtx>();

    ctx->use_rect("a", 10, 10, 20, 20);
    ctx->use_rect("b", std::nullopt, 10, 20, 20);
    ctx->use_rect("c", 110, 10, 20, 20);
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<EvenGapConstraint>(Vec<RectSpec2Side>{
            RectSpec2Side::HorizontalRectBounds("a"),
            RectSpec2Side::HorizontalRectBounds("b"),
            RectSpec2Side::HorizontalRectBounds("c"),
        }),
    };
    Layout layout(ctx, constraints);
    layout.solve();
    auto const& solved = layout.getSolved();
    write_outputs(layout);

    auto rect_a = solved.at("a")->getGeometry();
    auto rect_b = solved.at("b")->getGeometry();
    auto rect_c = solved.at("c")->getGeometry();
    EXPECT_NEAR(rect_b.x() - rect_a.x(), rect_c.x() - rect_b.x(), 1e-6);
    EXPECT_NEAR(rect_b.x(), 60.0, 1e-6);
}

TEST(KiwiIr, ParentWrapAndRelative) {
    auto ctx = std::make_shared<KiwiCtx>();
    ctx->use_rect("nested1", 20, 30, 30, 10);
    ctx->use_rect("nested2", 70, 60, 20, 20);
    ctx->use_rect("parent");
    ctx->use_rect("inner");
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
            /*parent_rect_id=*/"parent",
            /*nested_rect_id=*/"inner",
            /*x_dim=*/
            RelDimensionSpec{.size_factor = 0.2, .absolute_offset = 20},
            /*y_dim=*/
            RelDimensionSpec{.size_factor = 0.5},
            /*anchor_fixed=*/AnchorSpec::CenterCenter(),
            /*anchor_relative=*/AnchorSpec::UpperLeft()),
    };
    Layout layout(ctx, constraints);
    layout.verify_constraints();
    layout.solve();
    auto const& solved = layout.getSolved();
    write_outputs(layout);

    auto rect_parent = solved.at("parent")->getGeometry();
    auto rect_inner  = solved.at("inner")->getGeometry();

    EXPECT_NEAR(rect_parent.x(), 15.0, 1e-6);
    EXPECT_NEAR(rect_parent.y(), 20.0, 1e-6);
    EXPECT_NEAR(rect_parent.width(), 90.0, 1e-6);
    EXPECT_NEAR(rect_parent.height(), 80.0, 1e-6);
    EXPECT_NEAR(rect_inner.width(), rect_parent.width() * 0.2, 1e-6);
    EXPECT_NEAR(rect_inner.height(), rect_parent.height() * 0.5, 1e-6);
    EXPECT_NEAR(rect_inner.x(), rect_parent.x() + rect_parent.width() * 0.5 + 20, 1e-6);
    EXPECT_NEAR(rect_inner.y(), rect_parent.y() + rect_parent.height() * 0.5, 1e-6);
    EXPECT_OUTCOME_OK(checkFullyCovers(rect_parent, rect_inner));
}

TEST(KiwiIr, LinearAndEqualSize) {
    auto ctx = std::make_shared<KiwiCtx>();
    ctx->use_rect("a", 10, 10, 40, 25);
    ctx->use_rect("b", std::nullopt, 50, std::nullopt, std::nullopt);
    Rect::Ptr                       a           = ctx->rects.at("a");
    Rect::Ptr                       b           = ctx->rects.at("b");
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<EqualSizeConstraint>("a", "b", false, true),
        std::make_shared<LinearConstraint>(
            b->expr(RectAttr::X), Relation::EQ, a->expr(RectAttr::RIGHT) + 30),
        std::make_shared<LinearConstraint>(
            b->expr(RectAttr::WIDTH), Relation::EQ, a->expr(RectAttr::WIDTH) + 20),
    };
    Layout layout(ctx, constraints);
    layout.verify_constraints();
    layout.solve();
    auto const& solved = layout.getSolved();
    write_outputs(layout);

    auto rect_a = solved.at("a")->getGeometry();
    auto rect_b = solved.at("b")->getGeometry();

    EXPECT_NEAR(rect_b.x(), 80.0, 1e-6);
    EXPECT_NEAR(rect_b.width(), 60.0, 1e-6);
    EXPECT_NEAR(rect_b.height(), 25.0, 1e-6);
    EXPECT_OUTCOME_OK(checkSameHeight(rect_a, rect_b));
}

TEST(KiwiIr, MultiSeparateAndEvenGapRows) {
    auto ctx = std::make_shared<KiwiCtx>();
    ctx->use_rect("r00", 0, 0, 20, 10);
    ctx->use_rect("r01", std::nullopt, 0, 20, 10);
    ctx->use_rect("r02", 80, 0, 20, 10);
    ctx->use_rect("r10", std::nullopt, 30, 20, 10);
    ctx->use_rect("r11", std::nullopt, 30, 20, 10);
    ctx->use_rect("r12", std::nullopt, 30, 20, 10);
    ctx->use_rect("r20", std::nullopt, 60, 20, 10);
    ctx->use_rect("r21", std::nullopt, 60, 20, 10);
    ctx->use_rect("r22", std::nullopt, 60, 20, 10);
    auto                            la          = AlignSpec{.anchor = Anchor::LEFT};
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<EvenGapConstraint>(Vec<RectSpec2Side>{
            RectSpec2Side::HorizontalRectBounds("r00"),
            RectSpec2Side::HorizontalRectBounds("r01"),
            RectSpec2Side::HorizontalRectBounds("r02"),
        }),
        std::make_shared<AlignConstraint>(
            Vec<AlignItem>{{"r00", la}, {"r10", la}, {"r20", la}}),
        std::make_shared<AlignConstraint>(
            Vec<AlignItem>{{"r01", la}, {"r11", la}, {"r21", la}}),
        std::make_shared<AlignConstraint>(
            Vec<AlignItem>{{"r02", la}, {"r12", la}, {"r22", la}}),
        std::make_shared<MultiSeparateConstraint>(
            /*groups=*/
            Vec<Vec<RectSpec1Side>>{
                {
                    RectSpec1Side::Top("r00"),
                    RectSpec1Side::Top("r01"),
                    RectSpec1Side::Top("r02"),
                },
                {
                    RectSpec1Side::Top("r10"),
                    RectSpec1Side::Top("r11"),
                    RectSpec1Side::Top("r12"),
                },
                {
                    RectSpec1Side::Top("r20"),
                    RectSpec1Side::Top("r21"),
                    RectSpec1Side::Top("r22"),
                }},
            /*step=*/30),
    };
    Layout layout(ctx, constraints);
    layout.verify_constraints();
    layout.solve();
    auto const& solved = layout.getSolved();
    write_outputs(layout);

    auto rect_r01 = solved.at("r01")->getGeometry();
    auto rect_r10 = solved.at("r10")->getGeometry();
    auto rect_r20 = solved.at("r20")->getGeometry();
    EXPECT_NEAR(rect_r01.x(), 40.0, 1e-6);
    EXPECT_NEAR(rect_r10.y(), 30.0, 1e-6);
    EXPECT_NEAR(rect_r20.y(), 60.0, 1e-6);

    auto rect_r00 = solved.at("r00")->getGeometry();
    auto rect_r02 = solved.at("r02")->getGeometry();
    EXPECT_OUTCOME_OK(checkSameHeight(rect_r00, rect_r02));
}

TEST(KiwiIr, MultiSeparateGrid) {
    Vec<Vec<RectSpec1Side>> ids = {
        {
            RectSpec1Side::Top("g00"),
            RectSpec1Side::Top("g01"),
            RectSpec1Side::Top("g02"),
        },
        {
            RectSpec1Side::Top("g10"),
            RectSpec1Side::Top("g11"),
            RectSpec1Side::Top("g12"),
        },
        {
            RectSpec1Side::Top("g20"),
            RectSpec1Side::Top("g21"),
            RectSpec1Side::Top("g22"),
        },
    };
    auto ctx = std::make_shared<KiwiCtx>();
    ctx->use_rect("g00", 0, 0, 10, 10);
    for (auto const& row : ids) {
        for (auto const& rid : row) {
            if (rid.rect_id != "g00") {
                ctx->use_rect(rid.rect_id, std::nullopt, std::nullopt, 10, 10);
            }
        }
    }

    Vec<hstd::SPtr<ConstraintBase>> constraints;
    constraints.push_back(std::make_shared<MultiSeparateConstraint>(ids, 25));

    Vec<Vec<RectSpec1Side>> col_groups = {
        {
            RectSpec1Side::Left(ids[0][0].rect_id),
            RectSpec1Side::Left(ids[1][0].rect_id),
            RectSpec1Side::Left(ids[2][0].rect_id),
        },
        {
            RectSpec1Side::Left(ids[0][1].rect_id),
            RectSpec1Side::Left(ids[1][1].rect_id),
            RectSpec1Side::Left(ids[2][1].rect_id),
        },
        {
            RectSpec1Side::Left(ids[0][2].rect_id),
            RectSpec1Side::Left(ids[1][2].rect_id),
            RectSpec1Side::Left(ids[2][2].rect_id),
        },
    };

    constraints.push_back(std::make_shared<MultiSeparateConstraint>(col_groups, 35));

    for (auto const& row : ids) {
        Vec<AlignItem> row_items;
        for (auto const& r : row) {
            row_items.push_back(AlignItem{r.rect_id, AlignSpec{.anchor = Anchor::TOP}});
        }
        constraints.push_back(std::make_shared<AlignConstraint>(row_items));
    }
    for (auto const& col : col_groups) {
        Vec<AlignItem> col_items;
        for (auto const& r : col) {
            col_items.push_back(AlignItem{r.rect_id, AlignSpec{.anchor = Anchor::LEFT}});
        }
        constraints.push_back(std::make_shared<AlignConstraint>(col_items));
    }

    Layout layout(ctx, constraints);
    layout.verify_constraints();
    layout.solve();
    auto const& solved = layout.getSolved();
    write_outputs(layout);

    auto rect_g12 = solved.at("g12")->getGeometry();
    auto rect_g21 = solved.at("g21")->getGeometry();

    EXPECT_NEAR(rect_g12.x(), 70.0, 1e-6);
    EXPECT_NEAR(rect_g12.y(), 25.0, 1e-6);
    EXPECT_NEAR(rect_g21.x(), 35.0, 1e-6);
    EXPECT_NEAR(rect_g21.y(), 50.0, 1e-6);
    EXPECT_OUTCOME_OK(checkSameWidth(rect_g12, rect_g21));
    EXPECT_OUTCOME_OK(checkSameHeight(rect_g12, rect_g21));
}

TEST(KiwiIr, EvenGapParentsAndRelative) {
    auto ctx = std::make_shared<KiwiCtx>();
    ctx->use_rect("fix1", 0, 0, 100, 60);
    ctx->use_rect("fix2", std::nullopt, 0, 100, 60);
    ctx->use_rect("fix3", 300, 0, 100, 60);
    ctx->use_rect("rel1");
    ctx->use_rect("rel2");
    ctx->use_rect("rel3");
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<EvenGapConstraint>(Vec<RectSpec2Side>{
            RectSpec2Side::HorizontalRectBounds("fix1"),
            RectSpec2Side::HorizontalRectBounds("fix2"),
            RectSpec2Side::HorizontalRectBounds("fix3"),
        }),
        std::make_shared<RelativeConstraint>(
            /*parent_rect_id=*/"fix1",
            /*nested_rect_id=*/"rel1",
            RelDimensionSpec{.size_factor = 0.2, .absolute_offset = 10},
            RelDimensionSpec{.size_factor = 0.5},
            /*anchor_fixed=*/AnchorSpec::CenterCenter(),
            /*anchor_relative=*/AnchorSpec::UpperLeft()),
        std::make_shared<RelativeConstraint>(
            /*parent_rect_id=*/"fix2",
            /*nested_rect_id=*/"rel2",
            RelDimensionSpec{.size_factor = 0.2, .absolute_offset = 10},
            RelDimensionSpec{.size_factor = 0.5},
            /*anchor_fixed=*/AnchorSpec::CenterCenter(),
            /*anchor_relative=*/AnchorSpec::UpperLeft()),
        std::make_shared<RelativeConstraint>(
            /*parent_rect_id=*/"fix3",
            /*nested_rect_id=*/"rel3",
            RelDimensionSpec{.size_factor = 0.2, .absolute_offset = 10},
            RelDimensionSpec{.size_factor = 0.5},
            /*anchor_fixed=*/AnchorSpec::CenterCenter(),
            /*anchor_relative=*/AnchorSpec::UpperLeft()),
    };

    Layout layout(ctx, constraints);
    layout.verify_constraints();
    layout.solve();
    auto const& solved = layout.getSolved();
    write_outputs(layout);

    auto rect_p2 = solved.at("fix2")->getGeometry();
    auto rect_c2 = solved.at("rel2")->getGeometry();
    EXPECT_NEAR(rect_p2.x(), 150.0, 1e-6);
    EXPECT_NEAR(rect_c2.width(), 20.0, 1e-6);
    EXPECT_NEAR(rect_c2.height(), 30.0, 1e-6);
    EXPECT_NEAR(rect_c2.x(), rect_p2.x() + 50 + 10, 1e-6);
    EXPECT_NEAR(rect_c2.y(), rect_p2.y() + 30, 1e-6);

    EXPECT_OUTCOME_OK(checkFullyCovers(rect_p2, rect_c2));
}

TEST(KiwiIr, VerifyPass) {
    auto ctx = std::make_shared<KiwiCtx>();
    ctx->use_rect("a", 0, 0, 10, 10);
    ctx->use_rect("b", std::nullopt, 0, 10, 10);
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<SeparateConstraint>(
            RectSpec1Side("b", Anchor::LEFT), RectSpec1Side("a", Anchor::RIGHT), 5),
    };
    Layout layout(ctx, constraints);
    EXPECT_NO_THROW(layout.verify_constraints());
}

TEST(KiwiIr, VerifyPassWeakConflict) {
    auto ctx = std::make_shared<KiwiCtx>();
    ctx->use_rect("a");
    Rect::Ptr                       a           = ctx->rects.at("a");
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<LinearConstraint>(
            a->expr(RectAttr::X), Relation::EQ, Expr(0), Strength::WEAK),
        std::make_shared<LinearConstraint>(
            a->expr(RectAttr::X), Relation::EQ, Expr(100), Strength::WEAK),
    };
    Layout layout(ctx, constraints);
    EXPECT_NO_THROW(layout.verify_constraints());
}

TEST(KiwiIr, VerifyFailPinConflict) {
    auto ctx = std::make_shared<KiwiCtx>();
    ctx->use_rect("a", 0, std::nullopt, std::nullopt, std::nullopt);
    Rect::Ptr                       a           = ctx->rects.at("a");
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<LinearConstraint>(a->expr(RectAttr::X), Relation::EQ, Expr(10)),
    };
    Layout layout(ctx, constraints);

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
    auto ctx = std::make_shared<KiwiCtx>();
    ctx->use_rect("a");
    ctx->use_rect("b");
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<SeparateConstraint>(
            RectSpec1Side("b", Anchor::LEFT), RectSpec1Side("a", Anchor::RIGHT), 5),
        std::make_shared<SeparateConstraint>(
            RectSpec1Side("b", Anchor::LEFT), RectSpec1Side("a", Anchor::RIGHT), 7),
    };
    Layout layout(ctx, constraints);

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

/// \brief Verify the even gap constraint can be linked with other
/// constraint that provides a fixed spacing between the nodes.
TEST(KiwiIr, EvenGapWithMultiSeparateChangeDistance) {
    auto ctx = std::make_shared<KiwiCtx>();
    ctx->use_rect("a", 0, 0, 10, 10);
    ctx->use_rect("b", std::nullopt, 0, 10, 10);
    ctx->use_rect("c", std::nullopt, 0, 10, 10);
    ctx->use_rect("d", std::nullopt, 0, 10, 10);
    ctx->use_rect("e", std::nullopt, 0, 10, 10);
    ctx->use_rect("f", std::nullopt, 0, 10, 10);
    double                          step        = 40.0;
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<EvenGapConstraint>(Vec<RectSpec2Side>{
            RectSpec2Side::HorizontalRectBounds("a"),
            RectSpec2Side::HorizontalRectBounds("b"),
            RectSpec2Side::HorizontalRectBounds("c"),
            RectSpec2Side::HorizontalRectBounds("d"),
            RectSpec2Side::HorizontalRectBounds("e"),
            RectSpec2Side::HorizontalRectBounds("f"),
        }),
        std::make_shared<MultiSeparateConstraint>(
            /*groups=*/
            Vec<Vec<RectSpec1Side>>{
                {RectSpec1Side::Left("a")},
                {RectSpec1Side::Left("b")},
                {RectSpec1Side::Left("c")}},
            /*step=*/step),
    };
    Layout layout(ctx, constraints);
    layout.verify_constraints();
    layout.solve();
    auto const& solved = layout.getSolved();
    write_outputs(layout, "run1");

    auto rect_a = solved.at("a")->getGeometry();
    auto rect_b = solved.at("b")->getGeometry();
    auto rect_c = solved.at("c")->getGeometry();
    auto rect_d = solved.at("d")->getGeometry();
    auto rect_e = solved.at("e")->getGeometry();
    auto rect_f = solved.at("f")->getGeometry();

    EXPECT_NEAR(rect_a.x() + step, rect_b.x(), 1e-6);
    EXPECT_NEAR(rect_b.x() + step, rect_c.x(), 1e-6);
    EXPECT_NEAR(rect_c.x() + step, rect_d.x(), 1e-6);
    EXPECT_NEAR(rect_d.x() + step, rect_e.x(), 1e-6);
    EXPECT_NEAR(rect_e.x() + step, rect_f.x(), 1e-6);
    EXPECT_NEAR(rect_a.x() + step, rect_b.x(), 1e-6);
    EXPECT_NEAR(rect_b.x() + step, rect_c.x(), 1e-6);

    // Change step and verify new layout
    double new_step = 60.0;
    constraints[1]  = std::make_shared<MultiSeparateConstraint>(
        Vec<Vec<RectSpec1Side>>{
            {RectSpec1Side::Left("a")},
            {RectSpec1Side::Left("c")},
            {RectSpec1Side::Left("e")}},
        new_step);
    Layout layout2(ctx, constraints);
    layout2.verify_constraints();
    layout2.solve();
    auto const& solved2 = layout.getSolved();
    write_outputs(layout2, "run2");
    auto rect_a2 = solved2.at("a")->getGeometry();
    auto rect_b2 = solved2.at("b")->getGeometry();
    auto rect_c2 = solved2.at("c")->getGeometry();
    auto rect_d2 = solved2.at("d")->getGeometry();
    auto rect_e2 = solved2.at("e")->getGeometry();
    auto rect_f2 = solved2.at("f")->getGeometry();

    double new_gap = new_step / 2.0;
    EXPECT_NEAR(rect_b2.x() - rect_a2.x(), new_gap, 1e-6);
    EXPECT_NEAR(rect_c2.x() - rect_a2.x(), new_step, 1e-6);
    EXPECT_NEAR(rect_e2.x() - rect_c2.x(), new_step, 1e-6);
}

TEST(KiwiIr, ConflictingMultiSeparate) {
    auto ctx = std::make_shared<KiwiCtx>();
    ctx->use_rect("x", 0, 0, 10, 10);
    ctx->use_rect("y", std::nullopt, 0, 10, 10);
    ctx->use_rect("z", std::nullopt, 0, 10, 10);
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<MultiSeparateConstraint>(
            /*groups=*/
            Vec<Vec<RectSpec1Side>>{
                {RectSpec1Side::Left("x")},
                {RectSpec1Side::Left("y")},
                {RectSpec1Side::Left("z")}},
            /*step=*/20),
        std::make_shared<MultiSeparateConstraint>(
            /*groups=*/
            Vec<Vec<RectSpec1Side>>{
                {RectSpec1Side::Left("x")},
                {RectSpec1Side::Left("y")},
            },
            /*step=*/30),
    };
    Layout layout(ctx, constraints);
    try {
        layout.verify_constraints();
        FAIL() << "Expected constraint conflict";
    } catch (ConstraintVerificationError const& e) {
        Str msg = e.what();
        EXPECT_NE(msg.find("MultiSeparateConstraint"), Str::npos);
    }
}

TEST(KiwiIr, PinNodeLocation) {
    auto ctx = std::make_shared<KiwiCtx>();
    ctx->use_rect("pinned", 42, 10, 30, 20);
    Layout layout(ctx, {});
    layout.verify_constraints();
    layout.solve();
    auto const& solved = layout.getSolved();
    write_outputs(layout);
    auto rect_p = solved.at("pinned")->getGeometry();
    EXPECT_NEAR(rect_p.x(), 42, 1e-6);
    EXPECT_NEAR(rect_p.y(), 10, 1e-6);
    EXPECT_NEAR(rect_p.width(), 30, 1e-6);
    EXPECT_NEAR(rect_p.height(), 20, 1e-6);
}

TEST(KiwiIr, PinAndLeftOf) {
    auto ctx = std::make_shared<KiwiCtx>();
    ctx->use_rect("static", 100, 0, 20, 20);
    ctx->use_rect("movable", std::nullopt, 0, 15, 15);
    Rect::Ptr                       s           = ctx->rects.at("static");
    Rect::Ptr                       m           = ctx->rects.at("movable");
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<LinearConstraint>(
            m->expr(RectAttr::X) + m->expr(RectAttr::WIDTH),
            Relation::LE,
            s->expr(RectAttr::X)),
    };
    Layout layout(ctx, constraints);
    layout.verify_constraints();
    layout.solve();
    auto const& solved = layout.getSolved();
    write_outputs(layout);
    auto rect_s = solved.at("static")->getGeometry();
    auto rect_m = solved.at("movable")->getGeometry();
    EXPECT_OUTCOME_OK(checkLeftOf(rect_s, rect_m));
    EXPECT_LE(rect_m.x() + rect_m.width(), rect_s.x() + 1e-6);
}

TEST(KiwiIr, LeftOfAndBelow) {
    auto ctx = std::make_shared<KiwiCtx>();
    ctx->use_rect("leftStatic", 0, 0, 20, 20);
    ctx->use_rect("rightStatic", 100, 0, 20, 20);
    ctx->use_rect("target", std::nullopt, std::nullopt, 15, 15);
    Rect::Ptr                       ls          = ctx->rects.at("leftStatic");
    Rect::Ptr                       rs          = ctx->rects.at("rightStatic");
    Rect::Ptr                       t           = ctx->rects.at("target");
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<LinearConstraint>(
            t->expr(RectAttr::X) + t->expr(RectAttr::WIDTH),
            Relation::LE,
            rs->expr(RectAttr::X)),
        std::make_shared<LinearConstraint>(
            t->expr(RectAttr::Y),
            Relation::GE,
            ls->expr(RectAttr::Y) + ls->expr(RectAttr::HEIGHT)),
    };
    Layout layout(ctx, constraints);
    layout.verify_constraints();
    layout.solve();
    auto const& solved = layout.getSolved();
    write_outputs(layout);
    auto rect_ls = solved.at("leftStatic")->getGeometry();
    auto rect_rs = solved.at("rightStatic")->getGeometry();
    auto rect_t  = solved.at("target")->getGeometry();
    EXPECT_OUTCOME_OK(checkLeftOf(rect_rs, rect_t));
    EXPECT_OUTCOME_OK(checkBelow(rect_ls, rect_t));
}

TEST(KiwiIr, BoundedAllSides) {
    auto ctx = std::make_shared<KiwiCtx>();
    ctx->use_rect("leftWall", 0, 0, 10, 100);
    ctx->use_rect("rightWall", 200, 0, 10, 100);
    ctx->use_rect("topWall", 0, 0, 210, 10);
    ctx->use_rect("bottomWall", 0, 150, 210, 10);
    ctx->use_rect("center", std::nullopt, std::nullopt, 30, 30);
    Rect::Ptr                       lw          = ctx->rects.at("leftWall");
    Rect::Ptr                       rw          = ctx->rects.at("rightWall");
    Rect::Ptr                       tw          = ctx->rects.at("topWall");
    Rect::Ptr                       bw          = ctx->rects.at("bottomWall");
    Rect::Ptr                       c           = ctx->rects.at("center");
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<LinearConstraint>(
            c->expr(RectAttr::X),
            Relation::GE,
            lw->expr(RectAttr::X) + lw->expr(RectAttr::WIDTH)),
        std::make_shared<LinearConstraint>(
            c->expr(RectAttr::X) + c->expr(RectAttr::WIDTH),
            Relation::LE,
            rw->expr(RectAttr::X)),
        std::make_shared<LinearConstraint>(
            c->expr(RectAttr::Y),
            Relation::GE,
            tw->expr(RectAttr::Y) + tw->expr(RectAttr::HEIGHT)),
        std::make_shared<LinearConstraint>(
            c->expr(RectAttr::Y) + c->expr(RectAttr::HEIGHT),
            Relation::LE,
            bw->expr(RectAttr::Y)),
    };
    Layout layout(ctx, constraints);
    layout.verify_constraints();
    layout.solve();
    auto const& solved = layout.getSolved();
    write_outputs(layout);
    auto rect_c  = solved.at("center")->getGeometry();
    auto rect_lw = solved.at("leftWall")->getGeometry();
    auto rect_rw = solved.at("rightWall")->getGeometry();
    auto rect_tw = solved.at("topWall")->getGeometry();
    auto rect_bw = solved.at("bottomWall")->getGeometry();
    EXPECT_OUTCOME_OK(checkRightOf(rect_lw, rect_c));
    EXPECT_OUTCOME_OK(checkLeftOf(rect_rw, rect_c));
    EXPECT_OUTCOME_OK(checkBelow(rect_tw, rect_c));
    EXPECT_OUTCOME_OK(checkAbove(rect_bw, rect_c));
}

TEST(KiwiIr, RelativeOutsideParent) {
    auto ctx = std::make_shared<KiwiCtx>();
    ctx->use_rect("parent", 50, 50, 100, 100);
    ctx->use_rect("nested");
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<RelativeConstraint>(
            /*parent_rect_id=*/"parent",
            /*nested_rect_id=*/"nested",
            RelDimensionSpec{.absolute_offset = -20},
            RelDimensionSpec{.absolute_offset = -30}),
    };
    Layout layout(ctx, constraints);
    layout.verify_constraints();
    layout.solve();
    auto const& solved = layout.getSolved();
    write_outputs(layout);
    auto rect_parent = solved.at("parent")->getGeometry();
    auto rect_nested = solved.at("nested")->getGeometry();
    EXPECT_NEAR(rect_nested.x(), rect_parent.x() - 20, 1e-6);
    EXPECT_NEAR(rect_nested.y(), rect_parent.y() - 30, 1e-6);
    EXPECT_TRUE(rect_nested.x() < rect_parent.x());
    EXPECT_TRUE(rect_nested.y() < rect_parent.y());
}

TEST(KiwiIr, RelativeVariations) {
    auto ctx = std::make_shared<KiwiCtx>();
    ctx->use_rect("fix", 0, 0, 100, 80);
    ctx->use_rect("rel");
    // width factor 0.5, height factor 0.6, right-bottom anchors on both
    Vec<hstd::SPtr<ConstraintBase>> constraints = {
        std::make_shared<RelativeConstraint>(
            /*parent_rect_id=*/"fix",
            /*nested_rect_id=*/"rel",
            RelDimensionSpec{.size_factor = 0.5},
            RelDimensionSpec{.size_factor = 0.6},
            /*anchor_fixed=*/AnchorSpec::LowerRight(),
            /*anchor_relative=*/AnchorSpec::LowerRight()),
    };
    Layout layout(ctx, constraints);
    layout.verify_constraints();
    layout.solve();
    auto const& solved = layout.getSolved();
    write_outputs(layout);
    auto rect_p = solved.at("fix")->getGeometry();
    auto rect_c = solved.at("rel")->getGeometry();
    EXPECT_NEAR(rect_c.width(), rect_p.width() * 0.5, 1e-6);
    EXPECT_NEAR(rect_c.height(), rect_p.height() * 0.6, 1e-6);
    EXPECT_NEAR(rect_c.x() + rect_c.width(), rect_p.x() + rect_p.width(), 1e-6);
    EXPECT_NEAR(rect_c.y() + rect_c.height(), rect_p.y() + rect_p.height(), 1e-6);
}

TEST(KiwiIr, EqualSizeWithParentWrap) {
    auto ctx = std::make_shared<KiwiCtx>();
    ctx->use_rect("parent");
    ctx->use_rect("nested");
    ctx->use_rect("other", std::nullopt, 0, 10, 10);
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
    Layout layout(ctx, constraints);
    layout.verify_constraints();
    layout.solve();
    auto const& solved = layout.getSolved();
    write_outputs(layout);
    auto rect_parent = solved.at("parent")->getGeometry();
    auto rect_nested = solved.at("nested")->getGeometry();
    auto rect_other  = solved.at("other")->getGeometry();
    EXPECT_OUTCOME_OK(checkSameSize(rect_nested, rect_other));
    EXPECT_OUTCOME_OK(checkSameSize(rect_parent, rect_nested));
}

} // namespace hstd::ext::kiwi_ir
