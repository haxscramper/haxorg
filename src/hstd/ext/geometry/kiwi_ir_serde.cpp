#include "kiwi_ir_serde.hpp"
#include "hstd/ext/hstd_serde.hpp"

using namespace hstd::ext::kiwi_ir;
using namespace hstd::ext;

namespace {

proto::Relation write_relation(kiwi::RelationalOperator op) {
    switch (op) {
        case kiwi::OP_EQ: return proto::RELATION_EQ;
        case kiwi::OP_LE: return proto::RELATION_LE;
        case kiwi::OP_GE: return proto::RELATION_GE;
    }

    throw std::domain_error("Unsupported kiwi relational operator");
}

kiwi::RelationalOperator read_relation(proto::Relation relation) {
    switch (relation) {
        case proto::RELATION_EQ: return kiwi::OP_EQ;
        case proto::RELATION_LE: return kiwi::OP_LE;
        case proto::RELATION_GE: return kiwi::OP_GE;
    }

    throw std::domain_error("Unsupported protobuf relation");
}

} // namespace

void hstd::serde::proto_serde<proto::AnchorSpec, kiwi_ir::AnchorSpec>::write(
    proto::AnchorSpec*         out,
    kiwi_ir::AnchorSpec const& in) {
    out->set_x(static_cast<proto::Anchor>(in.x));
    out->set_y(static_cast<proto::Anchor>(in.y));
}

void hstd::serde::proto_serde<proto::AnchorSpec, kiwi_ir::AnchorSpec>::read(
    proto::AnchorSpec const& in,
    kiwi_ir::AnchorSpec*     out) {
    *out = kiwi_ir::AnchorSpec(
        static_cast<kiwi_ir::Anchor>(in.x()), static_cast<kiwi_ir::Anchor>(in.y()));
}

void hstd::serde::proto_serde<proto::RectSpec2Side, kiwi_ir::RectSpec2Side>::write(
    proto::RectSpec2Side*         out,
    kiwi_ir::RectSpec2Side const& in) {
    out->set_rect_id(in.rect_id);
    out->set_min_anchor(static_cast<proto::Anchor>(in.min_anchor));
    out->set_max_anchor(static_cast<proto::Anchor>(in.max_anchor));
}

void hstd::serde::proto_serde<proto::RectSpec2Side, kiwi_ir::RectSpec2Side>::read(
    proto::RectSpec2Side const& in,
    kiwi_ir::RectSpec2Side*     out) {
    *out = kiwi_ir::RectSpec2Side(
        in.rect_id(),
        static_cast<kiwi_ir::Anchor>(in.min_anchor()),
        static_cast<kiwi_ir::Anchor>(in.max_anchor()));
}

void hstd::serde::proto_serde<proto::RectSpec1Side, kiwi_ir::RectSpec1Side>::write(
    proto::RectSpec1Side*         out,
    kiwi_ir::RectSpec1Side const& in) {
    out->set_rect_id(in.rect_id);
    out->set_anchor(static_cast<proto::Anchor>(in.anchor));
}

void hstd::serde::proto_serde<proto::RectSpec1Side, kiwi_ir::RectSpec1Side>::read(
    proto::RectSpec1Side const& in,
    kiwi_ir::RectSpec1Side*     out) {
    *out = kiwi_ir::RectSpec1Side(
        in.rect_id(), static_cast<kiwi_ir::Anchor>(in.anchor()));
}

void hstd::serde::proto_serde<proto::Expr, kiwi_ir::Expr>::write(
    proto::Expr*         out,
    kiwi_ir::Expr const& in) {
    in.node->writeSerial(out->mutable_node());
}

void hstd::serde::proto_serde<proto::Expr, kiwi_ir::Expr>::read(
    proto::Expr const& in,
    kiwi_ir::Expr*     out) {
    out->node = Expr::readNode(in.node());
}

void hstd::serde::proto_serde<proto::Constraint, kiwi_ir::Constraint>::write(
    proto::Constraint*         out,
    kiwi_ir::Constraint const& in) {
    hstd::serde::write_serde(out->mutable_lhs(), in.lhs);
    hstd::serde::write_serde(out->mutable_rhs(), in.rhs);
    out->set_op(write_relation(in.op));

    if (in.strength) { out->set_strength(*in.strength); }
}

void hstd::serde::proto_serde<proto::Constraint, kiwi_ir::Constraint>::read(
    proto::Constraint const& in,
    kiwi_ir::Constraint*     out) {
    kiwi_ir::Expr lhs(0.0);
    kiwi_ir::Expr rhs(0.0);

    hstd::serde::read_serde(in.lhs(), &lhs);
    hstd::serde::read_serde(in.rhs(), &rhs);

    *out = kiwi_ir::Constraint(lhs, rhs, read_relation(in.op()));

    if (in.has_strength()) { out->strength = in.strength(); }
}

void hstd::serde::proto_serde<proto::Rect, kiwi_ir::Rect>::write(
    proto::Rect*         out,
    kiwi_ir::Rect const& in) {
    out->set_rect_id(in.rect_id);

    if (in.x0) { out->set_x0(*in.x0); }

    if (in.y0) { out->set_y0(*in.y0); }

    if (in.width0) { out->set_width0(*in.width0); }

    if (in.height0) { out->set_height0(*in.height0); }
}

void hstd::serde::proto_serde<proto::Rect, kiwi_ir::Rect>::read(
    proto::Rect const& in,
    kiwi_ir::Rect*     out) {
    hstd::Opt<double> x0;
    hstd::Opt<double> y0;
    hstd::Opt<double> width0;
    hstd::Opt<double> height0;

    if (in.has_x0()) { x0 = in.x0(); }

    if (in.has_y0()) { y0 = in.y0(); }

    if (in.has_width0()) { width0 = in.width0(); }

    if (in.has_height0()) { height0 = in.height0(); }

    *out = kiwi_ir::Rect(in.rect_id(), x0, y0, width0, height0);
}

void hstd::serde::proto_serde<proto::EdgeDesc, kiwi_ir::EdgeDesc>::write(
    proto::EdgeDesc*         out,
    kiwi_ir::EdgeDesc const& in) {
    out->set_rect_id(in.rect_id);
    out->set_label(in.label);
    out->set_axis(static_cast<proto::Axis>(in.axis));

    if (in.color) { out->set_color(*in.color); }
}

void hstd::serde::proto_serde<proto::EdgeDesc, kiwi_ir::EdgeDesc>::read(
    proto::EdgeDesc const& in,
    kiwi_ir::EdgeDesc*     out) {
    out->rect_id = in.rect_id();
    out->label   = in.label();
    out->axis    = static_cast<kiwi_ir::Axis>(in.axis());
    out->color.reset();

    if (in.has_color()) { out->color = in.color(); }
}

void hstd::serde::proto_serde<proto::AlignSpec, kiwi_ir::AlignSpec>::write(
    proto::AlignSpec*         out,
    kiwi_ir::AlignSpec const& in) {
    out->set_anchor(static_cast<proto::Anchor>(in.anchor));
    out->set_offset(in.offset);
}

void hstd::serde::proto_serde<proto::AlignSpec, kiwi_ir::AlignSpec>::read(
    proto::AlignSpec const& in,
    kiwi_ir::AlignSpec*     out) {
    out->anchor = static_cast<kiwi_ir::Anchor>(in.anchor());
    out->offset = in.offset();
}

void hstd::serde::proto_serde<proto::AlignItem, kiwi_ir::AlignItem>::write(
    proto::AlignItem*         out,
    kiwi_ir::AlignItem const& in) {
    out->set_rect_id(in.rect_id);
    hstd::serde::write_serde(out->mutable_spec(), in.spec);
}

void hstd::serde::proto_serde<proto::AlignItem, kiwi_ir::AlignItem>::read(
    proto::AlignItem const& in,
    kiwi_ir::AlignItem*     out) {
    out->rect_id = in.rect_id();
    hstd::serde::read_serde(in.spec(), &out->spec);
}

void hstd::serde::proto_serde<proto::AlignConstraint, kiwi_ir::AlignConstraint>::write(
    proto::AlignConstraint*         out,
    kiwi_ir::AlignConstraint const& in) {
    out->clear_items();

    for (kiwi_ir::AlignItem const& item : in.items) {
        hstd::serde::write_serde(out->add_items(), item);
    }

    out->set_strength(static_cast<proto::Strength>(in.strength));
}

void hstd::serde::proto_serde<proto::AlignConstraint, kiwi_ir::AlignConstraint>::read(
    proto::AlignConstraint const& in,
    kiwi_ir::AlignConstraint*     out) {
    hstd::Vec<kiwi_ir::AlignItem> items;
    items.reserve(in.items_size());

    for (proto::AlignItem const& item : in.items()) {
        kiwi_ir::AlignItem value;
        hstd::serde::read_serde(item, &value);
        items.push_back(std::move(value));
    }

    *out = kiwi_ir::AlignConstraint(
        std::move(items), static_cast<kiwi_ir::Strength>(in.strength()));
}

void hstd::serde::proto_serde<proto::SeparateConstraint, kiwi_ir::SeparateConstraint>::
    write(proto::SeparateConstraint* out, kiwi_ir::SeparateConstraint const& in) {
    hstd::serde::write_serde(out->mutable_rect_a(), in.rect_a);
    hstd::serde::write_serde(out->mutable_rect_b(), in.rect_b);
    out->set_offset(in.offset);
    out->set_strength(static_cast<proto::Strength>(in.strength));
}

void hstd::serde::proto_serde<proto::SeparateConstraint, kiwi_ir::SeparateConstraint>::
    read(proto::SeparateConstraint const& in, kiwi_ir::SeparateConstraint* out) {
    kiwi_ir::RectSpec1Side rect_a;
    kiwi_ir::RectSpec1Side rect_b;

    hstd::serde::read_serde(in.rect_a(), &rect_a);
    hstd::serde::read_serde(in.rect_b(), &rect_b);

    *out = kiwi_ir::SeparateConstraint(
        rect_a, rect_b, in.offset(), static_cast<kiwi_ir::Strength>(in.strength()));
}

void hstd::serde::
    proto_serde<proto::MultiSeparateConstraint, kiwi_ir::MultiSeparateConstraint>::write(
        proto::MultiSeparateConstraint*         out,
        kiwi_ir::MultiSeparateConstraint const& in) {
    out->clear_groups();

    for (auto const& group : in.groups) {
        auto* serialized_group = out->add_groups();

        for (kiwi_ir::RectSpec1Side const& item : group) {
            hstd::serde::write_serde(serialized_group->add_items(), item);
        }
    }

    out->set_step(in.step);
    out->set_strength(static_cast<proto::Strength>(in.strength));
}

void hstd::serde::
    proto_serde<proto::MultiSeparateConstraint, kiwi_ir::MultiSeparateConstraint>::read(
        proto::MultiSeparateConstraint const& in,
        kiwi_ir::MultiSeparateConstraint*     out) {
    hstd::Vec<hstd::Vec<kiwi_ir::RectSpec1Side>> groups;
    groups.reserve(in.groups_size());

    for (proto::RectSpec1SideGroup const& serialized_group : in.groups()) {
        hstd::Vec<kiwi_ir::RectSpec1Side> group;
        group.reserve(serialized_group.items_size());

        for (proto::RectSpec1Side const& item : serialized_group.items()) {
            kiwi_ir::RectSpec1Side value;
            hstd::serde::read_serde(item, &value);
            group.push_back(std::move(value));
        }

        groups.push_back(std::move(group));
    }

    *out = kiwi_ir::MultiSeparateConstraint(
        std::move(groups), in.step(), static_cast<kiwi_ir::Strength>(in.strength()));
}

void hstd::serde::
    proto_serde<proto::ParentWrapConstraint, kiwi_ir::ParentWrapConstraint>::write(
        proto::ParentWrapConstraint*         out,
        kiwi_ir::ParentWrapConstraint const& in) {
    out->set_parent_rect_id(in.parent_rect_id);
    out->clear_nested_rect_ids();

    for (auto const& id : in.nested_rect_ids) { out->add_nested_rect_ids(id); }

    out->mutable_pad()->set_left(in.pad.left);
    out->mutable_pad()->set_top(in.pad.top);
    out->mutable_pad()->set_right(in.pad.right);
    out->mutable_pad()->set_bottom(in.pad.bottom);
    out->set_strength(static_cast<proto::Strength>(in.strength));
}

void hstd::serde::
    proto_serde<proto::ParentWrapConstraint, kiwi_ir::ParentWrapConstraint>::read(
        proto::ParentWrapConstraint const& in,
        kiwi_ir::ParentWrapConstraint*     out) {
    hstd::Vec<hstd::Str> nested_rect_ids;
    nested_rect_ids.reserve(in.nested_rect_ids_size());

    for (auto const& id : in.nested_rect_ids()) { nested_rect_ids.push_back(id); }

    hstd::ext::geometry::Padding pad;
    pad.left   = in.pad().left();
    pad.top    = in.pad().top();
    pad.right  = in.pad().right();
    pad.bottom = in.pad().bottom();

    *out = kiwi_ir::ParentWrapConstraint(
        in.parent_rect_id(),
        std::move(nested_rect_ids),
        pad,
        static_cast<kiwi_ir::Strength>(in.strength()));
}

void hstd::serde::proto_serde<proto::RelDimensionSpec, kiwi_ir::RelDimensionSpec>::write(
    proto::RelDimensionSpec*         out,
    kiwi_ir::RelDimensionSpec const& in) {
    if (in.size_factor) { out->set_size_factor(*in.size_factor); }

    if (in.relative_offset) { out->set_relative_offset(*in.relative_offset); }

    out->set_absolute_offset(in.absolute_offset);
}

void hstd::serde::proto_serde<proto::RelDimensionSpec, kiwi_ir::RelDimensionSpec>::read(
    proto::RelDimensionSpec const& in,
    kiwi_ir::RelDimensionSpec*     out) {
    out->size_factor.reset();
    out->relative_offset.reset();

    if (in.has_size_factor()) { out->size_factor = in.size_factor(); }

    if (in.has_relative_offset()) { out->relative_offset = in.relative_offset(); }

    out->absolute_offset = in.absolute_offset();
}

void hstd::serde::proto_serde<proto::RelativeConstraint, kiwi_ir::RelativeConstraint>::
    write(proto::RelativeConstraint* out, kiwi_ir::RelativeConstraint const& in) {
    out->set_relative_rect_id(in.relative_rect_id);
    out->set_fixed_rect_id(in.fixed_rect_id);
    hstd::serde::write_serde(out->mutable_x_dim(), in.x_dim);
    hstd::serde::write_serde(out->mutable_y_dim(), in.y_dim);
    hstd::serde::write_serde(out->mutable_anchor_fixed(), in.anchor_fixed);
    hstd::serde::write_serde(out->mutable_anchor_relative(), in.anchor_relative);
    out->set_strength(static_cast<proto::Strength>(in.strength));
}

void hstd::serde::proto_serde<proto::RelativeConstraint, kiwi_ir::RelativeConstraint>::
    read(proto::RelativeConstraint const& in, kiwi_ir::RelativeConstraint* out) {
    kiwi_ir::RelDimensionSpec x_dim;
    kiwi_ir::RelDimensionSpec y_dim;
    kiwi_ir::AnchorSpec       anchor_fixed;
    kiwi_ir::AnchorSpec       anchor_relative;

    hstd::serde::read_serde(in.x_dim(), &x_dim);
    hstd::serde::read_serde(in.y_dim(), &y_dim);
    hstd::serde::read_serde(in.anchor_fixed(), &anchor_fixed);
    hstd::serde::read_serde(in.anchor_relative(), &anchor_relative);

    *out = kiwi_ir::RelativeConstraint(
        in.fixed_rect_id(),
        in.relative_rect_id(),
        x_dim,
        y_dim,
        anchor_fixed,
        anchor_relative,
        static_cast<kiwi_ir::Strength>(in.strength()));
}

void hstd::serde::proto_serde<proto::EvenGapConstraint, kiwi_ir::EvenGapConstraint>::
    write(proto::EvenGapConstraint* out, kiwi_ir::EvenGapConstraint const& in) {
    out->clear_rects_spec();

    for (kiwi_ir::RectSpec2Side const& spec : in.rects_spec) {
        hstd::serde::write_serde(out->add_rects_spec(), spec);
    }

    out->set_strength(static_cast<proto::Strength>(in.strength));
}

void hstd::serde::proto_serde<proto::EvenGapConstraint, kiwi_ir::EvenGapConstraint>::read(
    proto::EvenGapConstraint const& in,
    kiwi_ir::EvenGapConstraint*     out) {
    hstd::Vec<kiwi_ir::RectSpec2Side> specs;
    specs.reserve(in.rects_spec_size());

    for (proto::RectSpec2Side const& spec : in.rects_spec()) {
        kiwi_ir::RectSpec2Side value;
        hstd::serde::read_serde(spec, &value);
        specs.push_back(std::move(value));
    }

    *out = kiwi_ir::EvenGapConstraint(
        std::move(specs), static_cast<kiwi_ir::Strength>(in.strength()));
}

void hstd::serde::proto_serde<proto::EqualSizeConstraint, kiwi_ir::EqualSizeConstraint>::
    write(proto::EqualSizeConstraint* out, kiwi_ir::EqualSizeConstraint const& in) {
    out->set_rect_a_id(in.rect_a_id);
    out->set_rect_b_id(in.rect_b_id);
    out->set_match_width(in.match_width);
    out->set_match_height(in.match_height);
    out->set_strength(static_cast<proto::Strength>(in.strength));
}

void hstd::serde::proto_serde<proto::EqualSizeConstraint, kiwi_ir::EqualSizeConstraint>::
    read(proto::EqualSizeConstraint const& in, kiwi_ir::EqualSizeConstraint* out) {
    *out = kiwi_ir::EqualSizeConstraint(
        in.rect_a_id(),
        in.rect_b_id(),
        in.match_width(),
        in.match_height(),
        static_cast<kiwi_ir::Strength>(in.strength()));
}

void hstd::serde::proto_serde<proto::LinearConstraint, kiwi_ir::LinearConstraint>::write(
    proto::LinearConstraint*         out,
    kiwi_ir::LinearConstraint const& in) {
    hstd::serde::write_serde(out->mutable_left(), in.left);
    out->set_relation(static_cast<proto::Relation>(in.relation));
    hstd::serde::write_serde(out->mutable_right(), in.right);
    out->set_strength(static_cast<proto::Strength>(in.strength));
}

void hstd::serde::proto_serde<proto::LinearConstraint, kiwi_ir::LinearConstraint>::read(
    proto::LinearConstraint const& in,
    kiwi_ir::LinearConstraint*     out) {
    kiwi_ir::Expr left(0.0);
    kiwi_ir::Expr right(0.0);

    hstd::serde::read_serde(in.left(), &left);
    hstd::serde::read_serde(in.right(), &right);

    *out = kiwi_ir::LinearConstraint(
        left,
        static_cast<kiwi_ir::Relation>(in.relation()),
        right,
        static_cast<kiwi_ir::Strength>(in.strength()));
}

void hstd::serde::
    proto_serde<proto::ConstraintSpec, hstd::SPtr<kiwi_ir::ConstraintBase>>::write(
        proto::ConstraintSpec*                     out,
        hstd::SPtr<kiwi_ir::ConstraintBase> const& in) {
    if (auto value = std::dynamic_pointer_cast<kiwi_ir::AlignConstraint>(in)) {
        hstd::serde::write_serde(out->mutable_align(), *value);
    } else if (auto value = std::dynamic_pointer_cast<kiwi_ir::SeparateConstraint>(in)) {
        hstd::serde::write_serde(out->mutable_separate(), *value);
    } else if (
        auto value = std::dynamic_pointer_cast<kiwi_ir::MultiSeparateConstraint>(in)) {
        hstd::serde::write_serde(out->mutable_multi_separate(), *value);
    } else if (
        auto value = std::dynamic_pointer_cast<kiwi_ir::ParentWrapConstraint>(in)) {
        hstd::serde::write_serde(out->mutable_parent_wrap(), *value);
    } else if (auto value = std::dynamic_pointer_cast<kiwi_ir::RelativeConstraint>(in)) {
        hstd::serde::write_serde(out->mutable_relative(), *value);
    } else if (auto value = std::dynamic_pointer_cast<kiwi_ir::EvenGapConstraint>(in)) {
        hstd::serde::write_serde(out->mutable_even_gap(), *value);
    } else if (auto value = std::dynamic_pointer_cast<kiwi_ir::EqualSizeConstraint>(in)) {
        hstd::serde::write_serde(out->mutable_equal_size(), *value);
    } else if (auto value = std::dynamic_pointer_cast<kiwi_ir::LinearConstraint>(in)) {
        hstd::serde::write_serde(out->mutable_linear(), *value);
    } else {
        throw std::domain_error("Unsupported ConstraintBase subtype");
    }
}

void hstd::serde::
    proto_serde<proto::ConstraintSpec, hstd::SPtr<kiwi_ir::ConstraintBase>>::read(
        proto::ConstraintSpec const&         in,
        hstd::SPtr<kiwi_ir::ConstraintBase>* out) {
    switch (in.kind_case()) {
        case proto::ConstraintSpec::kAlign: {
            auto value = std::make_shared<kiwi_ir::AlignConstraint>(
                hstd::Vec<kiwi_ir::AlignItem>{});
            hstd::serde::read_serde(in.align(), value.get());
            *out = std::move(value);
            return;
        }

        case proto::ConstraintSpec::kSeparate: {
            auto value = std::make_shared<kiwi_ir::SeparateConstraint>(
                kiwi_ir::RectSpec1Side{}, kiwi_ir::RectSpec1Side{}, 0.0);
            hstd::serde::read_serde(in.separate(), value.get());
            *out = std::move(value);
            return;
        }

        case proto::ConstraintSpec::kMultiSeparate: {
            auto value = std::make_shared<kiwi_ir::MultiSeparateConstraint>(
                hstd::Vec<hstd::Vec<kiwi_ir::RectSpec1Side>>{}, 0.0);
            hstd::serde::read_serde(in.multi_separate(), value.get());
            *out = std::move(value);
            return;
        }

        case proto::ConstraintSpec::kParentWrap: {
            auto value = std::make_shared<kiwi_ir::ParentWrapConstraint>(
                hstd::Str{}, hstd::Vec<hstd::Str>{});
            hstd::serde::read_serde(in.parent_wrap(), value.get());
            *out = std::move(value);
            return;
        }

        case proto::ConstraintSpec::kRelative: {
            auto value = std::make_shared<kiwi_ir::RelativeConstraint>(
                hstd::Str{},
                hstd::Str{},
                kiwi_ir::RelDimensionSpec{},
                kiwi_ir::RelDimensionSpec{});
            hstd::serde::read_serde(in.relative(), value.get());
            *out = std::move(value);
            return;
        }

        case proto::ConstraintSpec::kEvenGap: {
            auto value = std::make_shared<kiwi_ir::EvenGapConstraint>(
                hstd::Vec<kiwi_ir::RectSpec2Side>{});
            hstd::serde::read_serde(in.even_gap(), value.get());
            *out = std::move(value);
            return;
        }

        case proto::ConstraintSpec::kEqualSize: {
            auto value = std::make_shared<kiwi_ir::EqualSizeConstraint>(
                hstd::Str{}, hstd::Str{});
            hstd::serde::read_serde(in.equal_size(), value.get());
            *out = std::move(value);
            return;
        }

        case proto::ConstraintSpec::kLinear: {
            auto value = std::make_shared<kiwi_ir::LinearConstraint>(
                kiwi_ir::Expr(0.0), kiwi_ir::Relation::EQ, kiwi_ir::Expr(0.0));
            hstd::serde::read_serde(in.linear(), value.get());
            *out = std::move(value);
            return;
        }

        case proto::ConstraintSpec::KIND_NOT_SET:
            throw std::domain_error("ConstraintSpec kind is not set");
    }

    throw std::domain_error("Unsupported ConstraintSpec kind");
}

void hstd::serde::proto_serde<proto::ConstraintEntry, kiwi_ir::ConstraintEntry>::write(
    proto::ConstraintEntry*         out,
    kiwi_ir::ConstraintEntry const& in) {
    if (std::holds_alternative<hstd::Str>(in.source)) {
        out->set_source_text(std::get<hstd::Str>(in.source));
    } else {
        hstd::serde::write_serde(
            out->mutable_constraint(),
            std::get<hstd::SPtr<kiwi_ir::ConstraintBase>>(in.source));
    }

    out->clear_lowered();

    for (kiwi_ir::Constraint const& constraint : in.lowered) {
        hstd::serde::write_serde(out->add_lowered(), constraint);
    }
}

void hstd::serde::proto_serde<proto::ConstraintEntry, kiwi_ir::ConstraintEntry>::read(
    proto::ConstraintEntry const& in,
    kiwi_ir::ConstraintEntry*     out) {
    switch (in.source_case()) {
        case proto::ConstraintEntry::kSourceText: out->source = in.source_text(); break;

        case proto::ConstraintEntry::kConstraint: {
            hstd::SPtr<kiwi_ir::ConstraintBase> value;
            hstd::serde::read_serde(in.constraint(), &value);
            out->source = std::move(value);
            break;
        }

        case proto::ConstraintEntry::SOURCE_NOT_SET:
            throw std::domain_error("ConstraintEntry source is not set");
    }

    out->lowered.clear();
    out->lowered.reserve(in.lowered_size());

    for (proto::Constraint const& constraint : in.lowered()) {
        kiwi_ir::Expr       lhs(0.0);
        kiwi_ir::Expr       rhs(0.0);
        kiwi_ir::Constraint value(lhs, rhs, kiwi::OP_EQ);
        hstd::serde::read_serde(constraint, &value);
        out->lowered.push_back(std::move(value));
    }
}
