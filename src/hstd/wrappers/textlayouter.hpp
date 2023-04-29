#ifndef TEXTLAYOUTER_HPP
#define TEXTLAYOUTER_HPP
#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/system/aux_utils.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/dod_base.hpp>
#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Opt.hpp>

namespace layout {

DECL_ID_TYPE_MASKED(LytStr, LytStrId, u64, 8);

struct LytStr {
    using id_type = LytStrId;
    /// Single layout string object. It contains all the information
    /// required to perform the layout and refer back to the original
    /// string piece if needed.
    LytStrId id; /// Id of the original piece of text
    int len; /// It's length in units (units are specified - can be ASCII
             /// or
    /// unicode or anything else)
};

struct LytStrSpan {
    /// Span of multiple layout strings
    Vec<LytStr> strs;
    int         len;
};

struct LayoutElement;
struct Layout;

template <typename T>
struct SharedPtrApi
    : public std::enable_shared_from_this<SharedPtrApi<T>>
    , public CRTP_this_method<T> {
    using CRTP_this_method<T>::_this;
    template <typename... Args>
    static std::shared_ptr<T> shared(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    std::shared_ptr<T> clone_this() {
        return std::make_shared<T>(*_this());
    }

    using Ptr = std::shared_ptr<T>;
};

struct Layout : public SharedPtrApi<Layout> {
    Vec<SPtr<LayoutElement>> elements;
    Layout() = default;
    Layout(CR<Vec<SPtr<LayoutElement>>> elements) : elements(elements) {}
};


/// An element of a layout object - a directive to the console.
///
/// This object sports a collection of static methods, each of which
/// returns an anonymous function invoking a method of the console to
/// which it is applied.
///
/// Refer to the corresponding methods of the Console object for
/// descriptions of the methods involved.
struct LayoutElement : public SharedPtrApi<LayoutElement> {
    /// These are types for formatting text. Text formatting doesn't have a
    /// perfect solution that works in all cases and we have to resort to
    /// heuristics to choose the most approriate text layout on a case by
    /// case basis.
    ///
    /// Text is initially described via a DSL as a set of blocks
    /// (Block). When it's time to output the text a layout (Layout)
    /// determines the exact strings (Str) to output. Text layout
    /// requires heuristics to choose between various options we use a
    /// solver
    /// ('Solution') which is used to determine the precise layout
    /// choosen for a given block.
    struct String {
        LytStrSpan text;
    };

    struct Newline {};

    struct LayoutPrint {
        SPtr<Layout> layout;
    };

    struct NewlineSpace {
        int spaceNum = 0;
    };

    SUB_VARIANTS(
        Kind,
        Data,
        data,
        getKind,
        String,
        Newline,
        LayoutPrint,
        NewlineSpace);
    Data data;
    int  id;
    bool indent;

    LayoutElement(CR<Data> data) : data(data) {}
};

struct Event {
    struct Text {
        LytStr str;
    };

    struct Spaces {
        int spaces;
    };

    struct Newline {};

    SUB_VARIANTS(Kind, Data, data, getKind, Text, Spaces, Newline);
    Data data;
};

struct Block;

struct FormatPolicy {
    std::function<Vec<Vec<SPtr<Block>>>(Vec<Vec<SPtr<Block>>>)>
        breakElementLines; /// Hook
};

struct Options {
    int leftMargin;  /// position of the first right margin. Expected 0
    int rightMargin; /// position of the second right margin. Set for 80
    /// to wrap on default column limit.
    float leftMarginCost; /// cost (per character) beyond margin 0.
    /// Expected value ~0.05
    float rightMarginCost; /// cost (per character) beyond margin 1. Should
    /// be much higher than c0. Expected value
    /// ~100
    int   linebreakCost; /// cost per line-break
    int   indentSpaces;  /// spaces per indent
    float cpack; /// cost (per element) for packing justified layouts.
    /// Expected value ~0.001
    FormatPolicy formatPolicy;
};

struct Solution : public SharedPtrApi<Solution> {
    /// A Solution object effectively maps an integer (the left margin at
    /// which the solution is placed) to a layout notionally optimal for
    /// that margin, together with cost information used to evaluate the
    /// layout. For compactness, the map takes the form of a
    /// piecewise-linear cost function, with associated layouts.
    ///
    /// This object corresponds to a cost function in the main article.
    /// Layout is constructed from this function.

    Vec<int> knots; /// a list of ints, specifying the margin settings at
    /// which the layout changes. Note that the first knot is required to
    /// be 0.
    Vec<int> spans; /// a list of ints, giving for each knot, the width of
    /// the corresponding layout in characters.
    Vec<float> intercepts; /// constant cost associated with each knot -
    /// computed cost of the outputting this layout solution at each know
    /// in the knots list
    Vec<float> gradients; /// at each knot, the rate with which the layout
    /// cost increases with an additional margin indent of 1 character.
    Vec<SPtr<Layout>> layouts; /// the Layout objects expressing the
                               /// optimal
    /// layout between each knot.
    int index = 0;

    void         reset() { index = 0; }
    void         advance() { ++index; }
    void         retreat() { --index; }
    int          curKnot() const { return knots[index]; }
    int          curSpan() const { return spans[index]; }
    float        curIntercept() const { return intercepts[index]; }
    float        curGradient() const { return gradients[index]; }
    SPtr<Layout> curLayout() const { return layouts[index]; }
    int          curIndex() const { return index; }


    Solution() = default;
    Solution(
        CR<Vec<int>>          knots,
        CR<Vec<int>>          spans,
        CR<Vec<float>>        intercepts,
        CR<Vec<float>>        gradients,
        CR<Vec<SPtr<Layout>>> layouts)
        : knots(knots)
        , spans(spans)
        , intercepts(intercepts)
        , gradients(gradients)
        , index(0) {}

    /// The value (cost) extrapolated for margin m from the current knot.
    /// Since a LytSolution's cost is represented by a piecewise linear
    /// function, the extrapolation in this case is linear, from the
    /// current knot.
    float curValueAt(int margin) {
        return curIntercept() + curGradient() * float(margin - curKnot());
    }

    Solution::Ptr plusConst(float val) {
        /// Add a constant to all values of this Solution::Ptr.
        Solution::Ptr result = clone_this();
        for (auto& a : result->intercepts) {
            a += val;
        }
        return result;
    }

    /// The knot after the once currently indexed.
    int nextKnot();

    /// Adjust the index so m falls between the current knot and the next.
    void moveToMargin(int margin);

    /// Add a segment to a LytSolution under construction.
    ///
    /// The function performs basic consistency checks, and eliminates
    /// redundant segments that are linear extrapolations of those that
    /// precede them.
    void add(
        int         knot,
        int         span,
        float       intercept,
        float       gradient,
        Layout::Ptr layout);
};

struct Block : public SharedPtrApi<Block> {
    struct Verb {
        Vec<LytStrSpan> textLines;
        bool            firstNl;
    };

    struct Text {
        LytStrSpan text;
    };

    struct Wrap {
        Opt<LytStr>     prefix;
        LytStr          sep;
        Vec<Block::Ptr> wrapElements;
    };

    struct Stack {
        Vec<Block::Ptr> elements;
    };

    struct Choice {
        Vec<Block::Ptr> elements;
    };

    struct Line {
        Vec<Block::Ptr> elements;
    };

    struct Empty {};
    SUB_VARIANTS(
        Kind,
        Data,
        data,
        getKind,
        Verb,
        Text,
        Wrap,
        Stack,
        Choice,
        Line,
        Empty);

    struct SolutionHash {
        template <typename T>
        std::size_t operator()(CR<Opt<T>> opt) const {
            if (opt) {
                return operator()(*opt);
            } else {
                return 0;
            }
        }

        template <typename T>
        std::size_t operator()(CR<Vec<T>> items) const {
            qFatal("TODO");
        }

        std::size_t operator()(CR<Solution>) const { qFatal("TODO"); }

        template <typename T>
        std::size_t operator()(CR<SPtr<T>> opt) const {
            qFatal("TODO");
        }
    };

    UnorderedMap<Opt<Solution::Ptr>, Opt<Solution::Ptr>, SolutionHash>
         layoutCache;
    bool isBreaking; /// Whether or not this block should end the line
    int  breakMult;  /// Local line break cost change
    Data data;
};


struct OutConsole {
    int      leftMargin;
    int      rightMargin;
    int      hPos; /// Horizontal position on the output console
    Vec<int> margins;

    int  margin() const { return margins.back(); }
    void addMargin(int m) { margins.push_back(m); }
    void popMargin(int m) { margins.pop_back(); }
};


} // namespace layout

#endif // TEXTLAYOUTER_HPP
