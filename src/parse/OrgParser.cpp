#pragma once

#include <parse/OrgParser.hpp>

using otk = OrgTokenKind;
using org = OrgNodeKind;
using ock = OrgCommandKind;
using Err = OrgParser::Errors;


class OrgParserImplBase : public OrgParser {
    using OrgParser::OrgParser;
};

#define EACH_METHOD(__IMPL)                                               \
    __IMPL(Footnote);                                                     \
    __IMPL(CSVArguments);                                                 \
    __IMPL(Macro);                                                        \
    __IMPL(RawUrl);                                                       \
    __IMPL(Link);                                                         \
    __IMPL(InlineMath);                                                   \
    __IMPL(Symbol);                                                       \
    __IMPL(HashTag);                                                      \
    __IMPL(TimeRange);                                                    \
    __IMPL(TimeStamp);                                                    \
    __IMPL(Ident);                                                        \
    __IMPL(SrcInline);                                                    \
    __IMPL(Table);                                                        \
    __IMPL(Placeholder);                                                  \
    __IMPL(TopParagraph);                                                 \
    __IMPL(InlineParagraph);                                              \
    __IMPL(CommandArguments);                                             \
    __IMPL(SrcArguments);                                                 \
    __IMPL(Src);                                                          \
    __IMPL(Example);                                                      \
    __IMPL(ListItemBody);                                                 \
    __IMPL(ListItem);                                                     \
    __IMPL(NestedList);                                                   \
    __IMPL(List);                                                         \
    __IMPL(Latex);                                                        \
                                                                          \
    __IMPL(Subtree);                                                      \
    __IMPL(SubtreeTodo);                                                  \
    __IMPL(SubtreeUrgency);                                               \
    __IMPL(SubtreeDrawer);                                                \
    __IMPL(SubtreeCompletion);                                            \
    __IMPL(SubtreeTags);                                                  \
    __IMPL(SubtreeTitle);                                                 \
    __IMPL(SubtreeTimes);                                                 \
                                                                          \
    __IMPL(SubtreeLogbookClockEntry);                                     \
    __IMPL(SubtreeLogbookListEntry);                                      \
    __IMPL(SubtreeLogbook);                                               \
    __IMPL(SubtreeProperties);                                            \
                                                                          \
    __IMPL(OrgFile);                                                      \
    __IMPL(LineCommand);                                                  \
    __IMPL(ToplevelItem);                                                 \
    __IMPL(Top);


namespace {

template <bool DoTrace>
struct OrgParserImpl : public OrgParserImplBase {
    OrgParserImpl(OrgNodeGroup* _group) : OrgParserImplBase(_group) {}

    Slice<OrgId> parseText(OrgLexer& lex);

    /// First pass of the text processing pass. Fold all known text
    /// structures into larger nodes, convert opening markup tokens into
    /// `XOpen` and `XClose` nodes.
    void textFold(OrgLexer& lex);

    /// Recursively fold text block in the specified range, updating nested
    /// markup nodes and converting `XOpen/XClose` elements to `X/Empty`
    /// nodes as needed.
    void parseTextRecursiveFold(Slice<OrgId> range);

#define OVERRIDE(Kind) virtual OrgId parse##Kind(OrgLexer& lex) override;

    EACH_METHOD(OVERRIDE);
#undef OVERRIDE

    virtual OrgId parseParagraph(OrgLexer& lex, bool onToplevel) override;
    virtual OrgId parseTextWrapCommand(OrgLexer& lex, OrgCommandKind kind)
        override;
};


void space(OrgLexer& lex) {
    while (lex.at(otk::Space) || lex.at(otk::SkipSpace)) {
        lex.next();
    }
}


void skipSpace(OrgLexer& lex) {
    while (lex.at(otk::SkipSpace)) {
        lex.next();
    }
}


void newline(OrgLexer& lex) {
    while (lex.at(otk::Newline) || lex.at(otk::SkipNewline)) {
        lex.next();
    }
}

Vec<OrgTokenId> strip(
    OrgLexer&                   lex,
    const Vec<OrgTokenId>&      tokens,
    const IntSet<OrgTokenKind>& leading,
    const IntSet<OrgTokenKind>& trailing,
    const IntSet<OrgTokenKind>& skipLeading,
    const IntSet<OrgTokenKind>& skipTrailing) {
    Vec<OrgTokenId> result;

    auto leftmost  = 0;
    auto rightmost = tokens.high();
    while (leftmost <= rightmost
           && (skipLeading + leading)
                  .contains(lex.in->at(tokens[leftmost]).kind)) {
        ++leftmost;
    }

    while (leftmost <= rightmost
           && (skipTrailing + trailing)
                  .contains(lex.in->at(tokens[rightmost]).kind)) {
        --rightmost;
    }

    for (const auto [idx, token] : enumerate(tokens)) {
        if (idx < leftmost) {
            if ((skipLeading.contains(lex.in->at(token).kind))) {
                result.push_back(token);
            }
        } else if (rightmost < idx) {
            if (skipTrailing.contains(lex.in->at(token).kind)) {
                result.push_back(token);
            }
        } else {
            result.push_back(token);
        }
    }
    return result;
}


#define SPECIALIZE(Kind)                                                  \
    template <>                                                           \
    OrgId OrgParserImpl<TRACE_STATE>::parse##Kind(OrgLexer& lex);


#define TRACE_STATE true
EACH_METHOD(SPECIALIZE)
#include <parse/OrgParser.cxx>

#define TRACE_STATE false
EACH_METHOD(SPECIALIZE)
#include <parse/OrgParser.cxx>

#undef SPECIALIZE

} // namespace


#define IMPL(Kind)                                                        \
    OrgId OrgParser::parse##Kind(OrgLexer& lex) {                         \
        return impl->parse##Kind(lex);                                    \
    }

EACH_METHOD(IMPL);
#undef IMPL


OrgId OrgParser::parseParagraph(OrgLexer& lex, bool onTopLevel) {
    return impl->parseParagraph(lex, onTopLevel);
}

OrgId OrgParser::parseTextWrapCommand(OrgLexer& lex, OrgCommandKind kind) {
    return impl->parseTextWrapCommand(lex, kind);
}

void OrgParser::initImpl(bool doTrace) {
    if (doTrace) {
        impl = std::shared_ptr<OrgParserImpl<true>>(
            new OrgParserImpl<true>(group));
    } else {
        impl = std::shared_ptr<OrgParserImpl<false>>(
            new OrgParserImpl<false>(group));
    }

    impl->locationResolver = locationResolver;
}


void OrgParser::skipLineCommand(OrgLexer& lex) {
    __trace();
    skip(lex, otk::CommandPrefix);
    skip(lex, otk::LineCommand);
    skip(lex, otk::Colon);
}


void assertValidStructure(OrgNodeGroup* group, OrgId id) {
    using Id = OrgNodeGroup::Id;

    Func<void(Id)> aux;
    aux = [&](Id top) {
        auto& g = *group;
        Q_ASSERT(g.nodes.contains(top));
        if (g.at(top).isTerminal() || g.at(top).isMono()) {
            return;
        }

        Q_ASSERT(g.at(top).kind != org::Empty);

        Id start = top + 1;
        Id id    = start;

        if (Opt<Slice<Id>> extentOpt = g.allSubnodesOf(top)) {
            Slice<Id> extent = extentOpt.value();
            Q_ASSERT(g.nodes.contains(extent.first));
            Q_ASSERT(g.nodes.contains(extent.last));

            int index = 0;
            while (extent.contains(id)) {
                Q_ASSERT(g.nodes.contains(id));
                aux(id);

                id = id + g.at(id).getExtent();
                Q_ASSERT_X(
                    g.nodes.contains(id),
                    "next subnode",
                    "Step over the subnode of $# with extent $# yielded "
                    "id $# which is outsize of the group range (index is "
                    "$#, group size is $#), subnode index is $#, size "
                    "overflow is $#"
                        % to_string_vec(
                            start.getUnmasked(),
                            extent,
                            id.getUnmasked(),
                            id.getIndex(),
                            g.size(),
                            index,
                            id - g.nodes.back()));


                id = id + 1;
                ++index;
            }

            Q_ASSERT_X(
                extent.last + 1 == id,
                "range end",
                "Iteration over subnode ranges for $# did not end at the "
                "$# -- combined subnode extent strides summed up to $#. "
                "Total subnode count is $#, full extent is $#"
                    % to_string_vec(
                        top.getUnmasked(),
                        (extent.last + 1).getUnmasked(),
                        id.getUnmasked(),
                        index,
                        extent));
        }
    };

    aux(id);
}


void OrgParser::extendSubtreeTrails(OrgId position) {
    Func<OrgId(OrgId, int)> aux;
    aux = [&](OrgId id, int level) -> OrgId {
        OrgId const start = id;
        // Iterate over all nodes until the end of the group or until exit
        // condition is met. This assumes non-restructured tree that has
        // subnodes positioned flatlyl on the top level
        auto& g = *group;
        while (id <= g.nodes.back()) {
            // NOTE: 'back' returns the last node, not one-past-last
            OrgNode node = g.at(id);
            if (node.kind == org::Subtree) {
                OrgId const tree  = id;
                OrgId       subId = g.subnode(tree, 0);
                int         sub   = g.strVal(subId).size();
                if (level < sub) {
                    OrgId stmt = g.subnode(tree, 8);
                    Q_ASSERT(g.at(stmt).kind == org::StmtList);
                    id = aux(stmt + 1, sub);
                    Q_ASSERT(stmt + 1 <= id);
                    // AUX returns next position to start looping from, so
                    // the tree size is 'end - start - 1' to account for
                    // the offset.

                    // Extend the tree itself and nested statement list
                    g.at(stmt).extend((id - stmt) - 1);

                    g.at(tree).extend((id - tree) - 1);

                    auto treeSlice = g.allSubnodesOf(tree).value();
                    auto stmtSlice = g.allSubnodesOf(tree).value();

                    // Structural correctness checks -- mostly for
                    // debugging of the implementation, malformed incoming
                    // data is not expected.
                    assertValidStructure(group, tree);
                    Q_ASSERT(treeSlice.last <= g.nodes.back());
                    Q_ASSERT(stmtSlice.last <= g.nodes.back());
                    Q_ASSERT_X(
                        treeSlice.last == stmtSlice.last,
                        "extend tree",
                        "$# -- $#" % to_string_vec(treeSlice, stmtSlice));
                    Q_ASSERT_X(
                        treeSlice.contains(stmtSlice),
                        "statement containment",
                        "$# -- $#" % to_string_vec(treeSlice, stmtSlice));


                } else {
                    // Found subtree on the same level or above
                    break;
                }
            } else {
                // Node is not a subtree, skipping.
                ++id;
            }
        }

        // Return next starting position for the caller start
        return id;
    };

    aux(position, 0);
    assertValidStructure(group, position);
}


void OrgParser::extendAttachedTrails(OrgId position) {
    Func<OrgId(OrgId)> aux;
    aux = [&](OrgId id) -> OrgId {
        auto& g = *group;

        OrgNode node = g.at(id);
        if (OrgAttachableCommands.contains(node.kind)) {
            OrgId const annotation = id;
            // Get ID of the nested statement list
            OrgId const stmt = g.subnode(annotation, 1);
            Q_ASSERT(g.at(stmt).kind == org::StmtList);
            // Next element after command block is the non-optional newline
            // to separate them.
            Q_ASSERT(g.at(stmt + 1).kind == org::SkipNewline);
            OrgId   nextId = stmt + 2;
            OrgNode next   = g.at(nextId);

            // qDebug() << "Next element from" << annotation << "has kind"
            //          << next.kind << "at" << nextId;

            if (OrgAttachableCommands.contains(next.kind)) {
                // Nested annotations are recursively placed inside
                // each other by extending the trail
                id = aux(nextId);
                g.at(annotation).extend((id - annotation) - 1);
                g.at(stmt).extend((id - stmt) - 1);

            } else if (OrgTrailableCommands.contains(next.kind)) {
                // Element that can be put as the final part of the
                // trailable statement
                if (auto nextSub = g.allSubnodesOf(nextId)) {
                    OrgId const end = nextSub->last;
                    g.at(annotation).extend(end - annotation);
                    g.at(stmt).extend(end - stmt);
                    id = end + 1;
                } else {
                    qWarning()
                        << "No subnodes found in the next node" << nextId;
                    ++id;
                }

            } else {
                // Next element after line command is neither trailable
                // nor another command. Switching the subnode kind to
                // empty.
                g.at(stmt) = getEmpty();
                ++id;
            }
        } else {
            ++id;
        }

        return id;
    };

    while (position < group->nodes.back()) {
        position = aux(position);
    }
}
