#pragma once

import org.lexbase.AstSpec;
import org.parse.OrgTypes;


using OrgSpec = astspec::AstSpec<OrgAdapter, OrgNodeKind, OrgSpecName>;

std::unique_ptr<OrgSpec> getOrgSpec();
