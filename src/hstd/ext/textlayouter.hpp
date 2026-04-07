#ifndef TEXTLAYOUTER_HPP
#define TEXTLAYOUTER_HPP

#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/system/aux_utils.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/dod_base.hpp>
#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/system/generator.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Func.hpp>
#include <hstd/stdlib/Str.hpp>


/// \brief Text block layouts used in exporters and code generation
namespace hstd::layout {

DECL_ID_TYPE_MASKED(LytStr, LytStrId, u64, 8);
DECL_ID_TYPE_MASKED(Block, BlockId, u64, 8);

inline const auto LytSpacesId = LytStrId::FromValue(
    value_domain<int>::high() - 120);

/// Single layout string object. It contains all the information
/// required to perform the layout and refer back to the original
/// string piece if needed.
struct LytStr {
    using id_type = LytStrId;

    LytStrId id = LytStrId::Nil(); /// Id of the original piece of text
    int len     = 0; /// It's length in units (units are specified - can be
                     /// ASCII or unicode or anything else)

    LytStr() = default;
    LytStr(LytStrId id, int len) : id(id), len(len) {}
    LytStr(int idx, int len) : id(LytStrId(idx)), len(len) {}
    int  toIndex() const { return id.getIndex(); }
    bool isSpaces() const { return id == LytSpacesId; }
    bool operator==(LytStr const& s) const {
        return id == s.id && len == s.len;
    }
};

BOOST_DESCRIBE_STRUCT(LytStr, (), (id, len));

inline const auto LytEmptyStr = LytStr(LytStrId::Nil(), 0);

struct LytStrSpan {
    /// Span of multiple layout strings
    Vec<LytStr> strs;
    int         len = 0;
    LytStrSpan()    = default;
    LytStrSpan(LytStr const& str) : strs({str}), len(str.len) {}
    LytStrSpan(Vec<LytStr> const& strs) : strs(strs) {
        for (const auto& str : strs) { len += str.len; }
    }
};

BOOST_DESCRIBE_STRUCT(LytStrSpan, (), (strs, len));

struct LayoutElement;
struct Layout;


struct Layout : public SharedPtrApi<Layout> {
    Vec<SPtr<LayoutElement>> elements;
    Layout() = default;
    Layout(Vec<SPtr<LayoutElement>> const& elements)
        : elements(elements) {}
    Layout(Span<SPtr<LayoutElement>> const& elements)
        : elements(Vec<SPtr<LayoutElement>>(elements)) {}
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
    int  id     = 0;
    bool indent = false;

    LayoutElement(Data const& data) : data(data) {}

    static Ptr newline() { return shared(Newline()); }
    static Ptr string(String const& str) { return shared(str); }
};


struct Event {
    struct Text {
        LytStr str;
        bool   operator==(Text const& s) const { return str == s.str; }
    };


    struct Spaces {
        int  spaces;
        bool operator==(Spaces const& s) const {
            return spaces == s.spaces;
        }
    };


    struct Newline {
        bool operator==(Newline const&) const { return true; }
    };


    bool operator==(Event const& other) const {
        return data == other.data;
    }

    SUB_VARIANTS(Kind, Data, data, getKind, Text, Spaces, Newline);
    Data data;
    Event(Data const& data) : data(data) {}
    Event() = default;
};

BOOST_DESCRIBE_STRUCT(Event::Text, (), (str));
BOOST_DESCRIBE_STRUCT(Event::Spaces, (), (spaces));
BOOST_DESCRIBE_STRUCT(Event::Newline, (), ());


struct Block;


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
        Vec<int> const&          knots,
        Vec<int> const&          spans,
        Vec<float> const&        intercepts,
        Vec<float> const&        gradients,
        Vec<SPtr<Layout>> const& layouts)
        : knots(knots)
        , spans(spans)
        , intercepts(intercepts)
        , gradients(gradients)
        , layouts(layouts)
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
        for (auto& a : result->intercepts) { a += val; }
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

struct Options;
struct BlockStore;

struct Block {
    using id_type = BlockId;
    struct Verb {
        Vec<LytStrSpan> textLines;
        bool            firstNl;
    };

    struct Text {
        LytStrSpan text;
    };

    struct Wrap {
        Opt<LytStr>  prefix;
        LytStr       sep;
        Vec<BlockId> wrapElements;
    };

    struct Stack {
        Vec<BlockId> elements;
    };

    struct Choice {
        Vec<BlockId> elements;
    };

    struct Line {
        Vec<BlockId> elements;
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

    int  size() const;
    int  leafCount(BlockStore const& store) const;
    void add(BlockId const& other);
    void add(CVec<BlockId> others);

    struct SolutionHash {
        template <typename T>
        std::size_t operator()(Opt<T> const& opt) const {
            if (opt) {
                return operator()(*opt);
            } else {
                return 0;
            }
        }

        template <typename T>
        std::size_t operator()(Vec<T> const& items) const {
            logic_todo_impl();
        }

        std::size_t operator()(Solution const&) const {
            logic_todo_impl();
        }

        template <typename T>
        std::size_t operator()(SPtr<T> const& opt) const {
            LOGIC_ASSERTION_CHECK(opt != nullptr, "");
            return std::hash<T*>{}(opt.get());
        }
    };

    UnorderedMap<Opt<Solution::Ptr>, Opt<Solution::Ptr>, SolutionHash>
         layoutCache;
    bool isBreaking = false; /// Whether or not this block should end the
                             /// line
    int  breakMult = 1;      /// Local line break cost change
    Data data;

    Block() = default;
    Block(Data const& data) : data(data) {}
};


struct BlockStore {
    dod::Store<BlockId, Block> store;

    Block&  at(BlockId const& id) { return store.at(id); }
    void    add_at(BlockId const& id, BlockId const& next);
    void    add_at(BlockId const& id, Vec<BlockId> const& next);
    BlockId text(LytStrSpan const& t);
    BlockId line(Vec<BlockId> const& l = {});
    BlockId stack(Vec<BlockId> const& l = {});
    BlockId choice(Vec<BlockId> const& l = {});
    BlockId space(int count);
    BlockId empty() { return store.add(Block(Block::Empty{})); }
    BlockId spatial(bool isVertical, Vec<BlockId> const& l = {});
    BlockId wrap(Vec<BlockId> const& elems, LytStr sep, int breakMult = 1);
    BlockId indent(int indent, BlockId const& block, int breakMult = 1);
    BlockId vertical(Vec<BlockId> const& blocks, BlockId const& sep);
    BlockId horizontal(Vec<BlockId> const& blocks, BlockId const& sep);

    BlockId surround_non_empty(
        BlockId content,
        BlockId before,
        BlockId after) {
        if (store.at(content).size() == 0) {
            return space(0);
        } else {
            return line({before, content, after});
        }
    }

    template <typename T, typename F>
    BlockId map_join(
        CVec<T>        items,
        F              convert,
        BlockId const& join,
        bool           isLine     = true,
        bool           isTrailing = false) {
        Vec<BlockId> tmp;
        for (auto const& it : items) { tmp.push_back(convert(it)); }
        return this->join(tmp, join, isLine, isTrailing);
    }

    BlockId join(
        CVec<BlockId>  items,
        BlockId const& join,
        bool           isLine     = true,
        bool           isTrailing = false);


    /// Return all possible formatting layouts for a given block with
    /// provided options. The best layout will be the first in the returned
    /// sequence.
    Vec<Layout::Ptr> toLayouts(BlockId id, Options const& opts);

    /// Return first best formatting layout for a given block. This is the
    /// procedure you should be using unless you need to have access to all
    /// the possible layouts.
    Layout::Ptr toLayout(BlockId id, Options const& opts) {
        Vec<Layout::Ptr> layouts = toLayouts(id, opts);
        LOGIC_ASSERTION_CHECK(!layouts.empty(), "");
        return layouts[0];
    }

    struct TreeReprConf {
        int                           maxDepth = 120;
        Func<std::string(BlockId id)> idText;
    };

    std::string toTreeRepr(BlockId root, TreeReprConf const& conf);
};

struct Options {
    int leftMargin  = 0; /// position of the first right margin. Expected 0
    int rightMargin = 80; /// position of the second right margin. Set for
                          /// 80
    /// to wrap on default column limit.
    float leftMarginCost = 0.05; /// cost (per character) beyond margin 0.
    /// Expected value ~0.05
    float rightMarginCost = 100; /// cost (per character) beyond margin 1.
                                 /// Should be much higher than c0.
                                 /// Expected value ~100
    int   linebreakCost = 5;     /// cost per line-break
    int   indentSpaces  = 2;     /// spaces per indent
    float cpack = 0.001; /// cost (per element) for packing justified
                         /// layouts. Expected value ~0.001


    using FormatPolicy = std::function<
        Vec<Vec<BlockId>>(BlockStore&, Vec<Vec<BlockId>>)>;

    static Vec<Vec<BlockId>> defaultFormatPolicy(
        BlockStore&              store,
        Vec<Vec<BlockId>> const& blc);

    FormatPolicy formatPolicy = defaultFormatPolicy;
};

struct OutConsole {
    int      leftMargin  = 0;
    int      rightMargin = 0;
    int      hPos        = 0; /// Horizontal position on the output console
    Vec<int> margins;

    int  margin() const { return margins.back(); }
    void addMargin(int m) { margins.push_back(m); }
    void popMargin() { margins.pop_back(); }
};

generator<Event> formatEvents(BlockStore& store, Layout::Ptr const& lyt);

struct SimpleStringStore {
    Vec<std::string> strings;
    BlockStore*      store;

    SimpleStringStore(BlockStore* store) : store(store) {}
    LytStr  str(std::string const& str);
    Str     str(LytStr const& str) const;
    Str     toString(BlockId const& blc, Options const& opts = Options{});
    BlockId text(std::string const& arg) { return store->text(str(arg)); }
    BlockId text(LytStr const& s) { return store->text(s); }

    std::string toTreeRepr(BlockId id, bool doRecurse = true);
};


} // namespace hstd::layout

namespace hstd {
template <>
struct SerdeDefaultProvider<layout::BlockId> {
    static layout::BlockId get() { return layout::BlockId::Nil(); }
};
} // namespace hstd

#endif // TEXTLAYOUTER_HPP
