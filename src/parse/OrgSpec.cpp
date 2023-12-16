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


std::unique_ptr<OrgSpec> getOrgSpec() {
    const IntSet<OrgNodeKind> anyTime{
        org::StaticActiveTime,
        org::StaticInactiveTime,
        org::DynamicActiveTime,
        org::DynamicInactiveTime,
    };

    const OrgPattern timeSpecPattern = OrgPattern({
        Field(Range(0, N::Year), OrgPattern({org::RawText, org::Empty})),
        Field(Range(1, N::Day), OrgPattern({org::RawText, org::Empty})),
        Field(Range(2, N::Clock), OrgPattern({org::RawText, org::Empty})),
        Field(
            Range(3, N::Repeater), OrgPattern({org::RawText, org::Empty})),
    });

    return std::make_unique<OrgSpec>(Vec<SpecPair>{
        SpecPair{org::StaticActiveTime, timeSpecPattern},
        SpecPair{org::StaticInactiveTime, timeSpecPattern},
        SpecPair{
            org::Subtree,
            OrgPattern({
                Field(
                    Range(0, N::Prefix)
                        .doc("Starting prefix of the subtree"),
                    OrgPattern(org::RawText)),
                Field(
                    Range(1, N::Todo)
                        .doc("Optional TODO state of the subtree"),
                    OrgPattern({org::BigIdent, org::Empty})),
                Field(
                    Range(2, N::Urgency)
                        .doc("Optional urgency marker for the subtree"),
                    OrgPattern({org::UrgencyStatus, org::Empty})),
                Field(
                    Range(3, N::Title)
                        .doc("Paragraph of text -- title of the subtree"),
                    OrgPattern(org::Paragraph)),
                Field(
                    Range(4, N::Completion)
                        .doc("Cumulative or direct completion of the "
                             "nested "
                             "tree elements"),
                    OrgPattern({org::Completion, org::Empty})),
                Field(
                    Range(5, N::Tags).doc("Trailing list of hashtags"),
                    OrgPattern({org::InlineStmtList, org::Empty})),
                Field(
                    Range(6, N::Times)
                        .doc(
                            "Scheduled, closed, and/or deadline times for "
                            "the subtree"),
                    OrgPattern(org::StmtList)),
                Field(
                    Range(7, N::Drawer)
                        .doc("Logbook, properties, description"),
                    OrgPattern(org::Drawer)),
                Field(
                    Range(8, N::Body)
                        .doc("Statement list of the nested nodes"),
                    OrgPattern(org::StmtList)),
            })},
        SpecPair{
            org::HashTag,
            OrgPattern({
                Field(
                    Range(0, N::Head)
                        .doc("First item in the hash tag name: #tag"),
                    OrgPattern(org::BigIdent)),
                Field(
                    Range(slice(1, 1_B), N::Subnodes)
                        .doc("Zero or more nested elements for nested tag "
                             "path"),
                    OrgPattern(org::HashTag)),
            })},
        SpecPair{
            org::Drawer,
            OrgPattern({
                Field(
                    Range(0, N::Properties)
                        .doc("Optional list of properties"),
                    OrgPattern({org::PropertyList, org::Empty})),
                Field(
                    Range(1, N::Logbook)
                        .doc(
                            "Optional list of log entries attached to the "
                            "subtree"),
                    OrgPattern({org::Logbook, org::Empty})),
                Field(
                    Range(2, N::Description)
                        .doc("Optional subtree description paragraph"),
                    OrgPattern({org::SubtreeDescription, org::Empty})),
            })},
        SpecPair{
            org::SubtreeDescription,
            OrgPattern(
                {Field(Range(0, N::Text), OrgPattern(org::Paragraph))})},
        SpecPair{
            org::AnnotatedParagraph,
            OrgPattern({
                Field(
                    Range(0, N::Prefix),
                    OrgPattern(
                        {org::ListTag,
                         org::Footnote,
                         org::AdmonitionTag})),
                Field(
                    Range(1, N::Body),
                    OrgPattern({org::Paragraph, org::Empty})),
            })},

        // Subtree logbook components
        SpecPair{
            org::Logbook,
            OrgPattern({
                Field(
                    Range(slice(0, 1_B), N::Logs),
                    OrgPattern({org::LogbookEntry, org::LogbookClock})),
            })},
        // Time clocking
        SpecPair{
            org::LogbookClock,
            OrgPattern({
                Field(
                    Range(0, N::Time),
                    OrgPattern(
                        anyTime + IntSet<OrgNodeKind>{org::TimeRange})),
            })},
        // Additional annotation logs
        SpecPair{
            // Main wrapper for all entires
            org::LogbookEntry,
            OrgPattern({
                Field(
                    Range(0, N::Header).doc("Main logbook entry header"),
                    OrgPattern({
                        org::LogbookTagChange,
                        org::LogbookNote,
                        org::LogbookStateChange,
                        org::LogbookRefile,
                    })),
                Field(
                    Range(1, N::Description)
                        .doc("Additional annotation or the description of "
                             "the transition"),
                    OrgPattern({
                        org::StmtList,
                        org::Empty,
                    })),
            })},
        SpecPair{
            org::LogbookTagChange,
            OrgPattern({
                Field(
                    Range(0, N::Tag).doc("Target tag"),
                    OrgPattern(org::HashTag)),
                Field(
                    Range(1, N::State).doc("Tag change action name"),
                    OrgPattern(org::Word)),
                Field(
                    Range(2, N::Time).doc("Time transition took place"),
                    OrgPattern(org::StaticInactiveTime)),
            })},
        SpecPair{
            org::LogbookStateChange,
            OrgPattern({
                Field(
                    Range(0, N::Newstate)
                        .doc("State that subtree was transitioned from"),
                    OrgPattern({org::BigIdent, org::Empty})),
                Field(
                    Range(1, N::Oldstate)
                        .doc("State that subtree was transitioned to"),
                    OrgPattern({org::BigIdent, org::Empty})),
                Field(
                    Range(2, N::Time).doc("Transition time"),
                    OrgPattern(anyTime + IntSet<OrgNodeKind>{org::Empty})),
                Field(
                    Range(3, N::Text)
                        .doc("Additional optional annotations for the "
                             "state "
                             "transition entry"),
                    OrgPattern({org::StmtList, org::Empty})),
            })},
        SpecPair{
            org::LogbookRefile,
            OrgPattern({
                Field(
                    Range(0, N::Time).doc("Time when refiling took place"),
                    OrgPattern(anyTime)),
                Field(
                    Range(1, N::From)
                        .doc("Link of the original subtree that was "
                             "refiled "
                             "from"),
                    OrgPattern(org::Link)),
                Field(
                    Range(2, N::Text)
                        .doc("Optional annotation for the refiling "
                             "transition"),
                    OrgPattern({org::StmtList, org::Empty})),
            })},
        SpecPair{
            org::LogbookNote,
            OrgPattern({
                Field(Range(0, N::Time), OrgPattern(anyTime)),
                Field(
                    Range(1, N::Text),
                    OrgPattern({org::StmtList, org::Empty})),
            })},
        // Inline node kinds
        SpecPair{
            org::CallCode,
            OrgPattern({
                Field(Range(0, N::Name), OrgPattern(org::Ident)),
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
            org::SrcInlineCode,
            OrgPattern({
                Field(
                    Range(0, N::Lang),
                    OrgPattern({org::Ident, org::Empty})),
                Field(
                    Range(1, N::HeaderArgs),
                    OrgPattern({org::CmdArguments, org::Empty})),
                Field(Range(2, N::Body), OrgPattern(org::CodeLine)),
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
                Field(
                    Range(1, N::Values),
                    {OrgPattern(org::InlineStmtList)
                         .sub({Field(
                             Range(slice(0, 1_B), N::Value),
                             OrgPattern(org::CmdValue))})}),
            })},
        SpecPair{
            org::CmdValue,
            OrgPattern(
                {Field(Range(0, N::Name)), Field(Range(1, N::Value))}),
        },
        SpecPair{
            org::AssocStmtList,
            OrgPattern(
                {Field(Range(0, N::Assoc)), Field(Range(1, N::Main))})},
        SpecPair{
            org::Result,
            OrgPattern(
                {Field(Range(0, N::Hash)), Field(Range(1, N::Body))})},
        SpecPair{
            org::ListItem,
            OrgPattern({
                Field(Range(0, N::Bullet)
                          .doc("list prefix - either dash/plus/star (for "
                               "unordered lists), or `<idx>.`/`<name>.`")),
                Field(Range(1, N::Counter)),

                Field(
                    Range(2, N::Checkbox).doc("optional checkbox"),
                    OrgPattern({org::Checkbox, org::Empty})),
                Field(
                    Range(3, N::Header).doc("Header part of the list"),
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
                    OrgPattern({org::StmtList, org::Empty})),
            })},
        SpecPair{
            org::TimeAssoc,
            OrgPattern({
                Field(
                    Range(0, N::Name),
                    OrgPattern({org::BigIdent, org::Empty})),
                Field(
                    Range(1, N::Time),
                    OrgPattern(
                        anyTime + IntSet<OrgNodeKind>{org::TimeRange})),
            })},
        SpecPair{
            org::TimeRange,
            OrgPattern({
                Field(Range(0, N::From), OrgPattern(anyTime)),
                Field(Range(1, N::To), OrgPattern(anyTime)),
                Field(
                    Range(2, N::Diff),
                    OrgPattern({org::SimpleTime, org::Empty})),
            })},

        SpecPair{
            org::PropertyList,
            OrgPattern({
                Field(
                    Range(slice(0, 1_B), N::Property),
                    OrgPattern(org::Property)),
            })},
        SpecPair{
            org::TableRow,
            OrgPattern({
                Field(
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
                        OrgPattern(org::TableCell))})),
            })},
        SpecPair{
            org::Property,
            OrgPattern({
                Field(
                    Range(0, N::InheritanceMode),
                    OrgPattern({org::Empty, org::Punctuation})),
                Field(Range(1, N::Name), OrgPattern(org::RawText)),
                Field(
                    Range(2, N::MainSetRule),
                    OrgPattern({org::Empty, org::Punctuation})),
                Field(
                    Range(3, N::Subname),
                    OrgPattern({org::Empty, org::Ident})),
                Field(
                    Range(4, N::SubSetRule),
                    OrgPattern({org::Empty, org::Punctuation})),
                Field(Range(5, N::Values), OrgPattern(org::RawText)),
            })},
        SpecPair{
            org::MultilineCommand,
            OrgPattern(
                {Field(Range(0, N::Name), OrgPattern(org::Ident)),
                 Field(
                     Range(1, N::Args),
                     OrgPattern({org::CmdArguments, org::Empty})),
                 Field(Range(2, N::Body))})},
        SpecPair{
            org::MetaSymbol,
            OrgPattern({
                Field(Range(0, N::Name), OrgPattern(org::Ident)),
                Field(
                    Range(1, N::Args),
                    OrgPattern({org::CmdArguments, org::Empty})),
                Field(Range(2, N::Body), OrgPattern(org::RawText)),
            })},
        SpecPair{
            org::Table,
            OrgPattern({
                Field(
                    Range(0, N::Args),
                    OrgPattern({org::CmdArguments, org::Empty})),
                Field(
                    Range(slice(1, 1_B), N::Rows),
                    OrgPattern(org::TableRow)),
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
                Field(Range(0, N::Name), OrgPattern(org::Ident)),
                Field(
                    Range(1, N::Args),
                    OrgPattern({org::CmdArguments, org::Empty})),
            })},
        SpecPair{
            org::CommandCaption,
            OrgPattern({
                Field(
                    Range(0, N::Args),
                    OrgPattern({OrgPattern({
                        Field(
                            Range(0, N::Text), OrgPattern(org::Paragraph)),
                    })})),
                Field(Range(1, N::Body), OrgPattern(org::StmtList)),
            })},
        SpecPair{
            org::BlockExport,
            OrgPattern({
                Field(Range(0, N::Name), OrgPattern(org::Ident)),
                Field(
                    Range(1, N::Args),
                    OrgPattern({org::Empty, org::CmdArguments})),
                Field(Range(2, N::Body), OrgPattern(org::RawText)),
            })},
        SpecPair{
            org::CommandInclude,
            OrgPattern({Field(
                Range(0, N::Args),
                OrgPattern({OrgPattern({
                    Field(Range(0, N::File), OrgPattern(org::File)),
                    Field(
                        Range(1, N::Kind),
                        OrgPattern({org::Empty, org::Ident})),
                    Field(
                        Range(2, N::Lang),
                        OrgPattern({org::Empty, org::Ident})),
                    Field(
                        Range(3, N::Args),
                        OrgPattern({org::Empty, org::CmdArguments})),
                })}))})},
        SpecPair{
            org::SrcCode,
            OrgPattern({
                Field(
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
                    OrgPattern({org::RawText, org::Empty})),
            })},
        SpecPair{
            org::Footnote,
            OrgPattern(
                {Field(Range(0, N::Name)),
                 Field(Range(1, N::Definition))})},
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
            OrgPattern({
                Field(
                    Range(slice(0, 1_B), N::Chunks),
                    OrgPattern(
                        {org::CodeText,
                         org::CodeTangle,
                         org::CodeCallout,
                         org::Empty})),
            })},
        SpecPair{
            org::Link,
            OrgPattern(
                {Field(Range(0, N::Protocol)),
                 Field(Range(1, N::Link)),
                 Field(Range(2, N::Desc))})}

        //
    });
}
