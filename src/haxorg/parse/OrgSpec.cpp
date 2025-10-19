#include <haxorg/parse/OrgSpec.hpp>

using namespace hstd;
using namespace org::parse;

using otk        = OrgTokenKind;
using OrgPattern = org::parse::
    AstPattern<OrgAdapter, OrgNodeKind, OrgSpecName>;
using SpecPair = Pair<OrgNodeKind, OrgPattern>;
using Field    = org::parse::
    AstPatternRange<OrgAdapter, OrgNodeKind, OrgSpecName>;
using Range = org::parse::AstRange<OrgSpecName>;

using N   = OrgSpecName;
using onk = OrgNodeKind;

Field idxField(int idx, N name, OrgPattern const& pattern) {
    return Field(Range(idx, name), pattern);
}


template <typename Idx>
Field field1(Idx idx, N name, OrgNodeKind const& pattern, Str doc = "") {
    return Field(Range(idx, name).doc(doc), OrgPattern(pattern));
}

template <typename Idx>
Field field1(
    Idx           idx,
    N             name,
    OrgSet const& pattern = OrgSet{},
    Str           doc     = "") {
    return Field(Range(idx, name).doc(doc), OrgPattern(pattern));
}

template <typename Idx>
Field fieldN(Idx idx, N name, OrgNodeKind const& pattern, Str doc = "") {
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
        onk::StaticActiveTime,
        onk::StaticInactiveTime,
        onk::DynamicActiveTime,
        onk::DynamicInactiveTime,
    };

    const OrgPattern timeSpecPattern = OrgPattern({
        fieldN(0, N::Year, {onk::RawText, onk::Empty}),
        fieldN(1, N::Clock, {onk::RawText, onk::Empty}),
        fieldN(2, N::Zone, {onk::RawText, onk::Empty}),
        fieldN(3, N::Repeater, {onk::RawText, onk::Empty}),
        fieldN(4, N::Warn, {onk::RawText, onk::Empty}),
    });

    const OrgPattern rawTextCmdPattern = OrgPattern({
        field1(0, N::Name, onk::RawText),
        field1(1, N::Args, onk::RawText),
    });

    const OrgPattern parTextCmdPattern = OrgPattern({
        Field(
            Range(0, N::Args),
            OrgPattern({OrgPattern({
                Field(Range(0, N::Text), OrgPattern(onk::Paragraph)),
            })})),
        Field(Range(1, N::Body), OrgPattern(onk::StmtList)),
    });

    const OrgPattern textWrapContent = OrgPattern({
        fieldN(0, N::Args, {onk::Attrs, onk::Empty}),
        fieldN(slice(1, 1_B), N::Body, {onk::Paragraph, onk::Empty}),
    });

    const OrgPattern anySubnodePattern = OrgPattern(
        {Field(Range(slice(0, 1_B), N::Body))});

    return std::make_unique<OrgSpec>(Vec<SpecPair>{
        SpecPair{onk::StaticActiveTime, timeSpecPattern},
        SpecPair{onk::StaticInactiveTime, timeSpecPattern},
        SpecPair{
            onk::DynamicActiveTime,
            OrgPattern({fieldN(0, N::Body, {onk::InlineStmtList})})},
        SpecPair{
            onk::DynamicInactiveTime,
            OrgPattern({fieldN(0, N::Body, {onk::InlineStmtList})})},
        SpecPair{
            onk::Subtree,
            OrgPattern({
                field1(
                    0,
                    N::Prefix,
                    onk::RawText,
                    "Starting prefix of the subtree"),
                fieldN(
                    1,
                    N::Todo,
                    {onk::BigIdent, onk::Empty},
                    "Optional TODO state of the subtree"),
                fieldN(
                    2,
                    N::Importance,
                    {onk::SubtreeImportance, onk::Empty},
                    "Optional urgency marker for the subtree"),
                field1(
                    3,
                    N::Title,
                    onk::Paragraph,
                    "Paragraph of text -- title of the subtree"),
                fieldN(
                    4,
                    N::Completion,
                    {onk::SubtreeCompletion, onk::Empty},
                    "Cumulative or direct completion of the "
                    "nested "
                    "tree elements"),
                fieldN(
                    5,
                    N::Tags,
                    {onk::InlineStmtList, onk::Empty},
                    "Trailing list of hashtags"),
                field1(
                    6,
                    N::Times,
                    onk::StmtList,
                    "Scheduled, closed, and/or deadline times for "
                    "the subtree"),
                field1(
                    7,
                    N::Drawer,
                    onk::Drawer,
                    "Logbook, properties, description"),
                field1(
                    8,
                    N::Body,
                    onk::StmtList,
                    "Statement list of the nested nodes"),
            })},
        SpecPair{
            onk::CmdFiletags,
            OrgPattern({
                field1(slice(0, 1_B), N::Tags, onk::HashTag, "File tags"),
            })},
        SpecPair{
            onk::HashTag,
            OrgPattern({
                fieldN(
                    0,
                    N::Head,
                    {onk::BigIdent, onk::Word, onk::RawText},
                    "First item in the hash tag name: #tag"),
                field1(
                    slice(1, 1_B),
                    N::Subnodes,
                    onk::HashTag,
                    "Zero or more nested elements for nested tag path"),
            })},
        SpecPair{
            onk::Drawer,
            OrgPattern({
                fieldN(
                    0,
                    N::Properties,
                    {onk::DrawerPropertyList, onk::Empty},
                    "Optional list of properties"),
                fieldN(
                    1,
                    N::Logbook,
                    {onk::DrawerLogbook, onk::Empty},
                    "Optional list of log entries attached to the "
                    "subtree"),
                Field(
                    Range(2, N::Description)
                        .doc("Optional subtree description paragraph"),
                    OrgPattern({onk::SubtreeDescription, onk::Empty})),
            })},
        SpecPair{
            onk::SubtreeDescription,
            OrgPattern({field1(0, N::Text, onk::Paragraph)})},
        SpecPair{onk::BlockCenter, textWrapContent},
        SpecPair{onk::BlockQuote, textWrapContent},
        SpecPair{onk::BlockComment, textWrapContent},
        SpecPair{
            onk::BlockExample,
            OrgPattern({
                fieldN(0, N::Args, {onk::Attrs, onk::Empty}),
                fieldN(slice(1, 1_B), N::Body, {onk::RawText, onk::Empty}),
            })},
        SpecPair{
            onk::BlockDynamicFallback,
            OrgPattern({
                fieldN(0, N::Name, {onk::Word}),
                fieldN(1, N::Args, {onk::Attrs, onk::Empty}),
                fieldN(slice(2, 1_B), N::Body, {onk::RawText, onk::Empty}),
            })},
        SpecPair{
            onk::ColonExample,
            OrgPattern({
                fieldN(slice(0, 1_B), N::Body, {onk::RawText, onk::Empty}),
            })},
        SpecPair{
            onk::ErrorSkipGroup,
            OrgPattern({
                fieldN(slice(0, 1_B), N::Body, {onk::ErrorSkipToken}),
            })},
        SpecPair{onk::StmtList, anySubnodePattern},
        SpecPair{onk::Paragraph, anySubnodePattern},
        SpecPair{onk::InlineStmtList, anySubnodePattern},
        SpecPair{
            onk::List,
            OrgPattern({
                fieldN(slice(0, 1_B), N::Body, OrgSet{onk::ListItem}),
            })},
        // Subtree logbook components
        SpecPair{
            onk::DrawerLogbook,
            OrgPattern({
                fieldN(0, N::Logs, OrgSet{onk::List}),
            })},
        // Inline node kinds
        SpecPair{
            onk::InlineCallCode,
            OrgPattern({
                Field(Range(0, N::Name), OrgPattern(onk::Word)),
                Field(
                    Range(1, N::HeaderArgs),
                    OrgPattern({onk::Attrs, onk::Empty})),
                Field(Range(2, N::Args)),
                Field(Range(3, N::EndArgs)),
                Field(
                    Range(4, N::Result),
                    OrgPattern({onk::RawText, onk::Empty})),
            })},
        SpecPair{
            onk::SrcInlineCode,
            OrgPattern({
                Field(
                    Range(0, N::Lang),
                    OrgPattern({onk::Word, onk::Empty})),
                Field(
                    Range(1, N::HeaderArgs),
                    OrgPattern({onk::Attrs, onk::Empty})),
                Field(Range(2, N::Body), OrgPattern(onk::CodeLine)),
                Field(
                    Range(3, N::Result),
                    OrgPattern({onk::RawText, onk::Empty})),
            })},
        SpecPair{
            onk::Attrs,
            OrgPattern({
                Field(
                    Range(0, N::Flags),
                    {OrgPattern(onk::InlineStmtList)
                         .sub({Field(
                             Range(slice(0, 1_B), N::Flags),
                             OrgPattern(onk::CmdFlag))})}),
                Field(
                    Range(1, N::Values),
                    {OrgPattern(onk::InlineStmtList)
                         .sub({Field(
                             Range(slice(0, 1_B), N::Value),
                             OrgPattern(onk::AttrValue))})}),
            })},
        SpecPair{
            onk::AttrValue,
            OrgPattern({
                fieldN(0, N::Name),
                fieldN(1, N::Subname),
                fieldN(2, N::Value),
                fieldN(3, N::Cells),
            })},
        SpecPair{
            onk::AttrLisp,
            OrgPattern({
                fieldN(0, N::Value),
            })},
        SpecPair{onk::CmdTblfm, OrgPattern({fieldN(0, N::Values)})},
        SpecPair{
            onk::CmdResult,
            OrgPattern({fieldN(0, N::Hash), fieldN(1, N::Body)})},
        SpecPair{
            onk::ListItem,
            OrgPattern({
                Field(Range(0, N::Bullet)
                          .doc("list prefix - either dash/plus/star (for "
                               "unordered lists), or `<idx>.`/`<name>.`")),
                Field(Range(1, N::Counter)),

                Field(
                    Range(2, N::Checkbox).doc("optional checkbox"),
                    OrgPattern({onk::Checkbox, onk::Empty})),
                Field(
                    Range(3, N::Header).doc("Header part of the list"),
                    OrgPattern({onk::Paragraph, onk::Empty})),
                Field(
                    Range(4, N::Body)
                        .doc("Additional list items - more sublists, "
                             "extended N::Body (with code blocks, extra "
                             "parargaphs etc.)"),
                    OrgPattern({onk::StmtList, onk::Empty})),
            })},
        SpecPair{
            onk::TimeRange,
            OrgPattern({
                fieldN(0, N::From, anyTime),
                fieldN(1, N::To, anyTime),
                fieldN(2, N::Diff, {onk::SimpleTime, onk::Empty}),
            })},
        SpecPair{
            onk::DrawerPropertyList,
            OrgPattern({
                Field(
                    Range(slice(0, 1_B), N::Property),
                    OrgPattern(onk::DrawerProperty)),
            })},
        SpecPair{
            onk::TableRow,
            OrgPattern({
                Field(
                    Range(0, N::Args)
                        .doc("N::Optional arguments for row - can be "
                             "specified using N::`#+row`. For pipe "
                             "formatting this is not supported, N::So "
                             "arguments would be an empty node."),
                    OrgPattern({onk::Attrs, onk::Empty})),
                Field(
                    Range(1, N::Text)
                        .doc("N::It is possible to put text on the* row* "
                             "level."),
                    OrgPattern({onk::Paragraph, onk::Empty})),
                Field(
                    Range(2, N::Body),
                    OrgPattern({Field(
                        Range(slice(0, 1_B), N::Cells),
                        OrgPattern(onk::TableCell))})),
            })},
        SpecPair{
            onk::DrawerProperty,
            OrgPattern({
                field1(0, N::Name, onk::RawText),
                field1(1, N::Values, onk::RawText),
            })},
        SpecPair{
            onk::MetaSymbol,
            OrgPattern({
                field1(0, N::Name, onk::Word),
                fieldN(1, N::Args, {onk::Attrs, onk::Empty}),
                field1(2, N::Body, onk::RawText),
            })},
        SpecPair{
            onk::Table,
            OrgPattern({
                fieldN(0, N::Args, {onk::Attrs, onk::Empty}),
                Field(
                    Range(slice(1, 1_B), N::Rows),
                    OrgPattern(onk::TableRow)),
            })},
        SpecPair{
            onk::TableCell,
            OrgPattern({
                fieldN(0, N::Args, {onk::Attrs, onk::Empty}),
                fieldN(1, N::Body, {onk::Empty, onk::StmtList}),
            })},
        SpecPair{
            onk::CriticMarkStructure,
            OrgPattern({
                fieldN(0, N::Name, {onk::RawText}),
                fieldN(1, N::Assoc, {onk::Empty, onk::Paragraph}),
                fieldN(2, N::Body, {onk::Empty, onk::Paragraph}),
            })},
        SpecPair{onk::CmdTitle, parTextCmdPattern},
        SpecPair{onk::CmdCaption, parTextCmdPattern},
        SpecPair{onk::CmdCreator, parTextCmdPattern},
        SpecPair{onk::CmdAuthor, parTextCmdPattern},
        SpecPair{
            onk::CmdColumns,
            OrgPattern({
                fieldN(0, N::Args, {onk::Attrs, onk::Empty}),
            })},
        SpecPair{
            onk::CmdPropertyText,
            OrgPattern({
                field1(0, N::Name, onk::RawText),
                Field(
                    Range(1, N::Args),
                    OrgPattern({OrgPattern({
                        field1(0, N::Text, onk::Paragraph),
                    })})),
                field1(2, N::Body, onk::StmtList),
            })},
        SpecPair{
            onk::CmdPropertyArgs,
            OrgPattern({
                field1(0, N::Name, onk::RawText),
                fieldN(1, N::Args, {onk::Attrs, onk::Empty}),
                field1(2, N::Body, onk::StmtList),
            })},
        SpecPair{
            onk::Cmd,
            OrgPattern({
                field1(0, N::Name, onk::Word),
                fieldN(1, N::Args, {onk::Attrs, onk::Empty}),
            })},
        SpecPair{
            onk::BlockExport,
            OrgPattern({
                field1(0, N::Name, onk::Word),
                fieldN(1, N::Args, {onk::Empty, onk::Attrs}),
                Field(
                    Range(2, N::Body),
                    OrgPattern(onk::StmtList)
                        .sub({Field(
                            Range(slice(0, 1_B), N::Lines),
                            OrgPattern(onk::RawText))})),
            })},
        SpecPair{
            onk::InlineExport,
            OrgPattern({
                field1(0, N::Name, onk::RawText),
                field1(1, N::Body, onk::RawText),
            })},
        SpecPair{
            onk::CmdInclude,
            OrgPattern({Field(
                Range(0, N::Args),
                OrgPattern({OrgPattern({
                    field1(0, N::File, onk::File),
                    fieldN(1, N::Kind, {onk::Empty, onk::Word}),
                    fieldN(2, N::Lang, {onk::Empty, onk::Word}),
                    fieldN(3, N::Args, {onk::Empty, onk::Attrs}),
                })}))})},
        SpecPair{
            onk::BlockCode,
            OrgPattern({
                fieldN(0, N::Lang, {onk::Word, onk::Empty}),
                fieldN(1, N::HeaderArgs, {onk::Attrs, onk::Empty}),
                Field(
                    Range(2, N::Body),
                    OrgPattern(onk::StmtList)
                        .sub({Field(
                            Range(slice(0, 1_B), N::Lines),
                            OrgPattern(onk::CodeLine))})),
                Field(
                    Range(3, N::Result),
                    OrgPattern({onk::RawText, onk::Empty})),
            })},
        SpecPair{
            onk::CmdResults,
            OrgPattern({
                field1(0, N::Args, {onk::Empty, onk::Attrs}),
                fieldN(1, N::Body),
            })},
        SpecPair{
            onk::CmdCustomArgsCommand,
            OrgPattern({
                field1(0, N::Name, onk::RawText),
                field1(1, N::Args, onk::Attrs),
            })},
        SpecPair{
            onk::CmdCustomTextCommand,
            OrgPattern({
                field1(0, N::Name, onk::RawText),
                field1(1, N::Args, onk::Paragraph),
            })},
        SpecPair{
            onk::CmdCustomRawCommand,
            OrgPattern({
                field1(0, N::Name, onk::RawText),
                field1(1, N::Args, onk::RawText),
            })},
        SpecPair{
            onk::Footnote,
            OrgPattern(
                {Field(Range(0, N::Name)),
                 Field(Range(1, N::Definition))})},
        SpecPair{
            onk::InlineFootnote,
            OrgPattern({Field(Range(0, N::Definition))})},
        SpecPair{
            onk::CmdAttr,
            OrgPattern({
                Field(
                    Range(0, N::Name),
                    OrgPattern({onk::Empty, onk::Word})),
                Field(
                    Range(1, N::Args),
                    OrgPattern({onk::Empty, onk::Attrs})),
            })},
        SpecPair{
            onk::CmdHeader,
            OrgPattern({
                Field(
                    Range(0, N::Args),
                    OrgPattern({onk::Empty, onk::Attrs})),
            })},
        SpecPair{
            onk::CmdOptions,
            OrgPattern({Field(
                Range(slice(0, 1_B), N::Args),
                OrgPattern(onk::RawText))})},
        SpecPair{
            onk::CodeLine,
            OrgPattern({
                Field(
                    Range(slice(0, 1_B), N::Chunks),
                    OrgPattern(
                        {onk::CodeText,
                         onk::CodeTangle,
                         onk::CodeCallout,
                         onk::Empty})),
            })},
        SpecPair{
            onk::Link,
            OrgPattern(
                {Field(Range(0, N::Protocol)),
                 Field(Range(1, N::Link)),
                 Field(Range(2, N::Desc))})}

        ,
        SpecPair{
            onk::Symbol,
            OrgPattern({
                field1(0, N::Name, onk::Word),
                fieldN(
                    1,
                    N::Args,
                    OrgPattern(
                        {field1(slice(0, 1_B), N::Args, onk::RawText)})),
                fieldN(
                    2,
                    N::Body,
                    OrgPattern(
                        {field1(slice(0, 1_B), N::Args, onk::Paragraph)})),
            })},
        SpecPair{
            onk::Macro,
            OrgPattern({
                fieldN(0, N::Name),
                fieldN(slice(1, 1_B), N::Args, onk::InlineStmtList),
            })},
        SpecPair{
            onk::CodeTangle,
            OrgPattern({
                fieldN(0, N::Name),
            })},
        SpecPair{
            onk::CmdCallCode,
            OrgPattern({
                fieldN(0, N::Name),
                fieldN(
                    1, N::HeaderArgs, {onk::InlineStmtList, onk::Empty}),
                fieldN(2, N::Args, {onk::InlineStmtList, onk::Empty}),
                fieldN(3, N::EndArgs, {onk::InlineStmtList, onk::Empty}),
            })},
        SpecPair{onk::Angle, OrgPattern({fieldN(0, N::Body)})},
        SpecPair{onk::Bold, OrgPattern({fieldN(slice(0, 1_B), N::Body)})},
        SpecPair{
            onk::Italic, OrgPattern({fieldN(slice(0, 1_B), N::Body)})},
        SpecPair{
            onk::Verbatim, OrgPattern({fieldN(slice(0, 1_B), N::Body)})},
        SpecPair{
            onk::Strike, OrgPattern({fieldN(slice(0, 1_B), N::Body)})},
        SpecPair{
            onk::Underline, OrgPattern({fieldN(slice(0, 1_B), N::Body)})},
        SpecPair{
            onk::Monospace,
            OrgPattern({field1(slice(0, 1_B), N::Body, onk::RawText)})},
        //
    });
}
