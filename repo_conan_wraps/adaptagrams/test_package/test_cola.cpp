#include <cmath>
#include <iostream>
#include <vector>

#include <libcola/cola.h>
#include <libcola/output_svg.h>
#include <libvpsc/rectangle.h>

#ifdef HAVE_CAIROMM
#    error "This package is expected to be built without Cairomm"
#endif

int main() {
    vpsc::Rectangle first(0.0, 10.0, 0.0, 10.0);
    vpsc::Rectangle second(30.0, 40.0, 20.0, 30.0);

    std::vector<vpsc::Rectangle*> rectangles{&first, &second};
    std::vector<cola::Edge>       edges{cola::Edge(0, 1)};

    {
        cola::ConstrainedFDLayout layout(rectangles, edges, 50.0);
        layout.setAvoidNodeOverlaps(true);
        layout.run();
    }

    for (const auto* rectangle : rectangles) {
        if (!std::isfinite(rectangle->getCentreX())
            || !std::isfinite(rectangle->getCentreY())) {
            std::cerr << "Cola produced non-finite coordinates\n";
            return 1;
        }
    }

    const double dx       = first.getCentreX() - second.getCentreX();
    const double dy       = first.getCentreY() - second.getCentreY();
    const double distance = std::sqrt(dx * dx + dy * dy);

    if (!(distance > 0.0)) {
        std::cerr << "Cola produced coincident node centres\n";
        return 1;
    }

    return 0;
}
