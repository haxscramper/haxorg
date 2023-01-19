#include "common.hpp"
#include <lexbase/Node.hpp>
#include <lexbase/Token.hpp>
#include <lexbase/PosStr.hpp>

#include <boost/describe/enum.hpp>

enum NodeKind : u8
{
    N1,
    N2,
    N3,
    N4
};


enum TokenKind : u8
{
    T1,
    T2,
    T3,
    T4
};

BOOST_DESCRIBE_ENUM(TokenKind, T1, T2, T3, T4);
BOOST_DESCRIBE_ENUM(NodeKind, N1, N2, N3, N4);

TEST_CASE("Core linearlized AST parser", "[node]") {
    ;
    ;
}
