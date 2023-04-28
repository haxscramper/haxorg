#pragma once

#include <sem/SemOrg.hpp>


template <typename V, typename R>
struct Exporter {
#define __EXPORTER_USING_DEFINE(__Kind)                                   \
    using __ExporterBase::visit##__Kind;

    template <typename T>
    using In = CR<sem::Wrap<T>>;


#define EXPORTER_USING()                                                  \
    using __ExporterBase::visitField;                                     \
    using __ExporterBase::visitSubnode;                                   \
    using __ExporterBase::pushVisit;                                      \
    using __ExporterBase::popVisit;                                       \
    using __ExporterBase::visit;                                          \
    using __ExporterBase::visitDispatchHook;                              \
    using __ExporterBase::visitStart;                                     \
    using __ExporterBase::visitEnd;                                       \
    using __ExporterBase::visitTop;                                       \
    using __ExporterBase::In;                                             \
    EACH_SEM_ORG_KIND(__EXPORTER_USING_DEFINE)

    void visitField(R& arg, const char* name, In<sem::Org> org) {
        _this()->visit(arg, org);
    }


    void visitSubnode(R& tmp, int, In<sem::Org> val) {
        _this()->visit(tmp, val);
    }

    R newRes(In<sem::Org>) { return R{}; }

    void pushVisit(R&, In<sem::Org>) {}
    void popVisit(R&, In<sem::Org>) {}
    void visitDispatchHook(R&, In<sem::Org>) {}
    void visitStart(In<sem::Org>) {}
    void visitEnd(In<sem::Org>) {}

    void visitDispatch(R& res, In<sem::Org> arg) {
        auto kind = arg->getKind();
        switch (kind) {
#define __case(__Kind)                                                    \
    case OrgSemKind::__Kind: {                                            \
        In<sem::__Kind> tmp = arg->as<sem::__Kind>();                     \
        _this()->pushVisit(res, tmp);                                     \
        _this()->visitDispatchHook(res, arg);                             \
        _this()->visit##__Kind(res, tmp);                                 \
        _this()->popVisit(res, tmp);                                      \
        break;                                                            \
    }


            EACH_SEM_ORG_KIND(__case)

#undef __case
        }
    }


    void visit(R& res, In<sem::Org> arg) { visitDispatch(res, arg); }


    R visitTop(In<sem::Org> org) {
        _this()->visitStart(org);
        R tmp = _this()->newRes(org);
        _this()->visit(tmp, org);
        _this()->visitEnd(org);
        return tmp;
    }

    void eachSub(R& res, In<sem::Org> org) {
        int idx = 0;
        for (const auto& it : org->subnodes) {
            _this()->visitSubnode(res, idx, it);
            ++idx;
        }
    }

    V* _this() { return static_cast<V*>(this); }

#define __field(res, obj, name) _this()->visitField(res, #name, obj->name);
#define __obj_field(res, obj, name)                                       \
    _this()->visitField(res, #name, obj.name);


    // Time specializations
    void visit(R& res, CR<sem::Time::Repeat> repeat) {
        __obj_field(res, repeat, period);
        __obj_field(res, repeat, count);
        __obj_field(res, repeat, mode);
    }
    void visit(R& res, CR<sem::Time::Static> time) {
        __obj_field(res, time, simpleTime);
        __obj_field(res, time, time);
        __obj_field(res, time, repeat);
    }

    void visit(R& res, CR<sem::Time::Dynamic> time) {
        __obj_field(res, time, expr);
    }

    void visit(R& res, CR<sem::Time::TimeVariant> time) {
        _this()->visitField(res, "kind", sem::Time::getTimeKind(time));
        std::visit(
            [&, this](const auto& it) { _this()->visit(res, it); }, time);
    }
    // End of time specializations

    // Link content specializations
    void visit(R& res, CR<sem::Link::Id> id) {
        __obj_field(res, id, text);
    }

    void visit(R& res, CR<sem::Link::Footnote> id) {
        __obj_field(res, id, target);
    }

    void visit(R& res, CR<sem::Link::Raw> raw) {
        __obj_field(res, raw, text);
    }

    void visit(R& res, CR<sem::Link::Data> data) {
        _this()->visitField(res, "kind", sem::Link::getLinkKind(data));
        std::visit(
            [&, this](const auto& it) { _this()->visit(res, it); }, data);
    }
    // End of link specializations

    void visitLink(R& res, In<sem::Link> link) {
        __field(res, link, description);
        __field(res, link, data);
        _this()->eachSub(res, link);
    }

    void visitHashTag(R& res, In<sem::HashTag> tag) {
        __field(res, tag, subtags);
        __field(res, tag, head);
        _this()->eachSub(res, tag);
    }

    void visitTime(R& res, In<sem::Time> time) {
        __field(res, time, time);
        __field(res, time, isActive);
    }

    void visitTable(R& res, In<sem::Table> table) {
        __field(res, table, rows);
    }

    void visitTimeRange(R& res, In<sem::TimeRange> range) {
        __field(res, range, from);
        __field(res, range, to);
    }

    void visitCaption(R& res, In<sem::Caption> range) {
        __field(res, range, text);
    }

    void visitInlineMath(R& res, In<sem::InlineMath> math) {}

    void visitDocument(R& res, In<sem::Document> doc) {
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

    void visitDocumentGroup(R& res, In<sem::DocumentGroup> doc) {
        _this()->eachSub(res, doc);
    }

    void visitCompletion(R& res, In<sem::Completion> completion) {
        __field(res, completion, done);
        __field(res, completion, full);
        __field(res, completion, isPercent);
    }

    // Log entry speciazliations

    void visit(R& res, CR<sem::SubtreeLog::State> state) {
        __obj_field(res, state, from);
        __obj_field(res, state, to);
        __obj_field(res, state, on);
    }

    void visit(R& res, CR<sem::SubtreeLog::Clock> state) {
        std::visit(
            [&, this](const auto& it) {
                _this()->visitField(res, "range", it);
            },
            state.range);
    }

    void visit(R& res, CR<sem::SubtreeLog::Tag> state) {
        __obj_field(res, state, tag);
        __obj_field(res, state, added);
    }

    void visit(R& res, CR<sem::SubtreeLog::Refile> state) {
        __obj_field(res, state, on);
    }

    void visit(R& res, CR<sem::SubtreeLog::Note> state) {
        __obj_field(res, state, on);
    }

    void visit(R& res, CR<sem::SubtreeLog::LogEntry> entry) {
        _this()->visitField(
            res, "kind", sem::SubtreeLog::getLogKind(entry));
        std::visit(
            [&, this](const auto& it) { _this()->visit(res, it); }, entry);
    }

    void visitSubtreeLog(R& res, In<sem::SubtreeLog> log) {
        __field(res, log, log);
    }
    // end

    // subtree specializations
    void visit(R& res, CR<sem::Subtree::Property::Ordered> p) {
        __obj_field(res, p, isOrdered);
    }

    void visit(R& res, CR<sem::Subtree::Property::ExportOptions> p) {
        __obj_field(res, p, backend);
        __obj_field(res, p, values);
    }

    void visit(R& res, CR<sem::Subtree::Property::Nonblocking> o) {
        __obj_field(res, o, isBlocking);
    }

    void visit(R& res, CR<sem::Subtree::Property::Blocker> o) {
        __obj_field(res, o, blockers);
    }

    void visit(R& res, CR<sem::Subtree::Property> prop) {
        __obj_field(res, prop, data);
        __obj_field(res, prop, mainSetRule);
        __obj_field(res, prop, subSetRule);
        __obj_field(res, prop, inheritanceMode);
    }

    void visit(R& res, CR<sem::Subtree::Property::Data> prop) {
        _this()->visitField(
            res, "kind", sem::Subtree::Property::getKind(prop));
        std::visit(
            [&, this](const auto& it) { _this()->visit(res, it); }, prop);
    }

    void visitSubtree(R& res, In<sem::Subtree> tree) {
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
        _this()->eachSub(res, tree);
    }
    // end


    void visitListItem(R& res, In<sem::ListItem> item) {
        __field(res, item, header);
        __field(res, item, checkbox);
        _this()->eachSub(res, item);
    }

    void visitQuote(R& res, In<sem::Quote> quote) {
        __field(res, quote, text);
    }

    void visitCode(R& res, In<sem::Code> code) {
        __field(res, code, exports);
        __field(res, code, cache);
        __field(res, code, eval);
        __field(res, code, noweb);
        __field(res, code, hlines);
        __field(res, code, tangle);
    }


#define __only_sub(__Kind)                                                \
    void visit##__Kind(R& res, In<sem::__Kind> p) {                       \
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
    void visit##__Kind(R& res, In<sem::__Kind> leaf) {                    \
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
