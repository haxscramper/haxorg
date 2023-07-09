#include <parse/OrgTypes.hpp>

#include <lexbase/Node.cpp>

template class NodeGroup<OrgNodeKind, OrgTokenKind>;

using org = OrgNodeKind;
using osk = OrgSemKind;

const OrgSet OrgAttachableCommands{
    org::CommandCaption,
};

const SemSet SemAttachableCommands{
    osk::Caption,
};

const OrgSet OrgTrailableCommands{
    org::SrcCode,
    org::QuoteBlock,
};

const SemSet SemTrailableCommands{
    osk::Code,
    osk::Quote,
};
