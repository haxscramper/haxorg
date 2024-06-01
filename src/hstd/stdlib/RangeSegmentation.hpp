/// \file RangeSegmentation.hpp
///
/// \brief Segment a sequence of values between `[first, last]` into blocks
/// with continuous kinds.

#pragma once

#include <vector>

/// \brief Input segment.
struct [[refl]] SequenceSegment {
    /// \brief Kind of the segment, does not have to be unique for all
    /// segments, and different sequence segment groups can have segments
    /// with identical kinds.
    [[refl]] int kind;

    /// \brief Inclusive left boundary of the segment. Mustnot overlap with
    /// other segments' boundaries,but can be identical to the `last`,
    /// to create a point segment (spans 1 element).
    [[refl]] int first;

    /// \brief Inclusive right boundary for the segment
    [[refl]] int last;
};

/// \brief Input segment group
struct [[refl]] SequenceSegmentGroup {
    /// \brief An kind of the segment group, does not have to be unique
    [[refl]] int kind;
    /// \brief List of input segments for grouping
    [[refl]] std::vector<SequenceSegment> segments;
};

/// \brief Output segment annotation
struct [[refl]] SequenceAnnotationTag {
    /// \brief ID of the original group this segment came from
    [[refl]] int groupKind;
    /// \brief ID of the segment in this group.
    [[refl]] int segmentKind;
};

/// \brief Annotated chunk of the original sequence
struct [[refl]] SequenceAnnotation {
    /// \brief Inclusive left boundary for the sequence segment annotation
    [[refl]] int first;
    ///  \brief Inclusive right boundary for the sequence segment
    [[refl]] int last;
    /// \brief Full list of all annotated segments.
    [[refl]] std::vector<SequenceAnnotationTag> annotations;

    /// \brief Check if the segment is annotated with a given group kind
    /// and a segment kind.
    bool isAnnotatedWith(int groupKind, int segmentKind) const;
};


/// \brief Return a flat list of annotated chunks for an inclusive range in
/// `[first, last]`. Use the incoming list of sequence elements.
[[refl]] std::vector<SequenceAnnotation> annotateSequence(
    std::vector<SequenceSegmentGroup> const& groups,
    int                                      first,
    int                                      last);
