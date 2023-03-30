#pragma once

#include <lexbase/AstSpec.hpp>
#include <parse/OrgTypes.hpp>


enum class OrgSpecName
{
    Unnamed,
    Result,
    Link,
    Protocol,
    Desc,
    Args,
    Name,
    Definition,
    Body,
    HeaderArgs,
    File,
    Kind,
    Lang,
    Prefix,
    Text,
    Todo,
    Urgency,
    Title,
    Completion,
    Head,
    Subnodes,
    Properties,
    Logbook,
    Description,
    Logs,
    Newstate,
    Oldstate,
    Time,
    From,
    EndArgs,
    Flags,
    Value,
    Assoc,
    Main,
    Hash,
    Bullet,
    Counter,
    Checkbox,
    Header,
    To,
    Diff,
    Property,
    Subname,
    Values,
    Cells,
    Rows,
    Lines,
    Chunks,
};

using OrgSpec = astspec::AstSpec<OrgAdapter, OrgNodeKind, OrgSpecName>;

extern OrgSpec spec;
