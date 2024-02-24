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


Field idxField(int idx, N name, OrgPattern const& pattern) {
    return Field(Range(idx, name), pattern);
}


template <typename Idx>
Field field1(Idx idx, N name, OrgNodeKind const& pattern, Str doc = "") {
    return Field(Range(idx, name).doc(doc), OrgPattern(pattern));
}

template <typename Idx>
Field fieldN(
    Idx           idx,
    N             name,
    OrgSet const& pattern = OrgSet{},
    Str           doc     = "") {
    return Field(Range(idx, name).doc(doc), OrgPattern(pattern));
}

template <typename Idx>
Field fieldN(Idx idx, N name, OrgPattern const& pattern, Str doc = "") {
    return Field(Range(idx, name).doc(doc), pattern);
}

std::unique_ptr<OrgSpec> getOrgSpec() {
    const IntSet<OrgNodeKind> anyTime{
        org::StaticActiveTime,
        org::StaticInactiveTime,
        org::DynamicActiveTime,
        org::DynamicInactiveTime,
    };

    const OrgPattern timeSpecPattern = OrgPattern({
        fieldN(0, N::Year, {org::RawText, org::Empty}),
        fieldN(1, N::Clock, {org::RawText, org::Empty}),
        fieldN(2, N::Zone, {org::RawText, org::Empty}),
        fieldN(3, N::Repeater, {org::RawText, org::Empty}),
    });

    const OrgPattern rawTextCmdPattern = OrgPattern({
        field1(0, N::Name, org::RawText),
        field1(1, N::Args, org::RawText),
    });

    const OrgPattern parTextCmdPattern = OrgPattern({
        Field(
            Range(0, N::Args),
            OrgPattern({OrgPattern({
                Field(Range(0, N::Text), OrgPattern(org::Paragraph)),
            })})),
        Field(Range(1, N::Body), OrgPattern(org::StmtList)),
    });

    const OrgPattern anySubnodePattern = OrgPattern(
        {Field(Range(slice(0, 1_B), N::Body))});

    return std::make_unique<OrgSpec>(Vec<SpecPair>{
        SpecPair{org::StaticActiveTime, timeSpecPattern},
        SpecPair{org::StaticInactiveTime, timeSpecPattern},
        SpecPair{
            org::Subtree,
            OrgPattern({
                field1(
                    0,
                    N::Prefix,
                    org::RawText,
                    "Starting prefix of the subtree"),
                fieldN(
                    1,
                    N::Todo,
                    {org::BigIdent, org::Empty},
                    "Optional TODO state of the subtree"),
                fieldN(
                    2,
                    N::Urgency,
                    {org::UrgencyStatus, org::Empty},
                    "Optional urgency marker for the subtree"),
                field1(
                    3,
                    N::Title,
                    org::Paragraph,
                    "Paragraph of text -- title of the subtree"),
                fieldN(
                    4,
                    N::Completion,
                    {org::Completion, org::Empty},
                    "Cumulative or direct completion of the "
                    "nested "
                    "tree elements"),
                fieldN(
                    5,
                    N::Tags,
                    {org::InlineStmtList, org::Empty},
                    "Trailing list of hashtags"),
                field1(
                    6,
                    N::Times,
                    org::StmtList,
                    "Scheduled, closed, and/or deadline times for "
                    "the subtree"),
                field1(
                    7,
                    N::Drawer,
                    org::Drawer,
                    "Logbook, properties, description"),
                field1(
                    8,
                    N::Body,
                    org::StmtList,
                    "Statement list of the nested nodes"),
            })},
        SpecPair{
            org::HashTag,
            OrgPattern({
                fieldN(
                    0,
                    N::Head,
                    {org::BigIdent, org::Word, org::RawText},
                    "First item in the hash tag name: #tag"),
                field1(
                    slice(1, 1_B),
                    N::Subnodes,
                    org::HashTag,
                    "Zero or more nested elements for nested tag path"),
            })},
        SpecPair{
            org::Drawer,
            OrgPattern({
                fieldN(
                    0,
                    N::Properties,
                    {org::PropertyList, org::Empty},
                    "Optional list of properties"),
                fieldN(
                    1,
                    N::Logbook,
                    {org::Logbook, org::Empty},
                    "Optional list of log entries attached to the "
                    "subtree"),
                Field(
                    Range(2, N::Description)
                        .doc("Optional subtree description paragraph"),
                    OrgPattern({org::SubtreeDescription, org::Empty})),
            })},
        SpecPair{
            org::SubtreeDescription,
            OrgPattern({field1(0, N::Text, org::Paragraph)})},
        SpecPair{
            org::CenterBlock,
            OrgPattern({
                fieldN(0, N::Args, {org::CmdArguments, org::Empty}),
                fieldN(
                    slice(1, 1_B), N::Body, {org::Paragraph, org::Empty}),
            })},
        SpecPair{
            org::QuoteBlock,
            OrgPattern({
                fieldN(0, N::Args, {org::CmdArguments, org::Empty}),
                fieldN(
                    slice(1, 1_B), N::Body, {org::Paragraph, org::Empty}),
            })},
        SpecPair{
            org::Example,
            OrgPattern({
                fieldN(0, N::Args, {org::CmdArguments, org::Empty}),
                fieldN(slice(1, 1_B), N::Body, {org::RawText, org::Empty}),
            })},
        SpecPair{
            org::AnnotatedParagraph,
            OrgPattern({
                fieldN(
                    0,
                    N::Prefix,
                    {org::ListTag, org::Footnote, org::AdmonitionTag}),
                fieldN(1, N::Body, {org::Paragraph, org::Empty}),
            })},

        SpecPair{org::StmtList, anySubnodePattern},
        SpecPair{org::Paragraph, anySubnodePattern},
        SpecPair{org::InlineStmtList, anySubnodePattern},
        SpecPair{
            org::List,
            OrgPattern({
                fieldN(slice(0, 1_B), N::Body, OrgSet{org::ListItem}),
            })},
        // Subtree logbook components
        SpecPair{
            org::Logbook,
            OrgPattern({
                fieldN(0, N::Logs, OrgSet{org::List}),
            })},
        // Inline node kinds
        SpecPair{
            org::InlineCallCode,
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
            OrgPattern({fieldN(0, N::Name), fieldN(1, N::Value)})},
        SpecPair{
            org::AssocStmtList,
            OrgPattern({fieldN(0, N::Assoc), fieldN(1, N::Main)})},
        SpecPair{
            org::Result,
            OrgPattern({fieldN(0, N::Hash), fieldN(1, N::Body)})},
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
                fieldN(0, N::Name, {org::BigIdent, org::Empty}),
                fieldN(
                    1,
                    N::Time,
                    anyTime + IntSet<OrgNodeKind>{org::TimeRange}),
            })},
        SpecPair{
            org::TimeRange,
            OrgPattern({
                fieldN(0, N::From, anyTime),
                fieldN(1, N::To, anyTime),
                fieldN(2, N::Diff, {org::SimpleTime, org::Empty}),
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
                field1(0, N::Name, org::RawText),
                field1(1, N::Values, org::RawText),
            })},
        SpecPair{
            org::MultilineCommand,
            OrgPattern(
                {field1(0, N::Name, org::Ident),
                 fieldN(1, N::Args, {org::CmdArguments, org::Empty}),
                 Field(Range(2, N::Body))})},
        SpecPair{
            org::MetaSymbol,
            OrgPattern({
                field1(0, N::Name, org::Ident),
                fieldN(1, N::Args, {org::CmdArguments, org::Empty}),
                field1(2, N::Body, org::RawText),
            })},
        SpecPair{
            org::Table,
            OrgPattern({
                fieldN(0, N::Args, {org::CmdArguments, org::Empty}),
                Field(
                    Range(slice(1, 1_B), N::Rows),
                    OrgPattern(org::TableRow)),
            })},
        SpecPair{
            org::TableCell,
            OrgPattern({
                fieldN(0, N::Args, {org::CmdArguments, org::Empty}),
                fieldN(1, N::Text, {org::Empty, org::StmtList}),
            })},
        SpecPair{org::CommandTitle, parTextCmdPattern},
        SpecPair{org::CommandCaption, parTextCmdPattern},
        SpecPair{
            org::CmdPropertyText,
            OrgPattern({
                field1(0, N::Name, org::RawText),
                Field(
                    Range(1, N::Args),
                    OrgPattern({OrgPattern({
                        field1(0, N::Text, org::Paragraph),
                    })})),
                field1(2, N::Body, org::StmtList),
            })},
        SpecPair{
            org::CmdPropertyArgs,
            OrgPattern({
                field1(0, N::Name, org::RawText),
                fieldN(1, N::Args, {org::CmdArguments, org::Empty}),
                field1(2, N::Body, org::StmtList),
            })},
        SpecPair{
            org::Command,
            OrgPattern({
                field1(0, N::Name, org::Ident),
                fieldN(1, N::Args, {org::CmdArguments, org::Empty}),
            })},
        SpecPair{
            org::BlockExport,
            OrgPattern({
                field1(0, N::Name, org::Ident),
                fieldN(1, N::Args, {org::Empty, org::CmdArguments}),
                Field(
                    Range(2, N::Body),
                    OrgPattern(org::StmtList)
                        .sub({Field(
                            Range(slice(0, 1_B), N::Lines),
                            OrgPattern(org::RawText))})),
            })},
        SpecPair{
            org::CommandInclude,
            OrgPattern({Field(
                Range(0, N::Args),
                OrgPattern({OrgPattern({
                    field1(0, N::File, org::File),
                    fieldN(1, N::Kind, {org::Empty, org::Ident}),
                    fieldN(2, N::Lang, {org::Empty, org::Ident}),
                    fieldN(3, N::Args, {org::Empty, org::CmdArguments}),
                })}))})},
        SpecPair{
            org::SrcCode,
            OrgPattern({
                fieldN(0, N::Lang, {org::Ident, org::Empty}),
                fieldN(1, N::HeaderArgs, {org::CmdArguments, org::Empty}),
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
            org::CommandArguments,
            OrgPattern({
                fieldN(
                    slice(0, 1_B),
                    N::Args,
                    {org::CmdKey,
                     org::CmdValue,
                     org::RawText,
                     org::Empty}),
            })},

        SpecPair{
            org::Footnote,
            OrgPattern(
                {Field(Range(0, N::Name)),
                 Field(Range(1, N::Definition))})},
        SpecPair{
            org::InlineFootnote,
            OrgPattern({Field(Range(0, N::Definition))})},
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

        ,
        SpecPair{
            org::Symbol,
            OrgPattern({
                field1(0, N::Name, org::Ident),
                fieldN(
                    1,
                    N::Args,
                    OrgPattern(
                        {field1(slice(0, 1_B), N::Args, org::RawText)})),
                fieldN(
                    2,
                    N::Body,
                    OrgPattern(
                        {field1(slice(0, 1_B), N::Args, org::Paragraph)})),
            })},
        SpecPair{
            org::Macro,
            OrgPattern({
                fieldN(0, N::Name),
                // fieldN(
                //     1,
                //     N::Args,
                //     OrgPattern(
                //         {field1(slice(0, 1_B), N::Args,
                //         org::RawText)})),
                // fieldN(
                //     2,
                //     N::Body,
                //     OrgPattern(
                //         {field1(slice(0, 1_B), N::Args,
                //         org::Paragraph)})),
            })},
        SpecPair{org::Angle, OrgPattern({fieldN(0, N::Body)})},
        SpecPair{org::Bold, OrgPattern({fieldN(slice(0, 1_B), N::Body)})},
        SpecPair{
            org::Italic, OrgPattern({fieldN(slice(0, 1_B), N::Body)})},
        SpecPair{
            org::Verbatim, OrgPattern({fieldN(slice(0, 1_B), N::Body)})},
        SpecPair{
            org::Strike, OrgPattern({fieldN(slice(0, 1_B), N::Body)})},
        SpecPair{
            org::Underline, OrgPattern({fieldN(slice(0, 1_B), N::Body)})},
        SpecPair{
            org::Monospace,
            OrgPattern({field1(slice(0, 1_B), N::Body, org::RawText)})},
        //
    });
}
