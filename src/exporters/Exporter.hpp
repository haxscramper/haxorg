#pragma once

#include <sem/SemOrg.hpp>


template <typename V, typename R>
struct Exporter {
#define __EXPORTER_USING_DEFINE(__Kind)                                   \
    using __ExporterBase::visit##__Kind;

#define EXPORTER_USING()                                                  \
    using __ExporterBase::visitField;                                     \
    using __ExporterBase::visitVariantField;                              \
    using __ExporterBase::visitSubnode;                                   \
    using __ExporterBase::pushVisit;                                      \
    using __ExporterBase::popVisit;                                       \
    using __ExporterBase::visit;                                          \
    using __ExporterBase::visitDispatchHook;                              \
    using __ExporterBase::visitStart;                                     \
    using __ExporterBase::visitEnd;                                       \
    using __ExporterBase::visitTop;                                       \
    EACH_SEM_ORG_KIND(__EXPORTER_USING_DEFINE)


    template <typename T>
    void visitField(R& arg, const char* name, T const& val) {}

    template <typename T>
    void visitField(R& arg, const char* name, Opt<T> const& value) {
        if (value) {
            visitField(arg, name, *value);
        }
    }

    void visitField(R& arg, const char* name, sem::Wrap<sem::Org> org) {
        visit(org);
    }

    template <typename T>
    void visitVariantField(R& arg, const char* type, T const& val) {
        visitField(arg, type, val);
    }

    void visitSubnode(R&, int, sem::Wrap<sem::Org> const& val) {
        visit(val);
    }

    R newRes(sem::Wrap<sem::Org> const) { return R{}; }

    void pushVisit(sem::Wrap<sem::Org> const) {}
    void popVisit(sem::Wrap<sem::Org> const) {}
    void visitDispatchHook(sem::Wrap<sem::Org> const) {}
    void visitStart(sem::Wrap<sem::Org> const) {}
    void visitEnd(sem::Wrap<sem::Org> const) {}

    void visitDispatch(R& res, sem::Wrap<sem::Org> const arg) {

        switch (arg->getKind()) {
#define __case(__Kind)                                                    \
    case OrgSemKind::__Kind: {                                            \
        sem::Wrap<sem::__Kind> tmp = arg->as<sem::__Kind>();              \
        _this()->pushVisit(tmp);                                          \
        _this()->visitDispatchHook(arg);                                  \
        _this()->visit##__Kind(res, tmp);                                 \
        _this()->popVisit(tmp);                                           \
        break;                                                            \
    }


            EACH_SEM_ORG_KIND(__case)

#undef __case
        }
    }


    void visit(R& res, sem::Wrap<sem::Org> const arg) {
        visitDispatch(res, arg);
    }

    template <typename T>
    R visit(CR<T> arg) {
        R tmp = _this()->newRes(arg);
        _this()->visit(tmp, arg);
        return tmp;
    }

    R visitTop(sem::Wrap<sem::Org> org) {
        _this()->visitStart(org);
        R tmp = _this()->visit(org);
        _this()->visitEnd(org);
        return tmp;
    }

    void eachSub(R& res, sem::Wrap<sem::Org> org) {
        int idx = 0;
        for (const auto& it : org->subnodes) {
            _this()->visitSubnode(res, idx, it);
            ++idx;
        }
    }

    V* _this() { return static_cast<V*>(this); }

    void visit(R& res, int value) { res = _this()->newRes(value); }
    void visit(R& res, CR<Str> value) { res = _this()->newRes(value); }

    template <typename E>
    void visit(R& res, E value)
        requires(std::is_enum<E>::value)
    {
        res = _this()->newRes(value);
    }

#define __field(res, obj, name) _this()->visitField(res, #name, obj->name);
#define __obj_field(res, obj, name)                                       \
    _this()->visitField(res, #name, obj.name);
#define __var_field(res, type, value, field)                              \
    _this()->visitVariantField(res, #type, value.field);


    void visit(R& res, CR<sem::Link::Data> data) {
        std::visit(
            overloaded{
                [&](CR<sem::Link::Id> id) {
                    __var_field(res, Id, id, text);
                },
                [&](CR<sem::Link::Footnote> id) {
                    __var_field(res, Footnote, id, target);
                },
                [&](CR<sem::Link::Raw> raw) {
                    __var_field(res, Raw, raw, text);
                }},
            data);
    }

    void visit(R& res, CR<sem::Time::Repeat> repeat) {
        __obj_field(res, repeat, period);
        __obj_field(res, repeat, count);
        __obj_field(res, repeat, mode);
    }

    void visit(R& res, CR<sem::Time::TimeVariant> time) {
        std::visit(
            overloaded{
                [&](CR<sem::Time::Static> time) {
                    __var_field(res, Static, time, simpleTime);
                    __var_field(res, Static, time, time);
                    __var_field(res, Static, time, repeat);
                },
                [&](CR<sem::Time::Dynamic> time) {
                    __var_field(res, Dynamic, time, expr);
                }},
            time);
    }

    void visitLink(R& res, sem::Wrap<sem::Link> link) {
        __field(res, link, description);
        __field(res, link, data);
        _this()->eachSub(res, link);
    }

    void visitHashTag(R& res, sem::Wrap<sem::HashTag> tag) {
        __field(res, tag, subtags);
        __field(res, tag, head);
        _this()->eachSub(res, tag);
    }

    void visitTime(R& res, sem::Wrap<sem::Time> time) {
        __field(res, time, time);
        __field(res, time, isActive);
    }

    void visitTable(R& res, sem::Wrap<sem::Table> table) {
        __field(res, table, rows);
    }

    void visitTimeRange(R& res, sem::Wrap<sem::TimeRange> range) {
        __field(res, range, from);
        __field(res, range, to);
    }

    void visitCaption(R& res, sem::Wrap<sem::Caption> range) {
        __field(res, range, text);
    }

    void visitInlineMath(R& res, sem::Wrap<sem::InlineMath> math) {}

    void visitDocument(R& res, sem::Wrap<sem::Document> doc) {
        __field(res, doc, title);
        __field(res, doc, author);
        __field(res, doc, creator);
        __field(res, doc, email);
        __field(res, doc, language);
        __field(res, doc, exportFileName);
        __field(res, doc, idTable);
        __field(res, doc, nameTable);
        __field(res, doc, anchorTable);
        __field(res, doc, footnoteTable);
        _this()->eachSub(res, doc);
    }

    void visitDocumentGroup(R& res, sem::Wrap<sem::DocumentGroup> doc) {
        _this()->eachSub(res, doc);
    }

    void visitCompletion(R& res, sem::Wrap<sem::Completion> completion) {
        __field(res, completion, done);
        __field(res, completion, full);
        __field(res, completion, isPercent);
    }

    void visit(R& res, CR<sem::SubtreeLog::LogEntry> entry) {
        std::visit(
            overloaded{
                [&](CR<sem::SubtreeLog::State> state) {
                    __var_field(res, State, state, from);
                    __var_field(res, State, state, to);
                    __var_field(res, State, state, on);
                },
                [&](CR<sem::SubtreeLog::Clock> state) {
                    __var_field(res, Clock, state, range);
                },
                [&](CR<sem::SubtreeLog::Tag> state) {
                    __var_field(res, Tag, state, tag);
                    __var_field(res, Tag, state, added);
                },
                [&](CR<sem::SubtreeLog::Refile> state) {
                    __var_field(res, Refile, state, on);
                },
                [&](CR<sem::SubtreeLog::Note> state) {
                    __var_field(res, Note, state, on);
                }},
            entry);
    }

    void visitSubtreeLog(R& res, sem::Wrap<sem::SubtreeLog> log) {
        __field(res, log, log);
    }

    void visit(R& res, CR<sem::Subtree::Properties::Property> prop) {
        /// TODO
    }

    void visitSubtree(R& res, sem::Wrap<sem::Subtree> tree) {
        __field(res, tree, level);
        __field(res, tree, id);
        __field(res, tree, todo);
        __field(res, tree, completion);
        __field(res, tree, tags);
        __field(res, tree, title);
        __field(res, tree, description);
        __field(res, tree, logbook);
        __field(res, tree, properties);
        __field(res, tree, closed);
        __field(res, tree, deadline);
        __field(res, tree, scheduled);
        eachSub(res, tree);
    }


    void visitListItem(R& res, sem::Wrap<sem::ListItem> item) {
        __field(res, item, header);
        __field(res, item, checkbox);
        _this()->eachSub(res, item);
    }

    void visitQuote(R& res, sem::Wrap<sem::Quote> quote) {
        __field(res, quote, text);
    }

    void visitCode(R& res, sem::Wrap<sem::Code> code) {
        __field(res, code, exports);
        __field(res, code, cache);
        __field(res, code, eval);
        __field(res, code, noweb);
        __field(res, code, hlines);
        __field(res, code, tangle);
    }


#define __only_sub(__Kind)                                                \
    void visit##__Kind(R& res, sem::Wrap<sem::__Kind> p) {                \
        _this()->eachSub(res, p);                                         \
    }

    __only_sub(Paragraph);
    __only_sub(Stmt);
    __only_sub(StmtList);
    __only_sub(Center);

    __only_sub(CommandGroup);

    __only_sub(Row);
    __only_sub(Example);

    // Markup default definitions
    __only_sub(Bold);
    __only_sub(Monospace);
    __only_sub(MarkQuote);
    __only_sub(Verbatim);
    __only_sub(Italic);
    __only_sub(Strike);
    __only_sub(Par);
    __only_sub(List);

#undef __only_sub

#define __only_leaf(__Kind)                                               \
    void visit##__Kind(R& res, sem::Wrap<sem::__Kind> leaf) {             \
        __field(res, leaf, text);                                         \
    }

    __only_leaf(Newline);
    __only_leaf(Space);
    __only_leaf(Word);
    __only_leaf(RawText);
    __only_leaf(Punctuation);
    __only_leaf(Placeholder);
    __only_leaf(BigIdent);

#undef __only_leaf


#undef __field
};
