#pragma once

#if ORG_BUILD_WITH_PROTOBUF

#    include <hstd_cpp_lib/ext/geometry/kiwi_ir.hpp>
#    include <hstd_cpp_lib/ext/hstd_serde.hpp>

namespace hstd::serde {
template <>
struct proto_serde<
    hstd::ext::kiwi_ir::proto::AnchorSpec,
    hstd::ext::kiwi_ir::AnchorSpec> {
    static void write(
        hstd::ext::kiwi_ir::proto::AnchorSpec* out,
        hstd::ext::kiwi_ir::AnchorSpec const&  in);
    static void read(
        hstd::ext::kiwi_ir::proto::AnchorSpec const& in,
        hstd::ext::kiwi_ir::AnchorSpec*              out);
};

template <>
struct proto_serde<
    hstd::ext::kiwi_ir::proto::RectSpec2Side,
    hstd::ext::kiwi_ir::RectSpec2Side> {
    static void write(
        hstd::ext::kiwi_ir::proto::RectSpec2Side* out,
        hstd::ext::kiwi_ir::RectSpec2Side const&  in);
    static void read(
        hstd::ext::kiwi_ir::proto::RectSpec2Side const& in,
        hstd::ext::kiwi_ir::RectSpec2Side*              out);
};

template <>
struct proto_serde<
    hstd::ext::kiwi_ir::proto::RectSpec1Side,
    hstd::ext::kiwi_ir::RectSpec1Side> {
    static void write(
        hstd::ext::kiwi_ir::proto::RectSpec1Side* out,
        hstd::ext::kiwi_ir::RectSpec1Side const&  in);
    static void read(
        hstd::ext::kiwi_ir::proto::RectSpec1Side const& in,
        hstd::ext::kiwi_ir::RectSpec1Side*              out);
};

template <>
struct proto_serde<hstd::ext::kiwi_ir::proto::Expr, hstd::ext::kiwi_ir::Expr> {
    static void write(
        hstd::ext::kiwi_ir::proto::Expr* out,
        hstd::ext::kiwi_ir::Expr const&  in);
    static void read(
        hstd::ext::kiwi_ir::proto::Expr const& in,
        hstd::ext::kiwi_ir::Expr*              out);
};

template <>
struct proto_serde<
    hstd::ext::kiwi_ir::proto::Constraint,
    hstd::ext::kiwi_ir::Constraint> {
    static void write(
        hstd::ext::kiwi_ir::proto::Constraint* out,
        hstd::ext::kiwi_ir::Constraint const&  in);
    static void read(
        hstd::ext::kiwi_ir::proto::Constraint const& in,
        hstd::ext::kiwi_ir::Constraint*              out);
};

template <>
struct proto_serde<hstd::ext::kiwi_ir::proto::Rect, hstd::ext::kiwi_ir::Rect> {
    static void write(
        hstd::ext::kiwi_ir::proto::Rect* out,
        hstd::ext::kiwi_ir::Rect const&  in);
    static void read(
        hstd::ext::kiwi_ir::proto::Rect const& in,
        hstd::ext::kiwi_ir::Rect*              out);
};

template <>
struct proto_serde<hstd::ext::kiwi_ir::proto::EdgeDesc, hstd::ext::kiwi_ir::EdgeDesc> {
    static void write(
        hstd::ext::kiwi_ir::proto::EdgeDesc* out,
        hstd::ext::kiwi_ir::EdgeDesc const&  in);
    static void read(
        hstd::ext::kiwi_ir::proto::EdgeDesc const& in,
        hstd::ext::kiwi_ir::EdgeDesc*              out);
};

template <>
struct proto_serde<hstd::ext::kiwi_ir::proto::AlignSpec, hstd::ext::kiwi_ir::AlignSpec> {
    static void write(
        hstd::ext::kiwi_ir::proto::AlignSpec* out,
        hstd::ext::kiwi_ir::AlignSpec const&  in);
    static void read(
        hstd::ext::kiwi_ir::proto::AlignSpec const& in,
        hstd::ext::kiwi_ir::AlignSpec*              out);
};

template <>
struct proto_serde<hstd::ext::kiwi_ir::proto::AlignItem, hstd::ext::kiwi_ir::AlignItem> {
    static void write(
        hstd::ext::kiwi_ir::proto::AlignItem* out,
        hstd::ext::kiwi_ir::AlignItem const&  in);
    static void read(
        hstd::ext::kiwi_ir::proto::AlignItem const& in,
        hstd::ext::kiwi_ir::AlignItem*              out);
};

template <>
struct proto_serde<
    hstd::ext::kiwi_ir::proto::AlignConstraint,
    hstd::ext::kiwi_ir::AlignConstraint> {
    static void write(
        hstd::ext::kiwi_ir::proto::AlignConstraint* out,
        hstd::ext::kiwi_ir::AlignConstraint const&  in);
    static void read(
        hstd::ext::kiwi_ir::proto::AlignConstraint const& in,
        hstd::ext::kiwi_ir::AlignConstraint*              out);
};

template <>
struct proto_serde<
    hstd::ext::kiwi_ir::proto::SeparateConstraint,
    hstd::ext::kiwi_ir::SeparateConstraint> {
    static void write(
        hstd::ext::kiwi_ir::proto::SeparateConstraint* out,
        hstd::ext::kiwi_ir::SeparateConstraint const&  in);

    static void read(
        hstd::ext::kiwi_ir::proto::SeparateConstraint const& in,
        hstd::ext::kiwi_ir::SeparateConstraint*              out);
};

template <>
struct proto_serde<
    hstd::ext::kiwi_ir::proto::MultiSeparateConstraint,
    hstd::ext::kiwi_ir::MultiSeparateConstraint> {
    static void write(
        hstd::ext::kiwi_ir::proto::MultiSeparateConstraint* out,
        hstd::ext::kiwi_ir::MultiSeparateConstraint const&  in);

    static void read(
        hstd::ext::kiwi_ir::proto::MultiSeparateConstraint const& in,
        hstd::ext::kiwi_ir::MultiSeparateConstraint*              out);
};

template <>
struct proto_serde<
    hstd::ext::kiwi_ir::proto::ParentWrapConstraint,
    hstd::ext::kiwi_ir::ParentWrapConstraint> {
    static void write(
        hstd::ext::kiwi_ir::proto::ParentWrapConstraint* out,
        hstd::ext::kiwi_ir::ParentWrapConstraint const&  in);

    static void read(
        hstd::ext::kiwi_ir::proto::ParentWrapConstraint const& in,
        hstd::ext::kiwi_ir::ParentWrapConstraint*              out);
};

template <>
struct proto_serde<
    hstd::ext::kiwi_ir::proto::RelDimensionSpec,
    hstd::ext::kiwi_ir::RelDimensionSpec> {
    static void write(
        hstd::ext::kiwi_ir::proto::RelDimensionSpec* out,
        hstd::ext::kiwi_ir::RelDimensionSpec const&  in);

    static void read(
        hstd::ext::kiwi_ir::proto::RelDimensionSpec const& in,
        hstd::ext::kiwi_ir::RelDimensionSpec*              out);
};

template <>
struct proto_serde<
    hstd::ext::kiwi_ir::proto::RelativeConstraint,
    hstd::ext::kiwi_ir::RelativeConstraint> {
    static void write(
        hstd::ext::kiwi_ir::proto::RelativeConstraint* out,
        hstd::ext::kiwi_ir::RelativeConstraint const&  in);

    static void read(
        hstd::ext::kiwi_ir::proto::RelativeConstraint const& in,
        hstd::ext::kiwi_ir::RelativeConstraint*              out);
};

template <>
struct proto_serde<
    hstd::ext::kiwi_ir::proto::EvenGapConstraint,
    hstd::ext::kiwi_ir::EvenGapConstraint> {
    static void write(
        hstd::ext::kiwi_ir::proto::EvenGapConstraint* out,
        hstd::ext::kiwi_ir::EvenGapConstraint const&  in);

    static void read(
        hstd::ext::kiwi_ir::proto::EvenGapConstraint const& in,
        hstd::ext::kiwi_ir::EvenGapConstraint*              out);
};

template <>
struct proto_serde<
    hstd::ext::kiwi_ir::proto::EqualSizeConstraint,
    hstd::ext::kiwi_ir::EqualSizeConstraint> {
    static void write(
        hstd::ext::kiwi_ir::proto::EqualSizeConstraint* out,
        hstd::ext::kiwi_ir::EqualSizeConstraint const&  in);

    static void read(
        hstd::ext::kiwi_ir::proto::EqualSizeConstraint const& in,
        hstd::ext::kiwi_ir::EqualSizeConstraint*              out);
};

template <>
struct proto_serde<
    hstd::ext::kiwi_ir::proto::LinearConstraint,
    hstd::ext::kiwi_ir::LinearConstraint> {
    static void write(
        hstd::ext::kiwi_ir::proto::LinearConstraint* out,
        hstd::ext::kiwi_ir::LinearConstraint const&  in);

    static void read(
        hstd::ext::kiwi_ir::proto::LinearConstraint const& in,
        hstd::ext::kiwi_ir::LinearConstraint*              out);
};

template <>
struct proto_serde<
    hstd::ext::kiwi_ir::proto::ConstraintSpec,
    hstd::SPtr<hstd::ext::kiwi_ir::ConstraintBase>> {
    static void write(
        hstd::ext::kiwi_ir::proto::ConstraintSpec*            out,
        hstd::SPtr<hstd::ext::kiwi_ir::ConstraintBase> const& in);

    static void read(
        hstd::ext::kiwi_ir::proto::ConstraintSpec const& in,
        hstd::SPtr<hstd::ext::kiwi_ir::ConstraintBase>*  out);
};

template <>
struct proto_serde<
    hstd::ext::kiwi_ir::proto::ConstraintEntry,
    hstd::ext::kiwi_ir::ConstraintEntry> {
    static void write(
        hstd::ext::kiwi_ir::proto::ConstraintEntry* out,
        hstd::ext::kiwi_ir::ConstraintEntry const&  in);

    static void read(
        hstd::ext::kiwi_ir::proto::ConstraintEntry const& in,
        hstd::ext::kiwi_ir::ConstraintEntry*              out);
};

} // namespace hstd::serde
#endif
