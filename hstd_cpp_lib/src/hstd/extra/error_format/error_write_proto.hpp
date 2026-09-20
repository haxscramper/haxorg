#pragma once

#if ORG_BUILD_WITH_PROTOBUF

#    include "hstd/ext/error_write.hpp"
#    include "src/hstd/ext/error_write.pb.h"
#    include <hstd_cpp_lib/ext/hstd_serde.hpp>

namespace hstd::serde {

namespace error_write_proto = hstd::ext::error_write;

template <>
struct proto_serde<error_write_proto::TermColorFg8Bit, hstd::TermColorFg8Bit> {
    static void write(
        error_write_proto::TermColorFg8Bit* out,
        hstd::TermColorFg8Bit const&        in);

    static void read(
        error_write_proto::TermColorFg8Bit const& in,
        hstd::TermColorFg8Bit*                    out);
};

template <>
struct proto_serde<error_write_proto::TermColorBg8Bit, hstd::TermColorBg8Bit> {
    static void write(
        error_write_proto::TermColorBg8Bit* out,
        hstd::TermColorBg8Bit const&        in);

    static void read(
        error_write_proto::TermColorBg8Bit const& in,
        hstd::TermColorBg8Bit*                    out);
};

template <>
struct proto_serde<error_write_proto::Style, hstd::Style> {
    static void write(error_write_proto::Style* out, hstd::Style const& in);

    static void read(error_write_proto::Style const& in, hstd::Style* out);
};

template <>
struct proto_serde<error_write_proto::ColStyle, hstd::ColStyle> {
    static void write(error_write_proto::ColStyle* out, hstd::ColStyle const& in);

    static void read(error_write_proto::ColStyle const& in, hstd::ColStyle* out);
};

template <>
struct proto_serde<error_write_proto::ColRune, hstd::ColRune> {
    static void write(error_write_proto::ColRune* out, hstd::ColRune const& in);

    static void read(error_write_proto::ColRune const& in, hstd::ColRune* out);
};

template <>
struct proto_serde<error_write_proto::ColText, hstd::ColText> {
    static void write(error_write_proto::ColText* out, hstd::ColText const& in);

    static void read(error_write_proto::ColText const& in, hstd::ColText* out);
};

template <>
struct proto_serde<error_write_proto::ReportSourceId, hstd::ext::ReportSourceId> {
    static void write(
        error_write_proto::ReportSourceId* out,
        hstd::ext::ReportSourceId const&   in);

    static void read(
        error_write_proto::ReportSourceId const& in,
        hstd::ext::ReportSourceId*               out);
};

template <>
struct proto_serde<error_write_proto::ReportLabelId, hstd::ext::ReportLabelId> {
    static void write(
        error_write_proto::ReportLabelId* out,
        hstd::ext::ReportLabelId const&   in);

    static void read(
        error_write_proto::ReportLabelId const& in,
        hstd::ext::ReportLabelId*               out);
};

template <>
struct proto_serde<error_write_proto::IntSlice, hstd::Slice<int>> {
    static void write(error_write_proto::IntSlice* out, hstd::Slice<int> const& in);

    static void read(error_write_proto::IntSlice const& in, hstd::Slice<int>* out);
};

template <>
struct proto_serde<error_write_proto::CodeSpan, hstd::ext::CodeSpan> {
    static void write(error_write_proto::CodeSpan* out, hstd::ext::CodeSpan const& in);

    static void read(error_write_proto::CodeSpan const& in, hstd::ext::CodeSpan* out);
};

template <>
struct proto_serde<error_write_proto::ReportSourceCache, hstd::ext::ReportSourceCache> {
    static void write(
        error_write_proto::ReportSourceCache* out,
        hstd::ext::ReportSourceCache const&   in);

    static void read(
        error_write_proto::ReportSourceCache const& in,
        hstd::ext::ReportSourceCache*               out);
};

template <>
struct proto_serde<error_write_proto::ReportSourceLine, hstd::ext::ReportSourceLine> {
    static void write(
        error_write_proto::ReportSourceLine* out,
        hstd::ext::ReportSourceLine const&   in);

    static void read(
        error_write_proto::ReportSourceLine const& in,
        hstd::ext::ReportSourceLine*               out);
};

template <>
struct proto_serde<
    error_write_proto::ReportSource::OffsetLine,
    hstd::ext::ReportSource::OffsetLine> {
    static void write(
        error_write_proto::ReportSource::OffsetLine* out,
        hstd::ext::ReportSource::OffsetLine const&   in);

    static void read(
        error_write_proto::ReportSource::OffsetLine const& in,
        hstd::ext::ReportSource::OffsetLine*               out);
};

template <>
struct proto_serde<error_write_proto::ReportSource, hstd::ext::ReportSource> {
    static void write(
        error_write_proto::ReportSource* out,
        hstd::ext::ReportSource const&   in);

    static void read(
        error_write_proto::ReportSource const& in,
        hstd::ext::ReportSource*               out);
};

template <>
struct proto_serde<
    error_write_proto::ReportSourceStrCache,
    hstd::ext::ReportSourceStrCache> {
    static void write(
        error_write_proto::ReportSourceStrCache* out,
        hstd::ext::ReportSourceStrCache const&   in);

    static void read(
        error_write_proto::ReportSourceStrCache const& in,
        hstd::ext::ReportSourceStrCache*               out);
};

template <>
struct proto_serde<error_write_proto::ReportCharacters, hstd::ext::ReportCharacters> {
    static void write(
        error_write_proto::ReportCharacters* out,
        hstd::ext::ReportCharacters const&   in);

    static void read(
        error_write_proto::ReportCharacters const& in,
        hstd::ext::ReportCharacters*               out);
};

template <>
struct proto_serde<error_write_proto::ReportLabel, hstd::ext::ReportLabel> {
    static void write(
        error_write_proto::ReportLabel* out,
        hstd::ext::ReportLabel const&   in);

    static void read(
        error_write_proto::ReportLabel const& in,
        hstd::ext::ReportLabel*               out);
};

template <>
struct proto_serde<error_write_proto::LabelInfo, hstd::ext::LabelInfo> {
    static void write(error_write_proto::LabelInfo* out, hstd::ext::LabelInfo const& in);

    static void read(error_write_proto::LabelInfo const& in, hstd::ext::LabelInfo* out);
};

template <>
struct proto_serde<error_write_proto::SourceGroup, hstd::ext::SourceGroup> {
    static void write(
        error_write_proto::SourceGroup* out,
        hstd::ext::SourceGroup const&   in);

    static void read(
        error_write_proto::SourceGroup const& in,
        hstd::ext::SourceGroup*               out);
};

template <>
struct proto_serde<error_write_proto::ReportRenderConfig, hstd::ext::ReportRenderConfig> {
    static void write(
        error_write_proto::ReportRenderConfig* out,
        hstd::ext::ReportRenderConfig const&   in);

    static void read(
        error_write_proto::ReportRenderConfig const& in,
        hstd::ext::ReportRenderConfig*               out);
};

template <>
struct proto_serde<error_write_proto::Report, hstd::ext::Report> {
    static void write(error_write_proto::Report* out, hstd::ext::Report const& in);

    static void read(error_write_proto::Report const& in, hstd::ext::Report* out);
};


} // namespace hstd::serde

#endif
