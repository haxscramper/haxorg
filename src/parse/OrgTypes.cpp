import org.parse.OrgTypes;

#include <lexbase/Node.cpp>

template class NodeGroup<OrgNodeKind, OrgTokenKind, OrgFill>;

using org = OrgNodeKind;

const OrgSet OrgAttachableCommands{
    org::CommandCaption,
};


const OrgSet OrgTrailableCommands{
    org::SrcCode,
    org::QuoteBlock,
};
