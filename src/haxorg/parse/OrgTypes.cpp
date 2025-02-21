#include <haxorg/parse/OrgTypes.hpp>

#include <haxorg/lexbase/Node.cpp>

namespace org::parse {
template class NodeGroup<OrgNodeKind, OrgTokenKind, OrgFill, OrgNodeMono>;
}
