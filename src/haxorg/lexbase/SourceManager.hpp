#pragma once
#pragma clang diagnostic ignored "-Wunknown-attributes"

#include <hstd/ext/bimap_wrap.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/stdlib/dod_base.hpp>

#if ORG_BUILD_WITH_PROTOBUF
#    include "src/haxorg/serde/OrgApiProto.pb.h"
#    include <hstd/ext/hstd_serde.hpp>
#endif

namespace org::parse {

DECL_ID_TYPE_MASKED_WITH_ATTR(
    SourceFile,
    SourceFileId,
    hstd::u32,
    0,
    [[refl(R"({"default-constructor": false})")]]);

struct SourceFile {
    using id_type = SourceFileId;
    std::string content;
    std::string path;
};

struct [[refl]] SourceManager {
    hstd::dod::Store<SourceFileId, SourceFile>               store;
    hstd::ext::Unordered1to1Bimap<std::string, SourceFileId> path_ids;

    [[refl]] std::string        getPath(SourceFileId const& id) const;
    [[refl]] SourceFileId       getId(std::string const& path) const;
    [[refl]] std::string const& getSourceContent(SourceFileId const& id) const;

    [[refl]] std::string const& getContentTextForPath(std::string const& path) const;

    [[refl]] SourceFileId addSource(std::string const& path, std::string const& content);
};


struct [[refl]] SourceLoc {
    [[refl]] int          line;
    [[refl]] int          column;
    [[refl]] SourceFileId file_id;
    [[refl]] int          pos = -1;

    bool operator==(SourceLoc const& other) const {
        return line == other.line && column == other.column && pos == other.pos
            && file_id == other.file_id;
    }

    bool isValid() const { return line != -1 && column != -1 && !file_id.isNil(); }

    BOOST_DESCRIBE_CLASS(SourceLoc, (), (line, column, pos, file_id), (), ());
};


} // namespace org::parse

namespace hstd {
template <>
struct SerdeDefaultProvider<org::parse::SourceLoc> {
    static org::parse::SourceLoc get() {
        return org::parse::SourceLoc{
            .line    = -1,
            .column  = -1,
            .file_id = org::parse::SourceFileId::Nil(),
        };
    }

    static void construct_at(void* ptr) { new (ptr) org::parse::SourceLoc(get()); };
};
} // namespace hstd

template <>
struct fmt::formatter<org::parse::SourceLoc> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(org::parse::SourceLoc const& p, fmt::format_context& ctx)
        const {
        return hstd::fmt_ctx(
            hstd::fmt("{}({}:{}:{})", p.file_id, p.line, p.column, p.pos), ctx);
    }
};

#if ORG_BUILD_WITH_PROTOBUF

template <>
struct hstd::serde::proto_serde<orgproto::SourceManager, org::parse::SourceManager> {
    static void write(orgproto::SourceManager* out, org::parse::SourceManager const& in);
    static void read(orgproto::SourceManager const& in, org::parse::SourceManager* out);
};

#endif
