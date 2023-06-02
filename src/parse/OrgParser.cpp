#pragma once

#include <parse/OrgParser.hpp>
#include <hstd/wrappers/perfetto_aux.hpp>

#ifdef USE_PERFETTO
#    define __perf_trace(name) TRACE_EVENT("parsing", name)
#else
#    define __perf_trace(_)
#endif

using otk = OrgTokenKind;
using org = OrgNodeKind;
using ock = OrgCommandKind;
using Err = OrgParser::Errors;


class OrgParserImplBase : public OrgParser {

  protected:
    void skipLineCommand(OrgLexer& lex) {
        skip(lex, otk::CommandPrefix);
        skip(lex, otk::LineCommand);
        skip(lex, otk::Colon);
        while (lex.at(otk::SkipSpace)) {
            lex.next();
        }
    }

    CR<OrgNode> pending() const {
        Q_ASSERT(0 <= group->treeDepth());
        return group->lastPending();
    }

    OrgId fail(OrgTokenId invalid) {
        token(OrgNodeKind::ErrorToken, invalid);
        /// TODO insert token with error description
        token(OrgNodeKind::ErrorTerminator, OrgTokenId::Nil());
        OrgId failed           = end();
        group->at(failed).kind = OrgNodeKind::Error;
        return failed;
    }

    OrgId back() const { return group->nodes.back(); }

    int treeDepth() const {
        Q_ASSERT(0 <= group->treeDepth());
        return group->treeDepth();
    }

    OrgId start(OrgNodeKind kind) { return group->startTree(kind); }
    OrgId end() {
        Q_ASSERT(0 <= group->treeDepth());
        return group->endTree();
    }
    OrgId   empty() { return token(getEmpty()); }
    OrgNode getEmpty() { return OrgNode::Mono(OrgNodeKind::Empty); }
    OrgId   token(CR<OrgNode> node) { return group->token(node); }
    OrgId   token(OrgNodeKind kind, OrgTokenId tok) {
        return group->token(kind, tok);
    }

    OrgId fake(OrgNodeKind kind) {
        return group->token(
            kind, group->tokens->add(OrgToken(OrgTokenKind::None)));
    }


    bool at(CR<OrgLexer> lex, CR<OrgParser::OrgExpectable> item) {
        if (item.index() == 0 && lex.at(std::get<0>(item))) {
            return true;
        } else if (item.index() == 1 && lex.at(std::get<1>(item))) {
            return true;
        } else if (
            item.index() == 2 //
            && lex.at(std::get<2>(item).kind)
            && lex.tok().strVal() == std::get<2>(item).value) {
            return true;
        } else {
            return false;
        }
    }

    void expect(CR<OrgLexer> lex, CR<OrgParser::OrgExpectable> item) {
        if (!(at(lex, item))) {
            throw wrapError(
                Err::UnexpectedToken(lex, getLoc(lex), {item}), lex);
        }
    }

    OrgTokenId pop(OrgLexer& lex, CR<OrgParser::OrgExpectable> tok) {
        expect(lex, tok);
        return lex.pop();
    }

    void skip(OrgLexer& lex, CR<OrgParser::OrgExpectable> item) {
        expect(lex, item);
        lex.next();
    }


  public:
    int  depth = 0;
    void report(CR<Report> in);

    Func<void(CR<Report>)>              reportHook;
    Func<void(CR<Report>, bool&, bool)> traceUpdateHook;
    OrgNodeGroup*                       group = nullptr;
    OrgParserImplBase(OrgNodeGroup* _group) : group(_group) {}

    void extendSubtreeTrails(OrgId position) override;
    void extendAttachedTrails(OrgId position) override;

    using OrgParser::OrgParser;
    Func<LineCol(CR<PosStr>)> locationResolver;


    void setReportHook(Func<void(CR<Report>)> in) override {
        reportHook = in;
    }

    void setTraceUpdateHook(
        Func<void(CR<Report>, bool&, bool)> in) override {
        traceUpdateHook = in;
    }

    void setLocationResolver(Func<LineCol(CR<PosStr>)> in) override {
        locationResolver = in;
    }


    virtual Opt<LineCol> getLoc(CR<OrgLexer> lex) override {
        if (!locationResolver) {
            return std::nullopt;
        }

        if (lex.finished()) {
            return std::nullopt;
        } else {
            for (int offset = 0;
                 lex.hasNext(-offset) || lex.hasNext(offset);
                 ++offset) {
                // Try incrementally widening lookarounds on the current
                // lexer position until there is a token that has proper
                // location information.
                for (int i : Vec{-1, 1}) {
                    if (lex.hasNext(offset * i)) {
                        OrgToken tok = lex.tok(offset * i);
                        if (tok.hasData()) {
                            PosStr str{tok.getText()};
                            return locationResolver(str);
                        }
                        // If offset falls out of the lexer range on both
                        // ends, terminate lookup.
                    }
                }
            }
            return std::nullopt;
        }
    }
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
    using OrgParserImplBase::OrgParserImplBase;
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

SPtr<OrgParser> OrgParser::initImpl(OrgNodeGroup* group, bool doTrace) {
    if (doTrace) {
        return SPtr<OrgParserImpl<true>>(new OrgParserImpl<true>(group));
    } else {
        return SPtr<OrgParserImpl<false>>(new OrgParserImpl<false>(group));
    }
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


void OrgParserImplBase::extendSubtreeTrails(OrgId position) {
    __perf_trace("extendSubtreeTrails");
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


void OrgParserImplBase::extendAttachedTrails(OrgId position) {
    __perf_trace("extendAttachedTrails");
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

void OrgParserImplBase::report(CR<Report> in) {
    using fg = TermColorFg8Bit;

    if (reportHook) {
        reportHook(in);
    }

    if (traceUpdateHook) {
        traceUpdateHook(in, trace, true);
    }
    if (!trace) {
        if (traceUpdateHook) {
            traceUpdateHook(in, trace, false);
        }

        return;
    }

    if (in.kind == ReportKind::EnterParse
        || in.kind == ReportKind::StartNode) {
        ++depth;
    }

    ColStream os = getStream();
    os << repeat("  ", depth);

    auto printTokens = [&]() {
        if (in.lex != nullptr) {
            os << " [";
            OrgLexer::PrintParams params;
            in.lex->print(os, params);
            os << "]";
        }
    };

    auto getLoc = [&]() -> QString {
        QString res;
        if (in.lex != nullptr) {
            Opt<LineCol> loc = this->getLoc(*in.lex);
            if (loc.has_value()) {
                res = "$#:$# " % to_string_vec(loc->line, loc->column);
            }
        }
        return res;
    };

    if (treeDepth() < 0) {
        qFatal("Negative tree depth");
    }

    switch (in.kind) {
        case ReportKind::Print: {
            os << "  " << in.line << getLoc() << ":" << in.subname.value();
            printTokens();
            break;
        }

        case ReportKind::AddToken: {
            auto id = in.node.value();
            os << "  # add [" << id.getIndex() << "] "
               << to_string(group->at(id).kind) << " at " << in.line
               << " with " << escape_literal(group->strVal(id));
            break;
        }

        case ReportKind::StartNode:
        case ReportKind::EndNode: {
            auto id = in.node.value();
            if (in.kind == ReportKind::StartNode) {
                os << "+ started node, level is " << treeDepth();
            } else {
                os << "- ended node, level is " << treeDepth();
            }

            os << " [" << id.getIndex() << "] "
               << to_string(group->at(id).kind) << " at " << in.line;
            if (in.kind == ReportKind::EndNode) {
                os << " ext=" << group->at(id).getExtent();
            }
            break;
        }

        case ReportKind::EnterParse:
        case ReportKind::LeaveParse: {
            os << (in.kind == ReportKind::EnterParse ? "> " : "< ") //
               << "~" << treeDepth() << " "                         //
               << fg::Green << in.name.value() << os.end() << ":"
               << fg::Cyan << in.line << os.end();

            if (in.subname.has_value()) {
                os << " <@" << in.subname.value() << ">";
            }

            printTokens();

            break;
        }
    }

    endStream(os);

    if (in.kind == ReportKind::LeaveParse
        || in.kind == ReportKind::EndNode) {
        --depth;
    }

    if (traceUpdateHook) {
        traceUpdateHook(in, trace, false);
    }
}
