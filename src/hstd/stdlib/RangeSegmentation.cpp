#include <hstd/stdlib/RangeSegmentation.hpp>
#include <hstd/stdlib/RangeTree.hpp>
#include <hstd/stdlib/Set.hpp>

Vec<SequenceAnnotation> annotateSequence(
    const Vec<SequenceSegmentGroup>& groups,
    int                              first,
    int                              last) {

    struct GroupTree {
        RangeTree<int>       tree;
        SequenceSegmentGroup group;
    };

    Vec<GroupTree> trees;

    for (auto const& g : groups) {
        Vec<Slice<int>> slices;
        for (auto const& s : g.segments) {
            slices.push_back(slice(s.first, s.last));
        }

        trees.push_back(GroupTree{
            .group = g,
            .tree  = RangeTree<int>(slices),
        });
    }

    using SegmentKind = Pair<int, int>; // group kind, segment Kind

    auto getPointGroups = [&](int point) -> UnorderedSet<SegmentKind> {
        UnorderedSet<SegmentKind> groups;
        for (auto const& tree : trees) {
            if (auto sliceIndex = tree.tree.getRangeIndex(point)) {
                groups.incl(std::make_pair(
                    tree.group.kind,
                    tree.group.segments.at(sliceIndex.value()).kind));
            }
        }
        return groups;
    };

    UnorderedSet<SegmentKind> prevKind  = getPointGroups(first);
    int                       lastStart = first;

    Vec<SequenceAnnotation> result;

    auto getAnnotations = [&]() {
        Vec<SequenceAnnotationTag> annotations;
        for (auto const& [group_Kind, segment_Kind] : prevKind) {
            annotations.push_back(SequenceAnnotationTag{
                .groupKind   = group_Kind,
                .segmentKind = segment_Kind,
            });
        }
        return annotations;
    };

    for (int i = first; i <= last; ++i) {
        auto thisKind = getPointGroups(i);
        if (thisKind != prevKind) {
            if (!prevKind.empty()) {
                result.push_back(SequenceAnnotation{
                    .first       = lastStart,
                    .last        = i - 1,
                    .annotations = getAnnotations(),
                });
            }

            prevKind  = thisKind;
            lastStart = i;
        }
    }

    if (lastStart < last && !prevKind.empty()) {
        result.push_back(SequenceAnnotation{
            .first       = lastStart,
            .last        = last,
            .annotations = getAnnotations(),
        });
    }

    return result;
}

bool SequenceAnnotation::isAnnotatedWith(int groupKind, int segmentKind)
    const {
    for (auto const& a : annotations) {
        if (a.groupKind == groupKind && a.segmentKind == segmentKind) {
            return true;
        }
    }

    return false;
}
