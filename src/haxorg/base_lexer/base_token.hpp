#pragma once

#include <haxorg/lexbase/Token.hpp>
#include <haxorg/sem/SemOrgEnums.hpp>
#include <hstd/system/reflection.hpp>

namespace org::parse {

struct OrgFill {
  private:
    // string value is necessary to support de-serialization
    // of the token text from enum.
    using StrValue = std::variant<hstd::StrView, hstd::Str>;
    using LocValue = hstd::Opt<org::parse::SourceLoc>;

    StrValue fill_text;

  public:
    hstd::Opt<org::parse::SourceLoc> loc;

    void setText(hstd::StrView view) { fill_text = view; }
    void setText(hstd::Str const& view) { fill_text = view; }

    bool empty() const { return text().empty(); }

    OrgFill(hstd::StrView const& view, LocValue const& value = std::nullopt)
        : fill_text{view}, loc{value} {}
    OrgFill(hstd::Str const& view, LocValue const& value = std::nullopt)
        : fill_text{view}, loc{value} {}

    hstd::StrView text() const {
        if (auto ptr = std::get_if<0>(&fill_text)) {
            return *ptr;
        } else {
            return std::get<1>(fill_text);
        }
    }

    OrgFill() {}

    bool isFake() const { return !loc.has_value(); }
    DESC_FIELDS(OrgFill, (text, loc));
};

using OrgToken   = Token<OrgTokenKind, OrgFill>;
using OrgTokenId = TokenId<OrgTokenKind, OrgFill>;

std::string format_token_location(
    org::parse::SourceManager const* mgr,
    OrgToken const&                  token);

std::string format_token(org::parse::SourceManager const* mgr, OrgToken const& token);


extern hstd::IntSet<OrgTokenKind> const OrgTokenCmdBlockClose;
extern hstd::IntSet<OrgTokenKind> const OrgTokenCmdBlockOpen;
extern hstd::IntSet<OrgTokenKind> const OrgTokenCmdBlockLine;

inline hstd::IntSet<OrgTokenKind> const OrgTokenLineEnd{
    OrgTokenKind::Newline,
    OrgTokenKind::MediumNewline,
    OrgTokenKind::LongNewline,
    OrgTokenKind::EndOfFile,
};

} // namespace org::parse


template <>
struct fmt::formatter<org::parse::OrgFill> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(org::parse::OrgFill const& p, fmt::format_context& ctx) const;
};
