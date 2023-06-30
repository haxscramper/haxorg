#pragma once

#include <sem/SemOrg.hpp>
#include <boost/mp11.hpp>
#include <concepts>
#include <lexbase/TraceBase.hpp>

using boost::mp11::mp_for_each;
using namespace boost::describe;

/// \brief Base class that should be used as the base for exporter
/// implementations.
///
/// Exporter class implements a CRTP visitation pattern that allows you to
/// implement custom visitation logic over the whole range of sem tree
/// types *and* operate on a custom types. First and foremost it was
/// designed in mind with exporters that build some tree-like structure
/// (JSON, YAML via direct types, string document via text layouter
/// library, some other IR for the final document). It is of course
/// possible to implement exporter that mutates some internal state -- in
/// this case \tparam R can be set to some dummy type such as `int` and
/// freely passed around.
template <typename V, typename R>
struct Exporter {
    struct VisitEvent {
        DECL_DESCRIBED_ENUM(
            Kind,
            VisitField,
            VisitSubnode,
            NewRes,
            VisitToEval,
            VisitValue,
            VisitDispatchHook,
            VisitStart,
            VisitEnd,
            VisitDispatch,
            VisitSpecificKind,
            PushVisit,
            PopVisit,
            VisitGeneric,
            VisitTop,
            VisitVariant);

        Kind            kind;
        Opt<sem::SemId> visitedNode  = std::nullopt;
        R*              visitedValue = nullptr;
        int             level        = 0;
        QString         file;
        int             line = 0;
        QString         field;
        QString         function;
        bool            isStart = true;
        QString         type;
    };

    using VisitEventCb = Func<void(VisitEvent const&)>;
    int visitDepth     = 0;

    VisitEventCb visitEventCb;

    void visitEvent(VisitEvent const& ev) {
        if (visitEventCb) {
            visitEventCb(ev);
        }
    }

    static void writeEvent(OperationsTracer& ot, VisitEvent const& ev) {
        auto os = ot.getStream();
        os << os.indent(ev.level * 2) << to_string(ev.kind) << ev.function
           << os.end();
        using K = typename VisitEvent::Kind;
    }

    static VisitEventCb getDefaultVisitEvent(OperationsTracer& trace) {
        return [&](VisitEvent const& ev) { writeEvent(trace, ev); };
    }

    struct VisitScope {
        Exporter<V, R>* exp;
        VisitEvent      event;
        VisitScope(Exporter<V, R>* exporter, VisitEvent event)
            : exp(exporter), event(event) {
            event.level   = exp->visitDepth;
            event.isStart = true;
            exp->visitEvent(event);
            ++exp->visitDepth;
        }

        ~VisitScope() {
            --exp->visitDepth;
            event.level   = exp->visitDepth;
            event.isStart = false;
            exp->visitEvent(event);
        }
    };

#define __visit_scope(VisitKind, ...)                                     \
    VisitScope CONCAT(visit_scope, __COUNTER__)(                          \
        this,                                                             \
        VisitEvent{                                                       \
            .kind     = VisitKind,                                        \
            .function = __PRETTY_FUNCTION__,                              \
            .line     = __LINE__,                                         \
            .file     = __FILE__,                                         \
            __VA_ARGS__});

#define __visit_field_scope(res, name, value)                             \
    __visit_scope(                                                        \
        VisitEvent::Kind::VisitField,                                     \
        .field        = name,                                             \
        .visitedValue = &res,                                             \
        .type         = typeid(value).name());

#define __visit_eval_scope(value)                                         \
    __visit_scope(                                                        \
        VisitEvent::Kind::VisitToEval, .type = typeid(value).name());

#define __visit_specific_kind(res, tree)                                  \
    __visit_scope(                                                        \
        VisitEvent::Kind::VisitSpecificKind,                              \
        .visitedValue = &res,                                             \
        .visitedNode  = tree);


#define __visit_value(res, value)                                         \
    __visit_scope(                                                        \
        VisitEvent::Kind::VisitValue,                                     \
        .visitedValue = &res,                                             \
        .type         = typeid(value).name());

#define __EXPORTER_USING_DEFINE(__Kind)                                   \
    using __ExporterBase::visit##__Kind;

    template <typename T>
    using In = sem::SemIdT<T>;


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

    void visitField(R& arg, const char* name, sem::SemId org) {
        __visit_scope(
            VisitEvent::Kind::VisitEnd,
            .visitedNode  = org,
            .field        = name,
            .visitedValue = &arg);

        _this()->visit(arg, org);
    }

    void visitSubnode(R& tmp, int, sem::SemId val) {
        _this()->visit(tmp, val);
    }

    /// \brief Create default instance of the new result type
    R newRes(sem::SemId) { return R{}; }


    /// \brief Additional hook that is called for each node before
    /// descending into specifically named overload
    void visitDispatchHook(R&, sem::SemId) {}
    /// \brief Start of the top-level visit, triggered in `visitTop`
    void visitStart(sem::SemId node) {
        __visit_scope(VisitEvent::Kind::VisitStart, .visitedNode = node);
    }
    /// \brief End of the top-level visit, triggered in the `visitTop`
    void visitEnd(sem::SemId node) {
        __visit_scope(VisitEvent::Kind::VisitEnd, .visitedNode = node);
    }

    /// \brief Main dispatch implementation for all sem types. Dispatch
    /// happens based on the kind of the provided sem node and not it's
    /// RTTI type.
    void visitDispatch(R& res, sem::SemId arg) {
        __visit_scope(
            VisitEvent::Kind::VisitDispatch,
            .visitedValue = &res,
            .visitedNode  = arg);

        if (arg.isNil()) {
            return;
        }

        auto kind = arg->getKind();
        switch (kind) {
#define __case(__Kind)                                                    \
    case OrgSemKind::__Kind: {                                            \
        In<sem::__Kind> tmp = arg.as<sem::__Kind>();                      \
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

    template <sem::NotOrg T>
    void visitDescribedOrgFields(R& res, CR<T> value) {}

    template <sem::IsOrg T>
    void visitDescribedOrgFields(R& res, In<T> tree) {
        using Bd = describe_bases<T, mod_any_access>;
        using Md = describe_members<T, mod_any_access>;
        mp_for_each<Md>([&](auto const& field) {
            _this()->visitField(
                res,
                field.name,
                (*static_cast<T const*>(tree.get())).*field.pointer);
        });

        mp_for_each<Bd>([&](auto Base) {
            visitDescribedOrgFields<typename decltype(Base)::type>(
                res, tree);
        });
    }

    /// \brief Hook called each time new sem node is visited using specific
    /// visitator hook. Used in default implementation of the
    /// `visitDispatch`
    ///
    /// \brief Pop visit after sem visit dispatch completed

#define __visit(__Kind)                                                   \
    void visit##__Kind(R& res, In<sem::__Kind> tree) {                    \
        __visit_specific_kind(res, tree);                                 \
        visitDescribedOrgFields(res, tree);                               \
    }


    EACH_SEM_ORG_KIND(__visit)

#undef __visit

    void pushVisit(R& res, sem::SemId arg) {
        __visit_scope(
            VisitEvent::Kind::PushVisit,
            .visitedValue = &res,
            .visitedNode  = arg);
    }
    void popVisit(R& res, sem::SemId arg) {
        __visit_scope(
            VisitEvent::Kind::PopVisit,
            .visitedValue = &res,
            .visitedNode  = arg);
    }

    /// \brief Default implementation of the visitation function for sem
    /// nodes
    ///
    /// Providing more specialized overload for visitation can be done
    /// using `visit(R, In<sem::MoreSpecificNodeType>)` or
    /// `visitMoreSpecificNodeType`. Former will also bypass all push/pop
    /// hooks while the latter will only override core functionality of the
    /// dispatch.
    void visit(R& res, sem::SemId arg) { visitDispatch(res, arg); }


    /// \brief Default implementation of the top visit
    ///
    /// User can redefined this function as well, or provided it's own
    /// implementation.
    R visitTop(sem::SemId org) {
        __visit_scope(VisitEvent::Kind::VisitTop, .visitedNode = org);

        _this()->visitStart(org);
        R tmp = _this()->newRes(org);
        _this()->visit(tmp, org);
        _this()->visitEnd(org);
        return tmp;
    }


    V* _this() { return static_cast<V*>(this); }

    template <typename T>
    void visitFieldRedirect(R& res, char const* name, T const& value) {
        __visit_field_scope(res, name, value);
        _this()->visitField(res, name, value);
    }

    /// \brief Trigger field visitation for value object
#define __obj_field(res, obj, name)                                       \
    visitFieldRedirect(res, #name, obj.name);

    template <typename T, typename Kind>
    void visitVariants(R& res, Kind kind, CR<T> var) {
        QString fieldName = to_string(kind);
        _this()->visitField(res, "kind", kind);
        std::visit(
            [&, this](const auto& it) {
                _this()->visitField(res, fieldName.toLatin1(), it);
            },
            var);
    }

    /// \name Specialization for inner objects of code block
    /// @{
    void visit(R& res, CR<sem::Code::Switch::LineStart> start) {
        __obj_field(res, start, start);
        __obj_field(res, start, extendLast);
    }

    void visit(R& res, CR<sem::Code::Switch::CalloutFormat> start) {
        __obj_field(res, start, format);
    }

    void visit(R& res, CR<sem::Code::Switch::RemoveCallout> start) {
        __obj_field(res, start, remove);
    }

    void visit(R& res, CR<sem::Code::Switch::EmphasizeLine> start) {
        __obj_field(res, start, line);
    }

    void visit(R& res, CR<sem::Code::Switch::Dedent> start) {
        __obj_field(res, start, value);
    }

    void visit(R& res, CR<sem::Code::Switch::Data> data) {
        visitVariants(res, sem::Code::Switch::getKind(data), data);
    }

    void visit(R& res, CR<sem::Code::Switch> sw) { visit(res, sw.data); }
    /// @}

    /// \name Specialization for inner objects of sem time
    /// @{
    void visit(R& res, CR<sem::Time::Repeat> repeat) {
        __obj_field(res, repeat, period);
        __obj_field(res, repeat, count);
        __obj_field(res, repeat, mode);
    }

    void visit(R& res, CR<UserTime> time) {
        visitVariants(res, time.getKind(), time.time);
    }

    /// \brief  Static time object visit
    void visit(R& res, CR<sem::Time::Static> time) {
        __obj_field(res, time, time);
        __obj_field(res, time, repeat);
    }

    /// \brief Dynamic time object visit
    void visit(R& res, CR<sem::Time::Dynamic> time) {
        __obj_field(res, time, expr);
    }

    /// \brief Visit time variand for time node
    void visit(R& res, CR<sem::Time::TimeVariant> time) {
        visitVariants(res, sem::Time::getTimeKind(time), time);
    }
    ///@}

    /// \name Specializations for inner objects of sem link
    ///@{
    void visit(R& res, CR<sem::Link::Id> id) {
        __obj_field(res, id, text);
    }

    void visit(R& res, CR<sem::Link::Footnote> id) {
        __obj_field(res, id, target);
    }

    void visit(R& res, CR<sem::Link::Raw> raw) {
        __obj_field(res, raw, text);
    }

    void visit(R& res, CR<sem::Link::File> raw) {
        __obj_field(res, raw, file);
    }

    void visit(R& res, CR<sem::Link::Person> raw) {
        __obj_field(res, raw, name);
    }

    void visit(R& res, CR<sem::Link::Data> data) {
        visitVariants(res, sem::Link::getLinkKind(data), data);
    }
    ///@}

    /// \name Specializations for inner details of the subtree log visit
    /// @{
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
        visitVariants(res, sem::SubtreeLog::getLogKind(entry), entry);
    }
    ///@}

    /// \name Specialization for nested include objects
    /// @{
    void visit(R& res, CR<sem::Include::Example> p) {}

    void visit(R& res, CR<sem::Include::Export> p) {}

    void visit(R& res, CR<sem::Include::Src> p) {}

    void visit(R& res, CR<sem::Include::OrgDocument> p) {}

    void visit(R& res, CR<sem::Include::Data> prop) {
        visitVariants(res, sem::Include::getIncludeKind(prop), prop);
    }
    /// @}

    void visit(R& res, CR<sem::DocumentOptions::TocExport> prop) {
        visitVariants(res, static_cast<int>(prop.index()), prop);
    }

    void visit(R& res, CR<sem::Symbol::Param> param) {
        __obj_field(res, param, key);
        __obj_field(res, param, value);
    }

    /// \name Specialization for nested subtree objects and subtree itself
    ///@{
    void visit(R& res, CR<sem::Subtree::Property::Ordered> p) {
        __obj_field(res, p, isOrdered);
    }

    void visit(R& res, CR<sem::Subtree::Property::Origin> p) {
        __obj_field(res, p, text);
    }

    void visit(R& res, CR<sem::Subtree::Property::Effort> p) {
        __obj_field(res, p, hours);
        __obj_field(res, p, minutes);
    }

    void visit(R& res, CR<sem::Subtree::Property::Visibility> p) {
        __obj_field(res, p, level);
    }

    void visit(R& res, CR<sem::Subtree::Property::ExportOptions> p) {
        __obj_field(res, p, backend);
        __obj_field(res, p, values);
    }

    void visit(R& res, CR<sem::Subtree::Property::ExportLatexClass> p) {
        __obj_field(res, p, latexClass);
    }

    void visit(R& res, CR<sem::Subtree::Property::ExportLatexHeader> p) {
        __obj_field(res, p, header);
    }

    void visit(R& res, CR<sem::Subtree::Property::ExportLatexCompiler> p) {
        __obj_field(res, p, compiler);
    }

    void visit(R& res, CR<sem::Subtree::Property::Nonblocking> o) {
        __obj_field(res, o, isBlocking);
    }

    void visit(R& res, CR<sem::Subtree::Property::Blocker> o) {
        __obj_field(res, o, blockers);
    }

    void visit(R& res, CR<sem::Subtree::Property::Trigger> trigger) {}
    void visit(R& res, CR<sem::Subtree::Property::Unnumbered> trigger) {}
    void visit(R& res, CR<sem::Subtree::Property::Created> created) {
        __obj_field(res, created, time);
    }

    void visit(R& res, CR<sem::Subtree::Property> prop) {
        __obj_field(res, prop, data);
        __obj_field(res, prop, mainSetRule);
        __obj_field(res, prop, subSetRule);
        __obj_field(res, prop, inheritanceMode);
    }

    void visit(R& res, CR<sem::Subtree::Property::Data> prop) {
        visitVariants(res, sem::Subtree::Property::getKind(prop), prop);
    }


    ///@}


#undef __field
};
