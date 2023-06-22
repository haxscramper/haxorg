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
            sem::SemIdT<sem::Time> time;
            sem::SemId             original;
        };

        struct SubtreeCreated : KindBase {};
        struct ListLogWritten : KindBase {
            sem::SemIdT<sem::ListItem> item;
        };
        struct SubtreeLogWritten : KindBase {};
        struct TagAssigned : KindBase {};
        struct TagRemoved : KindBase {};
        struct SubtreeRescheduled : KindBase {};
        struct SubtreeRefiled : KindBase {};
        struct SubtreeScheduled : KindBase {};
        /// \brief Clock started in the subtree -- without completion
        /// information
        struct ClockStarted : KindBase {};
        /// \brief Clock ended in the subtree -- with start and end
        /// completion information.
        ///
        /// This represents a fully completed clock instances whereas
        /// `ClockStarted` might only represent a dangling clock. Fully
        /// completed clock is represented as 'started-completed' pair in
        /// the log export
        struct ClockCompleted : KindBase {
            sem::SemIdT<sem::Time> at;
        };
        struct SubtreeStateAssigned : KindBase {};
        struct SubtreeClosed : KindBase {};

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
