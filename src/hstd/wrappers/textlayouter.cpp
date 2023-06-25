#include "textlayouter.hpp"
#include <hstd/stdlib/Ranges.hpp>
#include <hstd/system/generator.hpp>
#include <hstd/stdlib/charsets.hpp>
#include <hstd/stdlib/strutils.hpp>

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
             + to_string(gradient) + ")")
                .toStdString());
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
    Q_CHECK_PTR(s1);
    Q_CHECK_PTR(s2);
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
    Block::Ptr&         self,
    Opt<Solution::Ptr>& rest,
    CR<Options>         opts);

Opt<Solution::Ptr> optLayout(
    Block::Ptr&         self,
    Opt<Solution::Ptr>& rest,
    CR<Options>         opts) {
    /// Retrieve or compute the least-cost (optimum) layout for this block.
    /// - @arg{rest} :: text to the right of this block.
    /// - @ret{} :: Optimal layout for this block and the rest of the line.
    // Deeply-nested choice block may result in the same continuation
    // supplied repeatedly to the same block. Without memoisation, this
    // may result in an exponential blow-up in the layout algorithm.
    if (!self->layoutCache.contains(rest)) {
        self->layoutCache[rest] = doOptLayout(self, rest, opts);
    }

    return self->layoutCache[rest];
}

Opt<Solution::Ptr> doOptTextLayout(
    Block::Ptr&         self,
    Opt<Solution::Ptr>& rest,
    CR<Options>         opts) {

    Opt<Solution::Ptr> result;
    int                span = self->getText().text.len;

    Layout::Ptr layout = Layout::shared(
        Vec<LayoutElement::Ptr>{LayoutElement::shared(
            LayoutElement::String{.text = self->getText().text})});

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
    Block::Ptr&         self,
    Opt<Solution::Ptr>& rest,
    CR<Options>         opts) {
    Q_CHECK_PTR(self);

    Block::Line& line = self->getLine();
    /// Procedure to perform optimal line layout.
    if (line.elements.size() == 0) {
        return rest;
    }

    Vec<Vec<Block::Ptr>> elementLines;
    elementLines.push_back(Vec<Block::Ptr>());

    for (size_t i = 0; i < line.elements.size(); ++i) {
        Block::Ptr elt = line.elements[i];
        Q_CHECK_PTR(elt);
        elementLines.back().push_back(elt);
        if (i < line.elements.size() - 1 && elt->isBreaking) {
            elementLines.push_back(Vec<Block::Ptr>());
        }
    }

    if (elementLines.size() > 1) {
        assert(opts.formatPolicy != nullptr);
        elementLines = opts.formatPolicy(elementLines);
    }

    Vec<Solution::Ptr> lineSolns;

    for (size_t i = 0; i < elementLines.size(); ++i) {
        auto&              ln       = elementLines[i];
        Opt<Solution::Ptr> lnLayout = (i == elementLines.size() - 1)
                                        ? rest
                                        : Opt<Solution::Ptr>();

        for (int idx = ln.size() - 1; idx >= 0; --idx) {
            Block::Ptr elt = ln[idx];
            lnLayout       = optLayout(elt, lnLayout, opts);
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
    Block::Ptr&         self,
    Opt<Solution::Ptr>& rest,
    CR<Options>         opts) {
    Block::Choice& choice = self->getChoice();
    /// Optimum layout of this block is the piecewise minimum of its
    /// elements' layouts.
    Vec<Solution::Ptr> tmp;
    for (auto& it : choice.elements) {
        Opt<Solution::Ptr> lyt = optLayout(it, rest, opts);
        if (lyt.has_value()) {
            tmp.push_back(lyt.value());
        }
    }
    return minSolution(tmp);
}

Opt<Solution::Ptr> doOptStackLayout(
    Block::Ptr&         self,
    Opt<Solution::Ptr>& rest,
    CR<Options>         opts) {
    Block::Stack& stack = self->getStack();
    /// Optimum layout for this block arranges the elements vertically.
    if (stack.elements.size() == 0) {
        return rest;
    }

    Vec<Solution::Ptr> solnCandidates;
    for (size_t idx = 0; idx < stack.elements.size(); ++idx) {
        auto& elem = stack.elements.at(idx);
        if (idx < stack.elements.size() - 1) {
            Opt<Solution::Ptr> it;
            auto               opt = optLayout(elem, it, opts);
            if (opt) {
                solnCandidates.push_back(*opt);
            }
        } else {
            auto opt = optLayout(elem, rest, opts);
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
        opts.linebreakCost * self->breakMult
        * std::max(static_cast<int>(stack.elements.size() - 1), 0))));
}

Opt<Solution::Ptr> doOptWrapLayout(
    Block::Ptr&         self,
    Opt<Solution::Ptr>& rest,
    CR<Options>         opts) {
    /// Computing the optimum layout for this class of block involves
    /// finding the optimal packing of elements into lines, a problem
    /// which we address using dynamic programming.
    Block::Wrap&       wrap              = self->getWrap();
    Block::Ptr         initTextBlock_sep = Block::text(wrap.sep);
    Opt<Solution::Ptr> none_Solution;
    Opt<Solution::Ptr> sepLayout = optLayout(
        initTextBlock_sep, none_Solution, opts);

    Opt<Solution::Ptr> prefixLayout;
    if (wrap.prefix.has_value()) {
        Block::Ptr initTextBlock_prefix = Block::text(wrap.prefix.value());

        prefixLayout = doOptLayout(
            initTextBlock_prefix, none_Solution, opts);
    }

    Vec<Opt<Solution::Ptr>> eltLayouts;
    for (auto& it : wrap.wrapElements) {
        Opt<Solution::Ptr> tmp;
        eltLayouts.push_back(optLayout(it, tmp, opts));
    }

    // Entry i in the list wrapSolutions contains the optimum layout for
    // the last n - i elements of the block.
    Vec<Opt<Solution::Ptr>> wrapSolutions(
        self->size(), Opt<Solution::Ptr>());

    // Note that we compute the entries for wrapSolutions in reverse
    // order, at each iteration considering all the elements from i ... n
    // - 1 (the actual number of elements considered increases by one on
    // each iteration). This means that the complete solution, with
    // elements 0 ... n - 1 is computed last.
    for (int i = self->size() - 1; i >= 0; --i) {
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
        bool lastBreaking = wrap.wrapElements[i]->isBreaking;
        for (int j = i; j < self->size() - 1; ++j) {
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
                opts.linebreakCost * self->breakMult
                + opts.cpack * (self->size() - j))));
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
            lastBreaking = wrap.wrapElements[j + 1]->isBreaking;
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
    Block::Ptr&         self,
    Opt<Solution::Ptr>& rest,
    CR<Options>         opts) {
    // The solution for this block is essentially that of a TextBlock(''),
    // with an abberant layout calculated as follows.
    Vec<LayoutElement::Ptr> lElts;
    Block::Verb&            verb = self->getVerb();

    for (size_t i = 0; i < verb.textLines.size(); ++i) {
        const auto& ln = verb.textLines[i];
        if (i < 0 || verb.firstNl) {
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
    Block::Ptr&         self,
    Opt<Solution::Ptr>& rest,
    CR<Options>         opts) {
    switch (self->getKind()) {
        case Block::Kind::Empty: return std::nullopt;
        case Block::Kind::Verb: return doOptVerbLayout(self, rest, opts);
        case Block::Kind::Wrap: return doOptWrapLayout(self, rest, opts);
        case Block::Kind::Line: return doOptLineLayout(self, rest, opts);
        case Block::Kind::Text: return doOptTextLayout(self, rest, opts);
        case Block::Kind::Stack: return doOptStackLayout(self, rest, opts);
        case Block::Kind::Choice:
            return doOptChoiceLayout(self, rest, opts);
    }
}

generator<Event> layout::formatEvents(Layout::Ptr const& lyt) {
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

void Block::add(CR<Ptr> other) {
    Q_CHECK_PTR(other);
    return std::visit(
        overloaded{
            [&](Line& w) { w.elements.push_back(other); },
            [&](Stack& w) { w.elements.push_back(other); },
            [&](Choice& w) { w.elements.push_back(other); },
            [&](Wrap& w) { w.wrapElements.push_back(other); },
            [&](const auto&) { qFatal("TODO ERRMSG"); },
        },
        data);
}

void Block::add(CVec<Ptr> others) {
    for (auto const& p : others) {
        Q_CHECK_PTR(p);
    }

    return std::visit(
        overloaded{
            [&](Line& w) { w.elements.append(others); },
            [&](Stack& w) { w.elements.append(others); },
            [&](Choice& w) { w.elements.append(others); },
            [&](Wrap& w) { w.wrapElements.append(others); },
            [&](const auto&) { qFatal("TODO ERRMSG"); },
        },
        data);
}

Block::Ptr Block::text(CR<LytStrSpan> t) {
    return Block::shared(Text{.text = t});
}

Block::Ptr Block::line(CR<Vec<Ptr>> l) {
    return Block::shared(Line{.elements = l});
}

Block::Ptr Block::stack(CR<Vec<Ptr>> l) {
    return Block::shared(Stack{.elements = l});
}

Block::Ptr Block::choice(CR<Vec<Ptr>> l) {
    return Block::shared(Choice{.elements = l});
}

Block::Ptr Block::space(int count) {
    return Block::shared(Text{.text = LytStr(LytSpacesId, count)});
}

Block::Ptr Block::wrap(CR<Vec<Ptr>> elems, LytStr sep, int breakMult) {

    auto res = Block::shared(Wrap{
        .wrapElements = elems,
        .sep          = sep,
    });

    res->isBreaking = false;
    res->breakMult  = breakMult;
    return res;
}

Block::Ptr Block::indent(int indent, CR<Ptr> block, int breakMult) {
    if (indent == 0) {
        return block;
    } else {
        return line({text(LytStr(LytSpacesId, indent)), block});
    }
}

Block::Ptr Block::vertical(const Vec<Ptr>& blocks, const Ptr& sep) {
    Block::Ptr result = stack({});

    for (size_t idx = 0; idx < blocks.size(); ++idx) {
        const auto& item = blocks[idx];
        if (idx < blocks.size() - 1) {
            result->add(line({item, sep}));
        } else {
            result->add(item);
        }
    }

    return result;
}

Block::Ptr Block::horizontal(const Vec<Ptr>& blocks, const Ptr& sep) {
    Block::Ptr result = line({});

    for (size_t idx = 0; idx < blocks.size(); ++idx) {
        const auto& item = blocks[idx];
        if (idx > 0) {
            result->add(sep);
        }
        result->add(item);
    }

    return result;
}

Vec<Layout::Ptr> Block::toLayouts(const Options& opts) {
    Opt<Solution::Ptr> rest;
    Block::Ptr         this_ptr = shared_from_this();
    auto               sln      = doOptLayout(this_ptr, rest, opts);
    return sln.value()->layouts;
}

Vec<Vec<Block::Ptr>> Options::defaultFormatPolicy(
    const Vec<Vec<Block::Ptr>>& blc) {
    Vec<Vec<Block::Ptr>> result;

    auto strippedLine = [](const Vec<Block::Ptr>& line) -> Block::Ptr {
        return Block::line(line);
    };

    result.push_back({blc[0]});
    if (blc.size() > 1) {
        Vec<Block::Ptr> mapped;
        for (const auto& line : blc[slice(1, 1_B)]) {
            mapped.push_back(strippedLine(line));
        }

        Block::Ptr ind = Block::indent(2 * 2, Block::stack(mapped));

        result.push_back({ind});
    }

    return result;
}

LytStr SimpleStringStore::str(const QString& str) {
    LytStr result(strings.size(), str.length());
    strings.push_back(str);
    return result;
}

QString SimpleStringStore::str(const LytStr& str) {
    if (str.isSpaces()) {
        return QString(" ").repeated(str.len);
    } else {
        return strings[str.toIndex()];
    };
}

QString SimpleStringStore::toString(Block::Ptr& blc, const Options& opts) {
    Layout::Ptr lyt = blc->toLayout(opts);
    QString     result;
    for (const auto& event : formatEvents(lyt)) {
        switch (event.getKind()) {
            case Event::Kind::Newline: {
                result += "\n";
                break;
            }

            case Event::Kind::Spaces: {
                result += std::string(event.getSpaces().spaces, ' ');
                break;
            }

            case Event::Kind::Text: {
                result += str(event.getText().str);
                break;
            }
        }
    }

    Vec<QString> fin;
    for (const auto& line : result.split("\n")) {
        fin.push_back(strip(line, CharSet{}, CharSet{QChar(' ')}));
    }

    return join("\n", fin);
}
