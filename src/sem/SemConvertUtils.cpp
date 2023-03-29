#include <sem/SemConvert.hpp>
#include <hstd/stdlib/Func.hpp>


using namespace sem;
using namespace properties;

using org = OrgNodeKind;
using otk = OrgTokenKind;
using Err = OrgConverter::Errors;


OrgConverter::ConvertError OrgConverter::wrapError(
    CR<Error>      err,
    CR<OrgAdapter> adapter) {
    ConvertError result{err};
    auto         loc = getLoc(adapter);

    if (loc.has_value()) {
        result.setLoc(loc.value());
    }

    return result;
}

Opt<LineCol> OrgConverter::getLoc(CR<OrgAdapter> adapter) {
    int   offset  = 0;
    auto& g       = *adapter.group;
    bool  inRange = true;
    while (inRange) {
        bool leftOk  = false;
        bool rightOk = false;
        for (int i : Vec{-1, 1}) {
            int idx = adapter.id.getIndex() + offset * i;
            if (0 <= idx && idx < g.size()) {
                if (i == -1) {
                    leftOk = true;
                }
                if (i == 1) {
                    rightOk = true;
                }
                if (g.at(OrgId(idx)).isTerminal()) {
                    auto tok = g.tokens->at(g.at(OrgId(idx)).getToken());
                    if (tok.hasData()) {
                        PosStr str{tok.getText()};
                        return locationResolver(str);
                    }
                }
            }
        }
        if (!(leftOk || rightOk)) {
            inRange = false;
        }
        ++offset;
    }

    return std::nullopt;
}
