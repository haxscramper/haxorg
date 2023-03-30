#include <parse/OrgSpec.hpp>

using org        = OrgNodeKind;
using otk        = OrgTokenKind;
using OrgPattern = astspec::
    AstPattern<OrgAdapter, OrgNodeKind, OrgSpecName>;
using SpecPair = Pair<org, OrgPattern>;
using Field    = astspec::
    AstPatternRange<OrgAdapter, OrgNodeKind, OrgSpecName>;
using Range = astspec::AstRange<OrgSpecName>;

using N = OrgSpecName;

OrgSpec spec = OrgSpec(Vec<SpecPair>{
    SpecPair{
        org::Subtree,
        OrgPattern(
            {Field(Range(0, N::Prefix), OrgPattern(org::RawText)),
             Field(
                 Range(1, N::Todo),
                 OrgPattern({org::BigIdent, org::Empty})),
             Field(
                 Range(2, N::Urgency),
                 OrgPattern({org::UrgencyStatus, org::Empty})),
             Field(Range(3, N::Title), OrgPattern(org::Paragraph)),
             Field(
                 Range(4, N::Completion),
                 OrgPattern({org::Completion, org::Empty}))})},
    SpecPair{
        org::HashTag,
        OrgPattern(
            {Field(Range(0, N::Head), OrgPattern(org::BigIdent)),
             Field(
                 Range(slice(1, 1_B), N::Subnodes),
                 OrgPattern(org::HashTag))})},
    SpecPair{
        org::Drawer,
        OrgPattern(
            {Field(
                 Range(0, N::Properties),
                 OrgPattern({org::PropertyList, org::Empty})),
             Field(
                 Range(1, N::Logbook),
                 OrgPattern({org::Logbook, org::Empty})),
             Field(
                 Range(2, N::Description),
                 OrgPattern({org::SubtreeDescription, org::Empty}))})},
    SpecPair{
        org::SubtreeDescription,
        OrgPattern(
            {Field(Range(0, N::Text), OrgPattern(org::Paragraph))})},
    SpecPair{
        org::AnnotatedParagraph,
        OrgPattern(
            {Field(
                 Range(0, N::Prefix),
                 OrgPattern(
                     {org::ListTag, org::Footnote, org::AdmonitionTag})),
             Field(
                 Range(1, N::Body),
                 OrgPattern({org::Paragraph, org::Empty}))})},
    SpecPair{
        org::Logbook,
        OrgPattern({Field(
            Range(slice(0, 1_B), N::Logs),
            OrgPattern(
                {org::LogbookStateChange,
                 org::LogbookNote,
                 org::LogbookRefile,
                 org::LogbookClock}))})},
    SpecPair{
        org::LogbookStateChange,
        OrgPattern(
            {Field(
                 Range(0, N::Newstate),
                 OrgPattern({org::BigIdent, org::Empty})),
             Field(
                 Range(1, N::Oldstate),
                 OrgPattern({org::BigIdent, org::Empty})),
             Field(
                 Range(2, N::Time),
                 OrgPattern({org::TimeStamp, org::Empty})),
             Field(
                 Range(3, N::Text),
                 OrgPattern({org::StmtList, org::Empty}))})},
    SpecPair{
        org::LogbookRefile,
        OrgPattern({
            Field(Range(0, N::Time), OrgPattern(org::TimeStamp)),
            Field(Range(1, N::From), OrgPattern(org::Link)),
            Field(
                Range(2, N::Text),
                OrgPattern({org::StmtList, org::Empty})),
        })},
    SpecPair{
        org::CallCode,
        OrgPattern({
            Field(Range(0, N::Name), OrgPattern({org::Ident})),
            Field(
                Range(1, N::HeaderArgs),
                OrgPattern({org::CmdArguments, org::Empty})),
            Field(Range(2, N::Args)),
            Field(Range(3, N::EndArgs)),
            Field(
                Range(4, N::Result),
                OrgPattern({org::RawText, org::Empty})),
        })},
    SpecPair{
        org::LogbookNote,
        OrgPattern({
            Field(Range(0, N::Time), OrgPattern(org::TimeStamp)),
            Field(
                Range(1, N::Text),
                OrgPattern({org::StmtList, org::Empty})),
        })},
    SpecPair{
        org::SrcInlineCode,
        OrgPattern({
            Field(Range(0, N::Lang), OrgPattern({org::Ident, org::Empty})),
            Field(
                Range(1, N::HeaderArgs),
                OrgPattern({org::CmdArguments, org::Empty})),
            Field(Range(2, N::Body), OrgPattern({org::CodeLine})),
            Field(
                Range(3, N::Result),
                OrgPattern({org::RawText, org::Empty})),
        })},
    SpecPair{
        org::CmdArguments,
        OrgPattern({
            Field(
                Range(0, N::Flags),
                {OrgPattern(org::InlineStmtList)
                     .sub({Field(
                         Range(slice(0, 1_B), N::Flags),
                         OrgPattern(org::CmdFlag))})}),
        })},
    SpecPair{
        org::CmdValue,
        OrgPattern({Field(Range(0, N::Name)), Field(Range(1, N::Value))}),
    },
    SpecPair{
        org::AssocStmtList,
        OrgPattern({Field(Range(0, N::Assoc)), Field(Range(1, N::Main))})},
    SpecPair{
        org::Result,
        OrgPattern({Field(Range(0, N::Hash)), Field(Range(1, N::Body))})},
    SpecPair{
        org::ListItem,
        OrgPattern(
            {Field(Range(0, N::Bullet)
                       .doc("list prefix - either dash/plus/star (for "
                            "unordered lists), or `<idx>.`/`<name>.`")),
             Field(Range(1, N::Counter)),

             Field(
                 Range(2, N::Checkbox).doc("optional checkbox"),
                 OrgPattern({org::Checkbox, org::Empty})),
             Field(
                 Range(3, N::Header).doc("Main part of the list"),
                 OrgPattern(
                     {org::Paragraph,
                      org::AnnotatedParagraph,
                      org::Empty})),
             Field(
                 Range(4, N::Completion)
                     .doc("Cumulative completion progress for all "
                          "subnodes"),
                 OrgPattern({org::Completion, org::Empty})),
             Field(
                 Range(5, N::Body)
                     .doc("Additional list items - more sublists, "
                          "extended N::Body (with code blocks, extra "
                          "parargaphs etc.)"),
                 OrgPattern({org::StmtList, org::Empty}))})},
    SpecPair{
        org::TimeAssoc,
        OrgPattern({
            Field(
                Range(0, N::Name),
                OrgPattern({org::BigIdent, org::Empty})),
            Field(
                Range(1, N::Time),
                OrgPattern({org::TimeStamp, org::TimeRange})),
        })},
    SpecPair{
        org::LogbookClock,
        OrgPattern({
            Field(
                Range(0, N::Time),
                OrgPattern({org::TimeRange, org::TimeStamp})),
        })},
    SpecPair{
        org::TimeRange,
        OrgPattern({
            Field(Range(0, N::From), OrgPattern({org::TimeStamp})),
            Field(Range(1, N::To), OrgPattern({org::TimeStamp})),
            Field(
                Range(2, N::Diff),
                OrgPattern({org::SimpleTime, org::Empty})),
        })},

    SpecPair{
        org::PropertyList,
        OrgPattern({Field(
            Range(slice(0, 1_B), N::Property),
            OrgPattern({org::Property, org::PropertyAdd}))})},
    SpecPair{
        org::PropertyAdd,
        OrgPattern({
            Field(Range(0, N::Name), OrgPattern({org::RawText})),
            Field(
                Range(1, N::Subname),
                OrgPattern({org::Empty, org::Ident})),
            Field(Range(2, N::Values), OrgPattern({org::RawText})),
        })},
    SpecPair{
        org::TableRow,
        OrgPattern(
            {Field(
                 Range(0, N::Args)
                     .doc("N::Optional arguments for row - can be "
                          "specified using N::`#+row`. For pipe "
                          "formatting this is not supported, N::So "
                          "arguments would be an empty node."),
                 OrgPattern({org::CmdArguments, org::Empty})),
             Field(
                 Range(1, N::Text)
                     .doc("N::It is possible to put text on the* row* "
                          "level."),
                 OrgPattern({org::Paragraph, org::Empty})),
             Field(
                 Range(2, N::Body),
                 OrgPattern({Field(
                     Range(slice(0, 1_B), N::Cells),
                     OrgPattern(org::TableCell))}))})},
    SpecPair{
        org::Property,
        OrgPattern({
            Field(Range(0, N::Name), OrgPattern({org::RawText})),
            Field(
                Range(1, N::Subname),
                OrgPattern({org::Empty, org::Ident})),
            Field(Range(2, N::Values), OrgPattern({org::RawText})),
        })},
    SpecPair{
        org::MultilineCommand,
        OrgPattern(
            {Field(Range(0, N::Name), OrgPattern({org::Ident})),
             Field(
                 Range(1, N::Args),
                 OrgPattern({org::CmdArguments, org::Empty})),
             Field(Range(2, N::Body))})},
    SpecPair{
        org::MetaSymbol,
        OrgPattern({
            Field(Range(0, N::Name), OrgPattern({org::Ident})),
            Field(
                Range(1, N::Args),
                OrgPattern({org::CmdArguments, org::Empty})),
            Field(Range(2, N::Body), OrgPattern({org::RawText})),
        })},
    SpecPair{
        org::Table,
        OrgPattern({
            Field(
                Range(0, N::Args),
                OrgPattern({org::CmdArguments, org::Empty})),
            Field(
                Range(slice(1, 1_B), N::Rows),
                OrgPattern({org::TableRow})),
        })},
    SpecPair{
        org::TableCell,
        OrgPattern({
            Field(
                Range(0, N::Args),
                OrgPattern({org::CmdArguments, org::Empty})),
            Field(
                Range(1, N::Text),
                OrgPattern({org::Empty, org::StmtList})),
        })},
    SpecPair{
        org::Command,
        OrgPattern({
            Field(Range(0, N::Name), OrgPattern({org::Ident})),
            Field(
                Range(1, N::Args),
                OrgPattern({org::CmdArguments, org::Empty})),
        })},
    SpecPair{
        org::CommandCaption,
        OrgPattern({
            Field(Range(0, N::Text), OrgPattern({org::Paragraph})),
        })},
    SpecPair{
        org::CommandInclude,
        OrgPattern({
            Field(Range(0, N::File), OrgPattern({org::File})),
            Field(Range(1, N::Kind), OrgPattern({org::Empty, org::Ident})),
            Field(Range(2, N::Lang), OrgPattern({org::Empty, org::Ident})),
            Field(
                Range(3, N::Args),
                OrgPattern({org::Empty, org::CmdArguments})),
        })},
    SpecPair{
        org::SrcCode,
        OrgPattern(
            {Field(
                 Range(0, N::Lang),
                 OrgPattern({org::Ident, org::Empty})),
             Field(
                 Range(1, N::HeaderArgs),
                 OrgPattern({org::CmdArguments, org::Empty})),
             Field(
                 Range(2, N::Body),
                 OrgPattern(org::StmtList)
                     .sub({Field(
                         Range(slice(0, 1_B), N::Lines),
                         OrgPattern(org::CodeLine))})),
             Field(
                 Range(3, N::Result),
                 OrgPattern({org::RawText, org::Empty}))})},
    SpecPair{
        org::Footnote,
        OrgPattern(
            {Field(Range(0, N::Name)), Field(Range(1, N::Definition))})},
    SpecPair{
        org::CommandHeader,
        OrgPattern({
            Field(
                Range(0, N::Args),
                OrgPattern({org::Empty, org::CmdArguments})),
        })},
    SpecPair{
        org::CommandOptions,
        OrgPattern({Field(
            Range(slice(0, 1_B), N::Args),
            OrgPattern(org::RawText))})},
    SpecPair{
        org::CodeLine,
        OrgPattern({Field(
            Range(slice(0, 1_B), N::Chunks),
            OrgPattern(
                {org::CodeText,
                 org::CodeTangle,
                 org::CodeCallout,
                 org::Empty}))})},
    SpecPair{
        org::Link,
        OrgPattern(
            {Field(Range(0, N::Protocol)),
             Field(Range(1, N::Link)),
             Field(Range(2, N::Desc))})}

    //
});
