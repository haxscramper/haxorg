#pragma once

import org.sem.SemOrg;

struct QDataStream {};

struct SemDataStream {
    void read(QDataStream& in, sem::ContextStore* store);
    void write(QDataStream& out, sem::ContextStore const& store);
    void read(
        QDataStream&       in,
        sem::ContextStore* store,
        sem::SemId*        rootNode);
    void write(
        QDataStream&             out,
        sem::ContextStore const& store,
        sem::SemId const&        rootNode);
    void read(QDataStream& in, sem::ParseUnitStore& store);
    void write(QDataStream& out, sem::ParseUnitStore const& store);
};
