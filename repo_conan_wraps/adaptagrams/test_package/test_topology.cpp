#include <iostream>

#include <libtopology/cola_topology_addon.h>

int main() {
    topology::ColaTopologyAddon addon;

    if (!addon.topologyNodes.empty() || !addon.topologyRoutes.empty()) {
        std::cerr << "A default topology addon should be empty\n";
        return 1;
    }

    return 0;
}
