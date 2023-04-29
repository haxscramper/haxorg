#include "textlayouter.hpp"
#include <hstd/stdlib/Ranges.hpp>

using namespace layout;


int Solution::nextKnot() {
    if (index + 1 >= knots.size()) {
        return std::numeric_limits<int>::max();
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
        while (nextKnot() <= margin
               && nextKnot() != std::numeric_limits<int>::max()) {
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

const auto infty = 1024 * 1024 * 1024;

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
        s.reset();
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

    return Layout::shared(lElts);
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
        s.reset();
    }

    int           margin = 0; // Margin for all components
    Solution::Ptr result;
    while (true) {
        Vec<Layout::Ptr> stacked;
        for (const auto& it : solutions) {
            stacked.push_back(it->curLayout());
        }
        result->add(
            margin,
            solutions.back()->curSpan(),
            std::accumulate(
                solutions.begin(),
                solutions.end(),
                0.0f,
                [margin](float sum, const Solution::Ptr& s) {
                    return sum + s->curValueAt(margin);
                }),
            std::accumulate(
                solutions.begin(),
                solutions.end(),
                0.0f,
                [](float sum, const Solution::Ptr& s) {
                    return sum + s->curGradient();
                }),
            getStacked(stacked));

        // The distance to the closest next knot from the current margin.
        int dStar = std::numeric_limits<int>::max();
        for (const auto& s : solutions) {
            if (s->nextKnot() > margin) {
                dStar = std::min(dStar, s->nextKnot() - margin);
            }
        }

        if (dStar == std::numeric_limits<int>::max()) {
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
    s1.reset();
    s2.reset();
    int s1Margin = 0;
    int s2Margin = s1->curSpan();

    s2->moveToMargin(s2Margin);

    Solution::Ptr result;
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

        if (kn1 == std::numeric_limits<int>::max()
            && kn2 == std::numeric_limits<int>::max()) {
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
    if (self->layoutCache.contains(rest)) {
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
