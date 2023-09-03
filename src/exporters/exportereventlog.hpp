#pragma once

#include <exporters/Exporter.hpp>
#include <hstd/stdlib/Func.hpp>

struct ExporterEventLog : public Exporter<ExporterEventLog, int> {
    using Base = Exporter<ExporterEventLog, int>;
#define __ExporterBase Base
    EXPORTER_USING()
#undef __ExporterBase

    template <typename T>
    int newRes(T const&) {
        return 0;
    }

    template <typename T>
    void visitField(int&, const char*, CR<T>) {}

    struct Event {
        struct KindBase {
            DECL_FIELDS(
                KindBase,
                (),
                ((sem::SemId), original, sem::SemId::Nil()),
                ((sem::SemIdT<sem::Time>),
                 time,
                 sem::SemIdT<sem::Time>::Nil()));
        };

        struct SubtreeCreated : KindBase {
            DECL_FIELDS(SubtreeCreated, (KindBase));
        };

        struct ListLogWritten : KindBase {
            DECL_FIELDS(
                ListLogWritten,
                (KindBase),
                ((sem::SemIdT<sem::ListItem>),
                 item,
                 sem::SemIdT<sem::ListItem>::Nil()));
        };

        struct SubtreeLogWritten : KindBase {
            DECL_FIELDS(SubtreeLogWritten, (KindBase));
        };

        struct TagAssigned : KindBase {
            DECL_FIELDS(TagAssigned, (KindBase));
        };

        struct TagRemoved : KindBase {
            DECL_FIELDS(TagRemoved, (KindBase));
        };

        struct SubtreeRescheduled : KindBase {
            DECL_FIELDS(SubtreeRescheduled, (KindBase));
        };

        struct SubtreeRefiled : KindBase {
            DECL_FIELDS(SubtreeRefiled, (KindBase));
        };

        struct SubtreeScheduled : KindBase {
            DECL_FIELDS(SubtreeScheduled, (KindBase));
        };

        /// \brief Clock started in the subtree -- without completion
        /// information
        struct ClockStarted : KindBase {
            DECL_FIELDS(ClockStarted, (KindBase));
        };
        /// \brief Clock ended in the subtree -- with start and end
        /// completion information.
        ///
        /// This represents a fully completed clock instances whereas
        /// `ClockStarted` might only represent a dangling clock. Fully
        /// completed clock is represented as 'started-completed' pair in
        /// the log export
        struct ClockCompleted : KindBase {
            DECL_FIELDS(
                ClockCompleted,
                (KindBase),
                ((sem::SemIdT<sem::Time>),
                 at,
                 sem::SemIdT<sem::Time>::Nil()));
        };

        struct SubtreeStateAssigned : KindBase {
            DECL_FIELDS(SubtreeStateAssigned, (KindBase));
        };

        struct SubtreeClosed : KindBase {
            DECL_FIELDS(SubtreeClosed, (KindBase));
        };

        SUB_VARIANTS(
            Kind,
            Data,
            data,
            getKind,
            SubtreeCreated,
            ListLogWritten,
            SubtreeLogWritten,
            SubtreeRescheduled,
            SubtreeRefiled,
            TagRemoved,
            SubtreeScheduled,
            ClockStarted,
            ClockCompleted,
            SubtreeStateAssigned,
            SubtreeClosed,
            TagAssigned);

        Data data;
        Event(Data const& data) : data(data) {}
        sem::SemIdT<sem::Time> getTime() const {
            return std::visit(
                [](auto const& it) { return it.time; }, data);
        }
    };

    using LogConsumer = Func<void(Event const&)>;

    LogConsumer logConsumer;

    void visitSubtree(int&, In<sem::Subtree> tree);
    void visitListItem(int&, In<sem::ListItem> item);

    void visitSubnodes(CR<Vec<sem::SemId>> ids);
    void visitField(int&, const char*, CR<Vec<sem::SemId>> ids) {
        visitSubnodes(ids);
    }

    void log(Event const& event);
    void log(Event::Data const& event) { log(Event(event)); }
};

extern template class Exporter<ExporterEventLog, int>;
