#include "test_mind_map.hpp"

#include <libcola/cola.h>
#include <libcola/output_svg.h>
#include <QRect>
#include <hstd/stdlib/Ranges.hpp>

struct GraphConstraint {
    struct Align {
        struct Spec {
            int         node;
            Opt<double> fixPos = std::nullopt;
            double      offset = 0.0;
        };

        Vec<Spec> nodes;
        vpsc::Dim dimension;
        DESC_FIELDS(Align, (nodes, dimension));

        SPtr<cola::CompoundConstraint> toCola() const {
            auto result = std::make_shared<cola::AlignmentConstraint>(
                dimension);

            for (auto const& spec : nodes) {
                result->addShape(spec.node, spec.offset);
                if (spec.fixPos) { result->fixPos(*spec.fixPos); }
            }

            return result;
        }
    };

    SPtr<cola::CompoundConstraint> toCola() const {
        return std::visit(
            [](auto const& spec) { return spec.toCola(); }, data);
    }

    SUB_VARIANTS(Kind, Data, data, getKind, Align);
    Data data;

    GraphConstraint(CR<Data> data) : data(data) {};
};

struct GraphLayoutIR {
    Vec<QRect>           rectangles;
    Vec<Pair<int, int>>  edges;
    Vec<GraphConstraint> constraints;
    double               width  = 100;
    double               height = 100;

    void validate() {
        for (auto const& e : enumerator(edges)) {
            for (auto const& it :
                 Vec<int>{e.value().first, e.value().second}) {
                Q_ASSERT_X(
                    it < rectangles.size(),
                    "validate",
                    fmt("Edge {} point is out of range for rectangles: "
                        "[{}] out of {} rects",
                        e.index(),
                        it,
                        rectangles.size()));
            }
        }
    }

    struct Result {
        Vec<QRect>     fixed;
        Vec<QPolygonF> lines;
    };

    /// Intermediate layout representation storage
    struct ColaResult {
        Vec<vpsc::Rectangle>          baseRectangles;
        Vec<vpsc::Rectangle*>         rectPointers;
        Vec<Pair<unsigned, unsigned>> edges;

        Result convert() {
            Result res;

            res.fixed = baseRectangles
                      | rv::transform([](CR<vpsc::Rectangle> r) {
                            return QRect(
                                r.getMinX(),               // top left x
                                r.getMaxY(),               // top left y
                                r.getMaxX() - r.getMinX(), // width
                                r.getMaxY() - r.getMinY()  // height
                            );
                        })
                      | rs::to<Vec>();

            return res;
        }

        void writeSvg(CR<Str> path) {
            OutputFile output(rectPointers, edges, nullptr, path);
            output.rects = true;
            output.generate();
        }
    };

    ColaResult doColaLayout() {
        validate();
        ColaResult                ir;
        cola::CompoundConstraints ccs;

        auto constraints = this->constraints
                         | rv::transform([](CR<GraphConstraint> c) {
                               return c.toCola();
                           })
                         | rs::to<Vec>();

        for (auto const& c : constraints) { ccs.push_back(c.get()); }

        ir.baseRectangles.reserve(rectangles.size());
        for (auto const& r : rectangles) {
            ir.baseRectangles.push_back(
                vpsc::Rectangle(r.left(), r.right(), r.top(), r.bottom()));
        }

        ir.rectPointers = ir.baseRectangles
                        | rv::transform([](auto& r) { return &r; })
                        | rs::to<Vec>();

        ir.edges = edges
                 | rv::transform(
                       [](auto const& i) -> Pair<unsigned, unsigned> {
                           return std::make_pair<unsigned>(
                               i.first, i.second);
                       })
                 | rs::to<Vec>();

        cola::ConstrainedFDLayout alg2(
            ir.rectPointers, ir.edges, width / 2);

        alg2.setConstraints(ccs);
        alg2.run();

        return ir;
    }
};

void TestMindMap::testLibcolaApi1() {
    std::vector<std::pair<unsigned, unsigned>> edges{
        {0, 1},
        {1, 2},
        {2, 3},
    };

    double                        width  = 100;
    double                        height = 100;
    std::vector<vpsc::Rectangle*> rectangles;

    for (unsigned i = 0; i < edges.size() + 1; i++) {
        double x = i * 10;
        double y = i * 10;
        rectangles.push_back(new vpsc::Rectangle(x, x + 5, y, y + 5));
    }

    cola::CompoundConstraints ccs;

    cola::AlignmentConstraint align_on_x{vpsc::XDIM};
    ccs.push_back(&align_on_x);
    align_on_x.addShape(0, 0);
    align_on_x.addShape(1, 0);

    cola::AlignmentConstraint align_on_y{vpsc::YDIM};
    ccs.push_back(&align_on_y);
    align_on_y.addShape(1, 0);
    align_on_y.addShape(3, 0);

    cola::ConstrainedFDLayout alg2(rectangles, edges, width / 2);
    alg2.setConstraints(ccs);
    alg2.run();

    OutputFile output(
        rectangles, edges, nullptr, "/tmp/testLibcolaApi1.svg");
    output.rects = true;
    output.generate();

    for (auto r : rectangles) { delete r; }
}

void TestMindMap::testLibcolaIr1() {
    GraphLayoutIR ir;
    ir.edges.push_back({0, 1});
    ir.edges.push_back({1, 2});
    ir.edges.push_back({2, 3});

    ir.rectangles.push_back(QRect(0, 0, 5, 5));
    ir.rectangles.push_back(QRect(5, 5, 5, 5));
    ir.rectangles.push_back(QRect(10, 10, 5, 5));
    ir.rectangles.push_back(QRect(15, 15, 5, 5));

    using C = GraphConstraint;

    ir.constraints.push_back(C{C::Align{
        .nodes = {C::Align::Spec{.node = 0}, C::Align::Spec{.node = 1}},
        .dimension = vpsc::XDIM,
    }});

    ir.constraints.push_back(C{C::Align{
        .nodes = {C::Align::Spec{.node = 1}, C::Align::Spec{.node = 3}},
        .dimension = vpsc::YDIM,
    }});

    auto lyt = ir.doColaLayout();
    lyt.writeSvg("/tmp/testLibcolaIr1.svg");
    lyt.convert();
}
