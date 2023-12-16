#pragma once

import std.stdlib.IntSet;


const auto otcSubtreeKinds = IntSet<OrgTextContext>{
    slice(otcSubtree0, otcSubtreeOther)};
const auto otcMarkupKinds = IntSet<OrgTextContext>{
    slice(otcBold, otcMonospaceBlock)};

const auto orgMarkupKinds = IntSet<OrgNodeKind>{
    orgBold,
    orgItalic,
    orgVerbatim,
    orgBacktick,
    orgUnderline,
    orgStrike,
    orgQuote,
    orgAngle,
    orgMonospace};

const auto orgLineCommandKinds = IntSet<OrgNodeKind>{
    slice(orgCommandTitle, orgCommandCaption),
    orgAttrImg};

/// Line commands that can be used as associted property elements.
const auto orgAttachableKinds = IntSet<OrgNodeKind>{
    orgCommandAttrHtml,
    orgCommandName,
    orgCommandHeader,
    orgAttrImg,
    orgCommandCaption};

const auto orgBlockCommandKinds = IntSet<OrgNodeKind>{
    orgTable,
    orgSrcCode,
    orgQuoteBlock,
    orgExample};

/// Line or block commands that can have associated property elements
const auto orgAssociatedKinds = IntSet<OrgNodeKind>{orgLink}
                              + orgBlockCommandKinds
                              + IntSet<OrgNodeKind>{
                                  orgCommandInclude,
                                  orgResult};

/// Line commands that cannot be used in standalone manner, and always
/// have to be associated with some other block/line command
const auto orgNoAssociatedKinds = IntSet<OrgNodeKind>{
    orgCommandHeader,
    orgCommandName,
    orgCommandCaption};

/// Nodes that should only be processed when encountered on the toplevel
/// (initial document configuration)
const auto orgDoclevelKinds = IntSet<OrgNodeKind>{
    orgCommandOptions,
    orgCommandTitle,
    orgCommandAuthor,
    orgCommandBackendOptions};


/// All node kinds that should not have subnode values
const auto orgTokenKinds = IntSet<OrgNodeKind>{
    orgCmdKey,        orgTarget,
    orgTextSeparator, orgRawLink,
    orgRadioTarget,   orgCmdFlag,
    orgOrgTag,        orgCodeText,
    orgSubtreeStars,  orgSpace,
    orgPunctuation,   orgAtMention,

    orgIdent,         orgBullet,
    orgBareIdent,     orgRawText,
    orgUnparsed,      orgBigIdent,
    orgUrgencyStatus, orgVerbatimMultilineBlock,
    orgWord,          orgEscaped,
    orgNewline,       orgComment,
    orgCheckbox,      orgCounter,
    orgCompletion,    orgTimeStamp,
    orgSimpleTime,    orgEmpty};


/// ALl types of org-mode values that can have subnodes
const auto orgSubnodeKinds = IntSet<OrgNodeKind>{slice(orgNone, org__LAST)}
                           - orgTokenKinds
                           - IntSet<OrgNodeKind>{orgUserNode};

/// All possible values of the org-node kind
const auto orgAllKinds = IntSet<OrgNodeKind>{slice(orgNone, org__LAST)};


/// Nodes that can only contain fixed number of subnodes of fixed kinds.
const auto orgTokenLikeKinds = IntSet<OrgNodeKind>{
    orgTimeRange,
    orgTimeStamp};


/// Nodes that act like containers but are strongly typed and store
/// subelements in many typed fields instead of one long untyped list.
const auto orgTypedContainerLikeKinds = IntSet<OrgNodeKind>{
    orgListItem,
    orgSubtree};

/// Nodes that can contain any number of nested nodes in any combinations.
const auto orgContainerLikeKinds = IntSet<OrgNodeKind>{
    orgStmtList,
    orgParagraph,
    orgList,
    orgLink,
};
