#include "base_token.hpp"

using namespace hstd;
using namespace org::parse;

#include <haxorg/lexbase/TraceStructured.hpp>

using namespace org::report;


struct OrgLexerImpl {
    LexerParams p;

    struct PushInfo {
        int         stateId; /// Name of the state pushed into stack
        int         line;    /// Line in the source where state triggered
        int         column;  /// code column
        int         rule;    /// Line in the rule file
        std::string matched; /// matched text content
    };

    hstd::Vec<PushInfo> states;

    OrgTokenGroup* tokens;
    void           add(OrgTokenKind token);
    std::string    state_name(int name);
    void           unknown();
};


void OrgLexerImpl::add(OrgTokenKind token) {}


OrgTokenGroup org::parse::tokenize(
    char const*,
    int,
    org::parse::LexerParams const&) {
    OrgTokenGroup result;
    OrgLexerImpl  impl{};
    impl.tokens = &result;

    return result;
}
