#include "textlayouter.hpp"
#include <hstd/stdlib/Ranges.hpp>
#include <hstd/system/generator.hpp>
#include <hstd/stdlib/charsets.hpp>
#include <hstd/stdlib/strutils.hpp>
#include <hstd/stdlib/Set.hpp>
#include <algorithm>
#include <absl/log/check.h>

using namespace layout;

const auto infty = 1024 * 1024 * 1024;

bool isInf(int a) { return (infty - 4096 <= a) && (a <= infty + 4096); }

int Solution::nextKnot() {
    if (index + 1 >= knots.size()) {
        return infty;
    } else {
        return knots[index + 1];
    }
}

void Solution::moveToMargin(int margin) {
    if (curKnot() > margin) {
        while (curKnot() > margin) {
            retreat();
        }
    } else {
        while (nextKnot() <= margin && nextKnot() != infty) {
            advance();
        }
    }
}

void Solution::add(
    int         knot,
    int         span,
    float       intercept,
    float       gradient,
    Layout::Ptr layout) {
    if (knots.size() > 0) {
        // Don't add a knot if the new segment is a linear
        // extrapolation of the last.
        int   kLast = knots.back();
        int   sLast = spans.back();
        float iLast = intercepts.back();
        float gLast = gradients.back();

        if (span == sLast && gradient == gLast
            && iLast + (knot - kLast) * gLast == intercept) {
            return;
        }
    }

    if (knot < 0 || span < 0 || intercept < 0 || gradient < 0) {
        throw std::runtime_error(
            ("Internal error: bad layout: (k " + to_string(knot) + ", s "
             + to_string(span) + ", i " + to_string(intercept) + ", g "
             + to_string(gradient) + ")"));
    }

    knots.push_back(knot);
    spans.push_back(span);
    intercepts.push_back(intercept);
    gradients.push_back(gradient);
    layouts.push_back(layout);
}


/// Form the piecewise minimum of a sequence of Solutions.
///
/// Args:
///   solutions: a non-empty sequence of Solution objects
/// Returns:
///   values Solution object whose cost is the piecewise minimum of the
///   Solutions provided, and which associates the minimum-cost layout with
///   each piece.
Opt<Solution::Ptr> minSolution(Vec<Solution::Ptr> solutions) {
    if (solutions.size() == 1) {
        return solutions[0];
    }

    Solution::Ptr factory = Solution::shared();
    for (auto& s : solutions) {
        s->reset();
    }

    int n            = solutions.size();
    int kL           = 0;
    int lastIMinSoln = -1; // Index of the last minimum solution
    int lastIndex    = -1; // Index of the current knot in the last minimum
                           // solution

    while (kL < infty) {
        Vec<Solution::Ptr>::iterator min = std::min_element(
            solutions.begin(),
            solutions.end(),
            [](CR<Solution::Ptr> lhs, CR<Solution::Ptr> rhs) {
                return lhs->nextKnot() < rhs->nextKnot();
            });

        int        kH = (**min).nextKnot() - 1;
        Vec<float> gradients;
        for (const auto& s : solutions) {
            gradients.push_back(s->curGradient());
        }

        while (true) {
            Vec<float> values;
            for (const auto& s : solutions) {
                values.push_back(s->curValueAt(kL));
            }

            auto minIt = std::min_element(
                std::begin(values),
                std::end(values),
                [](const float& a, const float& b) { return a < b; });
            int   iMinSoln    = std::distance(std::begin(values), minIt);
            float minValue    = *minIt;
            float minGradient = gradients[iMinSoln];
            Solution::Ptr minSoln = solutions[iMinSoln];

            if (iMinSoln != lastIMinSoln
                || minSoln->curIndex() != lastIndex) {
                // Add another piece to the new Solution
                factory->add(
                    kL,
                    minSoln->curSpan(),
                    minValue,
                    minGradient,
                    minSoln->curLayout());

                lastIMinSoln = iMinSoln;
                lastIndex    = minSoln->curIndex();
            }

            Vec<int> distancesToCross;
            for (int i = 0; i < n; ++i) {
                if (gradients[i] < minGradient) {
                    distancesToCross.push_back(ceil(
                        (values[i] - minValue)
                        / (minGradient - gradients[i])));
                }
            }

            Vec<int> crossovers;
            for (int d : distancesToCross) {
                if (kL + d <= kH) {
                    crossovers.push_back(kL + d);
                }
            }

            if (!crossovers.empty()) { // Proceed to crossover in [kL, kH]
                kL = *std::min_element(
                    crossovers.begin(), crossovers.end());
            } else { // Proceed to next piece
                kL = kH + 1;
                if (kL < infty) {
                    for (auto& s : solutions) {
                        s->moveToMargin(kL);
                    }
                }
                break;
            }
        }
    }

    return factory;
}

/// Return the vertical composition of a sequence of layouts.
///
/// Args:
///   layouts: a sequence of Layout objects.
/// Returns:
///   A new Layout, stacking the arguments.
Layout::Ptr getStacked(const Vec<Layout::Ptr>& layouts) {
    Vec<LayoutElement::Ptr> lElts;

    for (const auto& l : layouts) {
        for (const auto& e : l->elements) {
            lElts.push_back(e);
        }

        lElts.push_back(LayoutElement::shared(LayoutElement::Newline()));
    }

    return Layout::shared(lElts[slice(0, 2_B)]);
}

/// The layout that results from stacking several Solution::Ptrs
/// vertically.
///
/// Args:
///   solutions: a non-empty sequence of Solution::Ptr objects
/// Returns:
///   A Solution::Ptr object that lays out the solutions vertically,
///   separated by newlines, with the same left margin.
Solution::Ptr vSumSolution(Vec<Solution::Ptr> solutions) {
    assert(solutions.size() > 0);

    if (solutions.size() == 1) {
        return solutions[0];
    }

    for (auto& s : solutions) {
        s->reset();
    }

    int           margin = 0; // Margin for all components
    Solution::Ptr result = Solution::shared();
    while (true) {
        Vec<Layout::Ptr> stacked;
        for (const auto& it : solutions) {
            stacked.push_back(it->curLayout());
        }
        float curValue = std::accumulate(
            solutions.begin(),
            solutions.end(),
            0.0f,
            [margin](float sum, const Solution::Ptr& s) {
                return sum + s->curValueAt(margin);
            });

        float curGradient = std::accumulate(
            solutions.begin(),
            solutions.end(),
            0.0f,
            [](float sum, const Solution::Ptr& s) {
                return sum + s->curGradient();
            });

        auto curStacked = getStacked(stacked);

        result->add(
            margin,
            solutions.back()->curSpan(),
            curValue,
            curGradient,
            curStacked);

        // The distance to the closest next knot from the current margin.
        int  dStar      = 0;
        bool firstMatch = true;
        for (const auto& s : solutions) {
            int knot = s->nextKnot();
            if (margin < knot) {
                if (firstMatch) {
                    dStar      = knot - margin;
                    firstMatch = false;
                } else {
                    dStar = std::min(dStar, knot - margin);
                }
            }
        }

        if (isInf(dStar)) {
            break;
        }

        margin += dStar;

        for (auto& s : solutions) {
            s->moveToMargin(margin);
        }
    }

    return result;
}

/// The Solution::Ptr that results from joining two Solution::Ptrs
/// side-by-side.
///
/// Args:
///   `s1`: Solution::Ptr object
///   `s2`: Solution::Ptr object
/// Returns:
///   A new Solution::Ptr reflecting a layout in which `s2` ('s layout) is
///   placed immediately to the right of `s1`.
///
/// The resulting Solution::Ptr object maps each prospective left margin m
/// to the span, cost and layout information that would result from
/// siting Solution::Ptr `s1` at m, and then placing `s2` at margin `m +
/// sp1(m)`, where `sp1(m)` is the span of characters occupied by the
/// layout to which `s1` maps m. In general, of course, both s1 and
/// `s2`'s layouts may occupy multiple lines, in which case `s2`'s
/// layout begins at the end of the last line of `s1`'s layout---the
/// span in this case is the span of `s1`'s last line.
Solution::Ptr hPlusSolution(
    Solution::Ptr& s1,
    Solution::Ptr& s2,
    const Options& opts) {
    CHECK(s1 != nullptr);
    CHECK(s2 != nullptr);
    s1->reset();
    s2->reset();
    int s1Margin = 0;
    int s2Margin = s1->curSpan();

    s2->moveToMargin(s2Margin);

    Solution::Ptr result = Solution::shared();
    while (true) {
        // When forming the composite cost gradient and intercept, we must
        // eliminate the over-counting of the last line of the s1, which is
        // attributable to its projection beyond the margins.
        float g1        = s1->curGradient();
        float g2        = s2->curGradient();
        int   overhang0 = s2Margin - opts.leftMargin; // s2Margin =
                                                      // rightMargin + span
                                                      // of s1
        int overhang1 = s2Margin - opts.rightMargin;  // s2Margin =
                                                      // rightMargin + span
                                                      // of s1
        float gCur
            = (g1 + g2 - (overhang0 >= 0 ? opts.leftMarginCost : 0)
               - (overhang1 >= 0 ? opts.rightMarginCost : 0));

        float iCur
            = (s1->curValueAt(s1Margin) + s2->curValueAt(s2Margin)
               - opts.leftMarginCost * std::max(overhang0, 0)
               - opts.rightMarginCost * std::max(overhang1, 0));

        // The Layout computed by the following implicitly sets the margin
        // for s2 at the end of the last line printed for s1.
        result->add(
            s1Margin,
            s1->curSpan() + s2->curSpan(),
            iCur,
            gCur,
            Layout::shared(Vec<LayoutElement::Ptr>{
                LayoutElement::shared(
                    LayoutElement::LayoutPrint({s1->curLayout()})),
                LayoutElement::shared(
                    LayoutElement::LayoutPrint({s2->curLayout()}))}));

        // Move to the knot closest to the margin of the corresponding
        // component.
        int kn1 = s1->nextKnot();
        int kn2 = s2->nextKnot();

        if (isInf(kn1) && isInf(kn2)) {
            break;
        }

        // Note in the following that one of kn1 or kn2 may be infinite.
        if (kn1 - s1Margin <= kn2 - s2Margin) {
            s1->advance();
            s1Margin = kn1;
            s2Margin = s1Margin + s1->curSpan();
            // Note that s1.CurSpan() may have changed, and s2Margin may
            // decrease, so we cannot simply increment s2's index.
            s2->moveToMargin(s2Margin);
        } else {
            s2->advance();
            s2Margin = kn2;
            s1Margin = s2Margin - s1->curSpan();
        }
    }
    return result;
}


Opt<Solution::Ptr> withRestOfLine(
    Opt<Solution::Ptr> self,
    Opt<Solution::Ptr> rest,
    CR<Options>        opts) {
    /// Return a Solution::Ptr that joins the rest of the line right of
    /// this one.
    ///
    /// Args:
    ///   rest: a Solution::Ptr object representing the code laid out on
    ///   the
    ///     remainder of the line, or None, if the rest of the line is
    ///     empty.
    /// Returns:
    ///   A new Solution::Ptr object juxtaposing the layout represented by
    ///   this Solution::Ptr to the immediate right of the remainder of the
    ///   line.
    if (!rest.has_value()) {
        return self;
    } else {
        return Opt<Solution::Ptr>(
            hPlusSolution(self.value(), rest.value(), opts));
    }
}

Opt<Solution::Ptr> doOptLayout(
    BlockStore&         store,
    BlockId&            self,
    Opt<Solution::Ptr>& rest,
    CR<Options>         opts);

Opt<Solution::Ptr> optLayout(
    BlockStore&         store,
    BlockId&            self,
    Opt<Solution::Ptr>& rest,
    CR<Options>         opts) {
    /// Retrieve or compute the least-cost (optimum) layout for this block.
    /// - @arg{rest} :: text to the right of this block.
    /// - @ret{} :: Optimal layout for this block and the rest of the line.
    // Deeply-nested choice block may result in the same continuation
    // supplied repeatedly to the same block. Without memoisation, this
    // may result in an exponential blow-up in the layout algorithm.
    if (!store.at(self).layoutCache.contains(rest)) {
        store.at(self).layoutCache[rest] = doOptLayout(
            store, self, rest, opts);
    }

    return store.at(self).layoutCache[rest];
}

Opt<Solution::Ptr> doOptTextLayout(
    BlockStore&         store,
    BlockId&            self,
    Opt<Solution::Ptr>& rest,
    CR<Options>         opts) {

    Opt<Solution::Ptr> result;
    int                span = store.at(self).getText().text.len;

    Layout::Ptr layout = Layout::shared(Vec<LayoutElement::Ptr>{
        LayoutElement::shared(LayoutElement::String{
            .text = store.at(self).getText().text})});

    // The costs associated with the layout of this block may require 1, 2
    // or 3 knots, depending on how the length of the text compares with
    // the two margins (leftMargin and rightMargin) in opts. Note that we
    // assume opts.rightMargin >= opts.leftMargin >= 0, as asserted in
    // base.Options.Check().
    if (span >= opts.rightMargin) {
        Solution::Ptr temp = Solution::shared(
            Vec<int>{0},
            Vec<int>{span},
            Vec<float>{static_cast<float>(
                (span - opts.leftMargin) * opts.leftMarginCost
                + (span - opts.rightMargin) * opts.rightMargin)},
            Vec<float>{static_cast<float>(
                opts.leftMarginCost + opts.rightMarginCost)},
            Vec<Layout::Ptr>{layout});

        result = Opt<Solution::Ptr>(temp);
    } else if (span >= opts.leftMargin) {
        Solution::Ptr temp = Solution::shared(
            Vec<int>{0, opts.rightMargin - span},
            Vec<int>{span, span},
            Vec<float>{
                static_cast<float>(
                    (span - opts.leftMargin) * opts.leftMarginCost),
                static_cast<float>(
                    (opts.rightMargin - opts.leftMargin)
                    * opts.leftMarginCost)},
            Vec<float>{
                static_cast<float>(opts.leftMarginCost),
                static_cast<float>(
                    opts.leftMarginCost + opts.rightMarginCost)},
            Vec<Layout::Ptr>{layout, layout});
        result = Opt<Solution::Ptr>(temp);
    } else {
        Solution::Ptr temp = Solution::shared(
            Vec<int>{0, opts.leftMargin - span, opts.rightMargin - span},
            Vec<int>{span, span, span},
            Vec<float>{
                static_cast<float>(0),
                static_cast<float>(0),
                static_cast<float>(
                    (opts.rightMargin - opts.leftMargin)
                    * opts.leftMarginCost)},
            Vec<float>{
                static_cast<float>(0),
                static_cast<float>(opts.leftMarginCost),
                static_cast<float>(
                    opts.leftMarginCost + opts.rightMarginCost)},
            Vec<Layout::Ptr>{layout, layout, layout});
        result = Opt<Solution::Ptr>(temp);
    }

    return withRestOfLine(result, rest, opts);
}

Opt<Solution::Ptr> doOptLineLayout(
    BlockStore&         store,
    BlockId&            self,
    Opt<Solution::Ptr>& rest,
    CR<Options>         opts) {


    /// Procedure to perform optimal line layout.
    if (store.at(self).getLine().elements.size() == 0) {
        return rest;
    }

    Vec<Vec<BlockId>> elementLines;
    elementLines.push_back(Vec<BlockId>());

    for (size_t i = 0; i < store.at(self).getLine().elements.size(); ++i) {
        BlockId elt = store.at(self).getLine().elements[i];
        elementLines.back().push_back(elt);
        if (i < store.at(self).getLine().elements.size() - 1
            && store.at(elt).isBreaking) {
            elementLines.push_back(Vec<BlockId>());
        }
    }

    if (elementLines.size() > 1) {
        assert(opts.formatPolicy != nullptr);
        elementLines = opts.formatPolicy(store, elementLines);
    }

    Vec<Solution::Ptr> lineSolns;

    for (size_t i = 0; i < elementLines.size(); ++i) {
        auto&              ln       = elementLines[i];
        Opt<Solution::Ptr> lnLayout = (i == elementLines.size() - 1)
                                        ? rest
                                        : Opt<Solution::Ptr>();

        for (int idx = ln.size() - 1; idx >= 0; --idx) {
            BlockId elt = ln[idx];
            lnLayout    = optLayout(store, elt, lnLayout, opts);
        }

        if (lnLayout.has_value()) {
            lineSolns.push_back(lnLayout.value());
        }
    }

    Solution::Ptr soln = vSumSolution(lineSolns);

    return Opt<Solution::Ptr>(soln->plusConst(
        static_cast<float>(opts.linebreakCost * (lineSolns.size() - 1))));
}

Opt<Solution::Ptr> doOptChoiceLayout(
    BlockStore&         store,
    BlockId&            self,
    Opt<Solution::Ptr>& rest,
    CR<Options>         opts) {

    /// Optimum layout of this block is the piecewise minimum of its
    /// elements' layouts.
    Vec<Solution::Ptr> tmp;
    for (auto& it : store.at(self).getChoice().elements) {
        Opt<Solution::Ptr> lyt = optLayout(store, it, rest, opts);
        if (lyt.has_value()) {
            tmp.push_back(lyt.value());
        }
    }
    return minSolution(tmp);
}

Opt<Solution::Ptr> doOptStackLayout(
    BlockStore&         store,
    BlockId&            self,
    Opt<Solution::Ptr>& rest,
    CR<Options>         opts) {

    /// Optimum layout for this block arranges the elements vertically.
    if (store.at(self).getStack().elements.size() == 0) {
        return rest;
    }

    Vec<Solution::Ptr> solnCandidates;
    for (size_t idx = 0; idx < store.at(self).getStack().elements.size();
         ++idx) {
        auto& elem = store.at(self).getStack().elements.at(idx);
        if (idx < store.at(self).getStack().elements.size() - 1) {
            Opt<Solution::Ptr> it;
            auto               opt = optLayout(store, elem, it, opts);
            if (opt) {
                solnCandidates.push_back(*opt);
            }
        } else {
            auto opt = optLayout(store, elem, rest, opts);
            if (opt) {
                solnCandidates.push_back(*opt);
            }
        }
    }

    Solution::Ptr soln = vSumSolution(solnCandidates);

    // Under some odd circumstances involving comments, we may have a
    // degenerate solution. WARNING
    if (soln->layouts.size() == 0) {
        return rest;
    }

    // Add the cost of the line breaks between the elements.
    return Opt<Solution::Ptr>(soln->plusConst(static_cast<float>(
        opts.linebreakCost * store.at(self).breakMult
        * std::max(
            static_cast<int>(
                store.at(self).getStack().elements.size() - 1),
            0))));
}

Opt<Solution::Ptr> doOptWrapLayout(
    BlockStore&         store,
    BlockId&            self,
    Opt<Solution::Ptr>& rest,
    CR<Options>         opts) {
    /// Computing the optimum layout for this class of block involves
    /// finding the optimal packing of elements into lines, a problem
    /// which we address using dynamic programming.
    BlockId initTextBlock_sep = store.text(store.at(self).getWrap().sep);
    Opt<Solution::Ptr> none_Solution;
    Opt<Solution::Ptr> sepLayout = optLayout(
        store, initTextBlock_sep, none_Solution, opts);

    Opt<Solution::Ptr> prefixLayout;
    if (store.at(self).getWrap().prefix.has_value()) {
        BlockId initTextBlock_prefix = store.text(
            store.at(self).getWrap().prefix.value());

        prefixLayout = doOptLayout(
            store, initTextBlock_prefix, none_Solution, opts);
    }

    Vec<Opt<Solution::Ptr>> eltLayouts;
    for (auto& it : store.at(self).getWrap().wrapElements) {
        Opt<Solution::Ptr> tmp;
        eltLayouts.push_back(optLayout(store, it, tmp, opts));
    }

    // Entry i in the list wrapSolutions contains the optimum layout for
    // the last n - i elements of the block.
    Vec<Opt<Solution::Ptr>> wrapSolutions(
        store.at(self).size(), Opt<Solution::Ptr>());

    // Note that we compute the entries for wrapSolutions in reverse
    // order, at each iteration considering all the elements from i ... n
    // - 1 (the actual number of elements considered increases by one on
    // each iteration). This means that the complete solution, with
    // elements 0 ... n - 1 is computed last.
    for (int i = store.at(self).size() - 1; i >= 0; --i) {
        // To calculate wrapSolutions[i], consider breaking the last n - i
        // elements after element j, for j = i ... n - 1. By induction,
        // wrapSolutions contains the optimum layout of the elements after
        // the break, so the full layout is calculated by composing a line
        // with the elements before the break with the entry from
        // wrapSolutions corresponding to the elements after the break.
        // The optimum layout to be entered into wrapSolutions[i] is then
        // simply the minimum of the full layouts calculated for each j.
        Vec<Solution::Ptr> solutionsI;
        // The layout of the elements before the break is built up
        // incrementally in lineLayout.
        Opt<Solution::Ptr> lineLayout = prefixLayout.has_value()
                                          ? withRestOfLine(
                                              prefixLayout,
                                              eltLayouts[i],
                                              opts)
                                          : eltLayouts[i];

        bool breakOut     = false;
        bool lastBreaking = store
                                .at(store.at(self)
                                        .getWrap()
                                        .wrapElements[i])
                                .isBreaking;
        for (int j = i; j < store.at(self).size() - 1; ++j) {
            // Stack solutions for two lines on each other. NOTE this part
            // is different from the reference implementation, but I think
            // this is just a minor bug on the other side.
            Solution::Ptr fullSoln = vSumSolution(
                {withRestOfLine(lineLayout, sepLayout, opts).value(),
                 // Solutions for the previous lines
                 wrapSolutions[j + 1].value()});
            // We adjust the cost of the full solution by adding the cost
            // of the line break we've introduced, and a small penalty
            // (Options.cpack) to favor (ceteris paribus) layouts with
            // elements packed into earlier lines.
            solutionsI.push_back(fullSoln->plusConst(static_cast<float>(
                opts.linebreakCost * store.at(self).breakMult
                + opts.cpack * (store.at(self).size() - j))));
            // If the element at the end of the line mandates a following
            // line break, we're done.
            if (lastBreaking) {
                breakOut = true;
                break;
            }
            // Otherwise, add a separator and the next element to the line
            // layout and continue.
            Opt<Solution::Ptr> sepEltLayout = withRestOfLine(
                sepLayout, eltLayouts[j + 1], opts);

            lineLayout   = withRestOfLine(lineLayout, sepEltLayout, opts);
            lastBreaking = store
                               .at(store.at(self)
                                       .getWrap()
                                       .wrapElements[j + 1])
                               .isBreaking;
        }

        if (!breakOut) {
            Opt<Solution::Ptr> line = withRestOfLine(
                lineLayout, rest, opts);
            solutionsI.push_back(line.value());
        }

        wrapSolutions[i] = minSolution(solutionsI);
    }
    // Once wrapSolutions is complete, the optimum layout for the entire
    // block is the optimum layout for the last n - 0 elements.
    return wrapSolutions[0];
}

Opt<Solution::Ptr> doOptVerbLayout(
    BlockStore&         store,
    BlockId&            self,
    Opt<Solution::Ptr>& rest,
    CR<Options>         opts) {
    // The solution for this block is essentially that of a TextBlock(''),
    // with an abberant layout calculated as follows.
    Vec<LayoutElement::Ptr> lElts;

    for (size_t i = 0; i < store.at(self).getVerb().textLines.size();
         ++i) {
        const auto& ln = store.at(self).getVerb().textLines[i];
        if (i < 0 || store.at(self).getVerb().firstNl) {
            lElts.push_back(LayoutElement::newline());
        }

        lElts.push_back(LayoutElement::string({ln}));
    }

    Layout::Ptr   layout = Layout::shared(lElts);
    int           span   = 0;
    Solution::Ptr sf;
    if (0 < opts.leftMargin) { // Prevent incoherent solutions
        sf->add(0, span, 0, 0, layout);
    }
    // opts.rightMargin == 0 is absurd
    sf->add(opts.leftMargin - span, span, 0, opts.leftMarginCost, layout);
    sf->add(
        opts.rightMargin - span,
        span,
        (opts.rightMargin - opts.leftMargin) * opts.leftMarginCost,
        opts.leftMarginCost + opts.rightMarginCost,
        layout);

    return Opt<Solution::Ptr>(sf);
}


Opt<Solution::Ptr> doOptLayout(
    BlockStore&         store,
    BlockId&            self,
    Opt<Solution::Ptr>& rest,
    CR<Options>         opts) {
    switch (store.at(self).getKind()) {
        case Block::Kind::Empty: return std::nullopt;
        case Block::Kind::Verb:
            return doOptVerbLayout(store, self, rest, opts);
        case Block::Kind::Wrap:
            return doOptWrapLayout(store, self, rest, opts);
        case Block::Kind::Line:
            return doOptLineLayout(store, self, rest, opts);
        case Block::Kind::Text:
            return doOptTextLayout(store, self, rest, opts);
        case Block::Kind::Stack:
            return doOptStackLayout(store, self, rest, opts);
        case Block::Kind::Choice:
            return doOptChoiceLayout(store, self, rest, opts);
    }
}

generator<Event> layout::formatEvents(
    BlockStore&        store,
    Layout::Ptr const& lyt) {
    /// Generate formatting events for the given layout. The events are
    /// backend-agnostic and can be interpreted further by the user
    /// depending on their needs.
    OutConsole                  buf;
    Vec<Pair<Layout::Ptr, int>> stack;
    stack.push_back({lyt, 0});

    auto top  = [&]() -> Pair<Layout::Ptr, int>& { return stack.back(); };
    using lek = LayoutElement::Kind;

    buf.addMargin(buf.hPos);
    while (!stack.empty()) {
        while (top().second < top().first->elements.size()) {
            const auto& elem = top().first->elements[top().second];
            top().second++;
            buf.hPos = std::max(buf.hPos, buf.margin());
            switch (elem->getKind()) {
                case lek::String: {
                    for (const auto& item : elem->getString().text.strs) {
                        if (item.id == LytSpacesId) {
                            if (item.len != 0) {
                                co_yield Event(Event::Spaces{item.len});
                            }
                            buf.hPos += item.len;
                        } else if (!item.id.isNil()) {
                            co_yield Event(Event::Text{item});
                            buf.hPos += item.len;
                        }
                    }
                    break;
                }

                case lek::Newline:
                case lek::NewlineSpace: {
                    co_yield Event(Event::Newline{});

                    buf.hPos = 0;
                    int mar  = buf.margin();
                    if (mar != 0) {
                        co_yield Event(Event::Spaces{mar});
                        buf.hPos += mar;
                    }

                    if (elem->getKind() == lek::NewlineSpace
                        && elem->getNewlineSpace().spaceNum != 0) {
                        co_yield Event(Event::Spaces{
                            elem->getNewlineSpace().spaceNum});
                        buf.hPos += elem->getNewlineSpace().spaceNum;
                    }
                    break;
                }

                case lek::LayoutPrint: {
                    stack.push_back({elem->getLayoutPrint().layout, 0});
                    buf.addMargin(buf.hPos);
                    break;
                }
            }
        }
        stack.pop_back();
        buf.popMargin();
    }
}

int Block::size() const {
    return std::visit(
        overloaded{
            [](CR<Wrap> w) { return w.wrapElements.size(); },
            [](CR<Stack> s) { return s.elements.size(); },
            [](CR<Choice> s) { return s.elements.size(); },
            [](CR<Line> s) { return s.elements.size(); },
            [](const auto&) { return 0; },
        },
        data);
}

void Block::add(CR<BlockId> other) {
    return std::visit(
        overloaded{
            [&](Line& w) { w.elements.push_back(other); },
            [&](Stack& w) { w.elements.push_back(other); },
            [&](Choice& w) { w.elements.push_back(other); },
            [&](Wrap& w) { w.wrapElements.push_back(other); },
            [&](const auto&) { CHECK(false) << ("TODO ERRMSG"); },
        },
        data);
}

void Block::add(CVec<BlockId> others) {
    return std::visit(
        overloaded{
            [&](Line& w) { w.elements.append(others); },
            [&](Stack& w) { w.elements.append(others); },
            [&](Choice& w) { w.elements.append(others); },
            [&](Wrap& w) { w.wrapElements.append(others); },
            [&](const auto&) { CHECK(false) << ("TODO ERRMSG"); },
        },
        data);
}

BlockId BlockStore::text(CR<LytStrSpan> t) {
    return store.add(Block(Block::Text{.text = t}));
}

BlockId BlockStore::line(CR<Vec<BlockId>> l) {
    return store.add(Block(Block::Line{.elements = l}));
}

BlockId BlockStore::stack(CR<Vec<BlockId>> l) {
    return store.add(Block(Block::Stack{.elements = l}));
}

BlockId BlockStore::spatial(bool isVertical, CR<Vec<BlockId>> l) {
    if (isVertical) {
        return stack(l);
    } else {
        return line(l);
    }
}

BlockId BlockStore::join(
    CVec<BlockId> items,
    CR<BlockId>   join,
    bool          isLine,
    bool          isTrailing) {
    BlockId res = spatial(!isLine);
    for (int i = 0; i < items.size(); ++i) {
        if (i < items.high() || isTrailing) {
            add_at(res, line({items.at(i), join}));
        } else {
            add_at(res, items.at(i));
        }
    }
    return res;
}

BlockId BlockStore::choice(CR<Vec<BlockId>> l) {
    return store.add(Block(Block::Choice{.elements = l}));
}

BlockId BlockStore::space(int count) {
    return store.add(
        Block(Block::Text{.text = LytStr(LytSpacesId, count)}));
}

BlockId BlockStore::wrap(
    CR<Vec<BlockId>> elems,
    LytStr           sep,
    int              breakMult) {
    auto res = store.add(Block(Block::Wrap{
        .wrapElements = elems,
        .sep          = sep,
    }));

    at(res).isBreaking = false;
    at(res).breakMult  = breakMult;
    return res;
}

BlockId BlockStore::indent(int indent, CR<BlockId> block, int breakMult) {
    if (indent == 0) {
        return block;
    } else {
        return line({text(LytStr(LytSpacesId, indent)), block});
    }
}

BlockId BlockStore::vertical(
    const Vec<BlockId>& blocks,
    const BlockId&      sep) {
    BlockId result = stack({});

    for (size_t idx = 0; idx < blocks.size(); ++idx) {
        const auto& item = blocks[idx];
        if (idx < blocks.size() - 1) {
            add_at(result, line({item, sep}));
        } else {
            add_at(result, item);
        }
    }

    return result;
}

BlockId BlockStore::horizontal(
    const Vec<BlockId>& blocks,
    const BlockId&      sep) {
    BlockId result = line({});

    for (size_t idx = 0; idx < blocks.size(); ++idx) {
        const auto& item = blocks[idx];
        if (idx > 0) {
            add_at(result, sep);
        }
        add_at(result, item);
    }

    return result;
}

Vec<Layout::Ptr> BlockStore::toLayouts(BlockId id, const Options& opts) {
    Opt<Solution::Ptr> rest;
    auto               sln = doOptLayout(*this, id, rest, opts);
    return sln.value()->layouts;
}

std::string SimpleStringStore::toTreeRepr(BlockId id, bool doRecurse) {
    std::stringstream               os;
    UnorderedSet<BlockId>           visited;
    Func<void(const BlockId&, int)> aux;

    aux = [&](const BlockId& blId, int level) -> void {
        std::string pref2 = repeat(" ", level * 2 + 2);
        os << fmt_str(pref2) << "ID:" << fmt_str(blId) << " ";
        if (id.isNil()) {
            os << "<nil>";
            return;
        } else if (visited.contains(blId)) {
            os << "<visited> " << fmt_str(blId);
            return;
        } else {
            visited.incl(blId);
        }

        std::string  name;
        Block const& bl = store->at(blId);
        switch (bl.getKind()) {
            case Block::Kind::Line: name = "Ln"; break;
            case Block::Kind::Choice: name = "Ch"; break;
            case Block::Kind::Text: name = "Tx"; break;
            case Block::Kind::Wrap: name = "Wr"; break;
            case Block::Kind::Stack: name = "St"; break;
            case Block::Kind::Verb: name = "Ve"; break;
            case Block::Kind::Empty: name = "Em"; break;
        }

        os << right_aligned(name + " ", level * 2) << "brk: {"
           << fmt_str(bl.isBreaking) << "} "
           << "mul: {" << fmt_str(bl.breakMult) << "}";

        switch (bl.getKind()) {
            case Block::Kind::Line: {
                os << (doRecurse ? "\n" : "");
                for (const auto& elem : bl.getLine().elements) {
                    if (doRecurse) {
                        aux(elem, level + 1);
                    } else {
                        os << " " << fmt_str(elem);
                    }
                }
                break;
            }
            case Block::Kind::Choice: {
                os << (doRecurse ? "\n" : "");
                for (const auto& elem : bl.getChoice().elements) {
                    if (doRecurse) {
                        aux(elem, level + 1);
                    } else {
                        os << " " << fmt_str(elem);
                    }
                }
                break;
            }
            case Block::Kind::Stack: {
                os << (doRecurse ? "\n" : "");
                for (const auto& elem : bl.getStack().elements) {
                    if (doRecurse) {
                        aux(elem, level + 1);
                    } else {
                        os << " " << fmt_str(elem);
                    }
                }
                break;
            }
            case Block::Kind::Wrap: {
                os << (doRecurse ? "\n" : "");
                for (const auto& elem : bl.getWrap().wrapElements) {
                    if (doRecurse) {
                        aux(elem, level + 1);
                    } else {
                        os << " " << fmt_str(elem);
                    }
                }
                break;
            }
            case Block::Kind::Text: {
                std::string text;
                for (auto const& it : bl.getText().text.strs) {
                    text += str(it);
                }
                os << text;
                break;
            }

            case Block::Kind::Empty: {
                os << "<empty>";
                break;
            }

            case Block::Kind::Verb: {
                os << "\n";
                for (const auto& line : bl.getVerb().textLines) {
                    os << pref2
                       << repeat("  ", std::clamp(level - 1, 0, INT_MAX))
                       << "  〚" << fmt_str(line) << "〛\n";
                }
                break;
            }
        }
    };

    aux(id, 0);
    return os.str();
}

Vec<Vec<BlockId>> Options::defaultFormatPolicy(
    BlockStore&              store,
    const Vec<Vec<BlockId>>& blc) {
    Vec<Vec<BlockId>> result;

    auto strippedLine = [&](const Vec<BlockId>& line) -> BlockId {
        return store.line(line);
    };

    result.push_back({blc[0]});
    if (blc.size() > 1) {
        Vec<BlockId> mapped;
        for (const auto& line : blc[slice(1, 1_B)]) {
            mapped.push_back(strippedLine(line));
        }

        BlockId ind = store.indent(2 * 2, store.stack(mapped));

        result.push_back({ind});
    }

    return result;
}

LytStr SimpleStringStore::str(const std::string& str) {
    LytStr result(strings.size(), str.length());
    strings.push_back(str);
    return result;
}

Str SimpleStringStore::str(const LytStr& str) const {
    if (str.isSpaces()) {
        return Str(" ").repeated(str.len);
    } else {
        return strings[str.toIndex()];
    };
}

Str SimpleStringStore::toString(const BlockId& blc, const Options& opts) {
    Layout::Ptr lyt = store->toLayout(blc, opts);
    Str         result;
    for (const auto& event : formatEvents(*store, lyt)) {
        switch (event.getKind()) {
            case Event::Kind::Newline: {
                result += "\n";
                break;
            }

            case Event::Kind::Spaces: {
                result += Str(event.getSpaces().spaces, ' ');
                break;
            }

            case Event::Kind::Text: {
                result += str(event.getText().str);
                break;
            }
        }
    }

    Vec<Str> fin;
    for (const auto& line : result.split("\n")) {
        fin.push_back(strip(line, CharSet{}, CharSet{' '}));
    }

    return join("\n", fin);
}
