#include <parse/OrgTypes.hpp>

#include <lexbase/Node.cpp>

template class NodeGroup<OrgNodeKind, OrgTokenKind>;

using org = OrgNodeKind;
using sem = OrgSemKind;

const OrgSet OrgAttachableCommands{
    org::CommandCaption,
};

const SemSet SemAttachableCommands{
    sem::Caption,
};

const OrgSet OrgTrailableCommands{
    org::SrcCode,
    org::QuoteBlock,
};

const SemSet SemTrailableCommands{
    sem::Code,
    sem::Quote,
};
