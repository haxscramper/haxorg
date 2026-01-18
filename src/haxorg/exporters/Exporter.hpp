#pragma once

#include <haxorg/sem/SemOrg.hpp>
#include <boost/mp11.hpp>
#include <hstd/stdlib/TraceBase.hpp>

using boost::mp11::mp_for_each;
using namespace boost::describe;

namespace org::algo {
struct ExporterEventBase : hstd::OperationsTracer {
    struct VisitReport : hstd::OperationsMsg {
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
            VisitVariant,
            Print);

        Kind                            kind;
        hstd::Opt<sem::SemId<sem::Org>> node = std::nullopt;
        hstd::Opt<std::string>          field;
        bool                            isStart = true;
        hstd::Opt<std::string>          type;
        bool                            instant = false;

        VisitReport& with_loc(
            int         line     = __builtin_LINE(),
            char const* function = __builtin_FUNCTION()) {
            this->line     = line;
            this->function = function;
            return *this;
        }


        template <typename T>
        VisitReport& with_value(T const& value) {
            this->type = hstd::value_metadata<T>::typeName();
            return *this;
        }

        VisitReport& with_level(int level) {
            this->level = level;
            return *this;
        }

        VisitReport& with_node(sem::SemId<sem::Org> node) {
            this->node = node;
            return *this;
        }

        VisitReport& with_field(std::string field) {
            this->field = field;
            return *this;
        }

        VisitReport& with_type(std::string type) {
            this->type = type;
            return *this;
        }

        VisitReport& with_msg(std::string msg) {
            this->msg = msg;
            return *this;
        }
    };

    void report(VisitReport const& event);

    struct VisitScope {
        ExporterEventBase* exp;
        VisitReport        event;
        VisitScope(ExporterEventBase* exporter, VisitReport event)
            : exp(exporter), event(event) {
            if (exp->TraceState) {
                event.level   = exp->activeLevel;
                event.isStart = true;
                exp->report(event);
                ++exp->activeLevel;
            }
        }

        ~VisitScope() {
            if (exp->TraceState) {
                --exp->activeLevel;
                if (!event.instant) {
                    event.level   = exp->activeLevel;
                    event.isStart = false;
                    exp->report(event);
                }
            }
        }
    };

    VisitScope trace_instant(VisitReport report) {
        report.instant = true;
        return VisitScope{this, report};
    }

    VisitScope trace_scope(VisitReport report) {
        report.instant = false;
        return VisitScope{this, report};
    }

    VisitReport trace(
        VisitReport::Kind kind,
        int               line     = __builtin_LINE(),
        char const*       function = __builtin_FUNCTION()) {
        return VisitReport{
            hstd::OperationsMsg{
                .function = function,
                .line     = line,
            },
            .kind = kind,
        };
    }
};

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
template <typename V, typename R = std::monostate>
struct Exporter : ExporterEventBase {


#define __EXPORTER_USING_DEFINE(__Kind)                                   \
    using __ExporterBase::visit##__Kind;

    template <typename T>
    using In = sem::SemId<T>;

    using export_type = R;
    using crtp_type   = V;


#define EXPORTER_USING()                                                  \
    using __ExporterBase::visitField;                                     \
    using __ExporterBase::visitSubnode;                                   \
    using __ExporterBase::pushVisit;                                      \
    using __ExporterBase::popVisit;                                       \
    using __ExporterBase::visit;                                          \
    using __ExporterBase::visitDispatchHook;                              \
    using __ExporterBase::visitStart;                                     \
    using __ExporterBase::visitEnd;                                       \
    using __ExporterBase::evalTop;                                        \
    using __ExporterBase::In;                                             \
    using __ExporterBase::export_type;                                    \
    using __ExporterBase::crtp_type;                                      \
    EACH_SEM_ORG_KIND(__EXPORTER_USING_DEFINE)

    void visitField(R& arg, const char* name, sem::SemId<sem::Org> org);

    void visitSubnode(R& tmp, int, sem::SemId<sem::Org> val);

    /// \brief Create default instance of the new result type
    R newRes(sem::SemId<sem::Org>) {
        return hstd::SerdeDefaultProvider<R>::get();
    }


    /// \brief Additional hook that is called for each node before
    /// descending into specifically named overload
    void visitDispatchHook(R&, sem::SemId<sem::Org>) {}
    /// \brief Start of the top-level visit, triggered in `visitTop`
    void visitStart(sem::SemId<sem::Org> node) {
        trace_instant(
            trace(VisitReport::Kind::VisitStart).with_node(node));
    }
    /// \brief End of the top-level visit, triggered in the `visitTop`
    void visitEnd(sem::SemId<sem::Org> node) {
        trace_instant(trace(VisitReport::Kind::VisitEnd).with_node(node));
    }

    /// \brief Main dispatch implementation for all sem types. Dispatch
    /// happens based on the kind of the provided sem node and not it's
    /// RTTI type.
    void visitDispatch(R& res, sem::SemId<sem::Org> arg);

    template <org::sem::NotOrg T>
    void visitDescribedOrgFields(R& res, T const& value);

    template <org::sem::IsOrg T>
    void visitDescribedOrgFields(R& res, In<T> tree);

    /// \brief Hook called each time new sem node is visited using specific
    /// visitator hook. Used in default implementation of the
    /// `visitDispatch`
    ///
    /// \brief Pop visit after sem visit dispatch completed


    void pushVisit(R& res, sem::SemId<sem::Org> arg) {
        trace_instant(trace(VisitReport::Kind::PushVisit).with_node(arg));
    }

    void popVisit(R& res, sem::SemId<sem::Org> arg) {
        trace_instant(trace(VisitReport::Kind::PopVisit).with_node(arg));
    }

    /// \brief Default implementation of the visitation function for sem
    /// nodes
    ///
    /// Providing more specialized overload for visitation can be done
    /// using `visit(R, In<sem::MoreSpecificNodeType>)` or
    /// `visitMoreSpecificNodeType`. Former will also bypass all push/pop
    /// hooks while the latter will only override core functionality of the
    /// dispatch.
    void visit(R& res, sem::SemId<sem::Org> arg) {
        visitDispatch(res, arg);
    }

    /// \brief Default implementation of the top visit
    ///
    /// User can redefined this function as well, or provided it's own
    /// implementation.
    R evalTop(sem::SemId<sem::Org> org);


    V* _this() { return static_cast<V*>(this); }

    template <typename T>
    void visitFieldRedirect(R& res, char const* name, T const& value) {
        auto __scope = trace_scope(trace(VisitReport::Kind::VisitField)
                                       .with_field(name)
                                       .with_value(value));
        _this()->visitField(res, name, value);
    }


    template <typename T, typename Kind>
    void visitVariants(R& res, Kind kind, T const& var);

    void visit(R& res, hstd::UserTime const& time);
    void visit(R& res, org::sem::OrgJson const& time);
    void visit(R& res, org::parse::SourceLoc const& time);
    void visit(R& res, org::parse::SourceFileId const& time);
    void visit(R& res, float const& time);
    void visit(
        R&                                                      res,
        hstd::Variant<In<sem::Time>, In<sem::TimeRange>> const& range);

#include "ExporterMethods.tcc"
};

} // namespace org::algo
