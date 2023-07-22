#include <parse/OrgTypes.hpp>

#include <lexbase/Node.cpp>

template class NodeGroup<OrgNodeKind, OrgTokenKind>;

using org = OrgNodeKind;

const OrgSet OrgAttachableCommands{
    org::CommandCaption,
};


const OrgSet OrgTrailableCommands{
    org::SrcCode,
    org::QuoteBlock,
};
