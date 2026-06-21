/// \file RangeSegmentation.hpp
///
/// \brief Segment a sequence of values between `[first, last]` into blocks
/// with continuous kinds.

#pragma once

#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Pair.hpp>

#pragma clang diagnostic ignored "-Wunknown-attributes"

namespace hstd {

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

    DESC_FIELDS(SequenceSegment, (kind, first, last));
};

/// \brief Input segment group
struct [[refl]] SequenceSegmentGroup {
    /// \brief An kind of the segment group, does not have to be unique
    [[refl]] int kind;
    /// \brief List of input segments for grouping
    [[refl]] Vec<SequenceSegment> segments;

    DESC_FIELDS(SequenceSegmentGroup, (kind, segments));
};

/// \brief Output segment annotation
struct [[refl]] SequenceAnnotationTag {
    /// \brief ID of the original group this segment came from
    [[refl]] int groupKind;
    /// \brief ID of the segment in this group.
    ///
    /// Segment kinds are constructed from all ranges
    /// that overlap points in the segment.
    ///
    /// In the example below, there are 3 separate slices, `[2,3]`, `[1,4]`
    /// and finally `[6,7]`. The resulting segmentation will have 4
    /// different sequence segments from these ranges. The first one is
    /// `[1,1]`, then `[2,3]`, `[4]`, and `[6,7]`.
    ///
    /// ```
    /// 0
    /// 1   |
    /// 2 | |
    /// 3 | |
    /// 4   |
    /// 5
    /// 6   |
    /// 7   |
    /// ```
    [[refl]] Vec<int> segmentKinds;

    DESC_FIELDS(SequenceAnnotationTag, (groupKind, segmentKinds));
};

/// \brief Annotated chunk of the original sequence
struct [[refl]] SequenceAnnotation {
    /// \brief Inclusive left boundary for the sequence segment annotation
    [[refl]] int first;
    ///  \brief Inclusive right boundary for the sequence segment
    [[refl]] int last;
    /// \brief Full list of all annotated segments.
    [[refl]] Vec<SequenceAnnotationTag> annotations;

    /// \brief Check if the segment is annotated with a given group kind
    /// and a segment kind.
    [[refl]] bool isAnnotatedWith(int groupKind, int segmentKind) const;

    DESC_FIELDS(SequenceAnnotation, (first, last, annotations));

    Slice<int> slice() const { return ::hstd::slice(first, last); }
};


/// \brief Return a flat list of annotated chunks for an inclusive range in
/// `[first, last]`. Use the incoming list of sequence elements.
[[refl]] Vec<SequenceAnnotation> annotateSequence(
    Vec<SequenceSegmentGroup> const& groups,
    int                              first,
    int                              last);

} // namespace hstd
