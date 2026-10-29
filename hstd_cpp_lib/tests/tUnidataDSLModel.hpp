/* clang-format off */
#pragma once
#include <hstd_cpp_lib/system/basic_templates.hpp>
#include <hstd_cpp_lib/system/reflection.hpp>
#include <hstd_cpp_lib/stdlib/containers/Opt.hpp>
#include <hstd_cpp_lib/stdlib/containers/Vec.hpp>
#include <hstd_cpp_lib/stdlib/containers/Map.hpp>
#include <hstd_cpp_lib/proto_serde/hstd_unidata_validate.hpp>
namespace hstd::unidata_dsl::test {
enum class Status : short int { Ready, Other, };
BOOST_DESCRIBE_ENUM_BEGIN(hstd::unidata_dsl::test::Status)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::Status, Ready)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::Status, Other)
BOOST_DESCRIBE_ENUM_END(hstd::unidata_dsl::test::Status)
enum class CheckKind : short int { Eq, Ne, Lt, Le, Add, Sub, Mul, Div, ConstFloat, ConstBool, And, Or, Not, Cond, CondLazy, Let, All, Exists, ExistsOne, Map, Filter, FilterMap, TakeWhile, GroupBy, Fold, Walk, Sum, Min, Max, StrSize, StrMatches, StrFormat, ListSize, ListContains, ListAt, ListSlice, ListSliceBounds, ListConcat, ListEmpty, MapSize, MapContains, MapGet, MapInsert, MapReplace, MapKeys, MapValues, MapEmpty, OptHasValue, OptValue, CaseIs, CaseWhich, CaseField, EnumIs, NthGet, IsDerived, TypeCond, TypeCondOptional, TypeOf, PathOf, EmptyCollections, };
BOOST_DESCRIBE_ENUM_BEGIN(hstd::unidata_dsl::test::CheckKind)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, Eq)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, Ne)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, Lt)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, Le)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, Add)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, Sub)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, Mul)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, Div)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, ConstFloat)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, ConstBool)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, And)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, Or)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, Not)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, Cond)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, CondLazy)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, Let)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, All)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, Exists)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, ExistsOne)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, Map)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, Filter)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, FilterMap)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, TakeWhile)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, GroupBy)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, Fold)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, Walk)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, Sum)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, Min)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, Max)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, StrSize)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, StrMatches)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, StrFormat)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, ListSize)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, ListContains)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, ListAt)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, ListSlice)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, ListSliceBounds)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, ListConcat)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, ListEmpty)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, MapSize)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, MapContains)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, MapGet)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, MapInsert)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, MapReplace)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, MapKeys)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, MapValues)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, MapEmpty)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, OptHasValue)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, OptValue)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, CaseIs)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, CaseWhich)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, CaseField)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, EnumIs)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, NthGet)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, IsDerived)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, TypeCond)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, TypeCondOptional)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, TypeOf)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, PathOf)
  BOOST_DESCRIBE_ENUM_ENTRY(hstd::unidata_dsl::test::CheckKind, EmptyCollections)
BOOST_DESCRIBE_ENUM_END(hstd::unidata_dsl::test::CheckKind)
struct TrivialText {
  BOOST_DESCRIBE_CLASS(TrivialText, (), (), (), (text, unidata_id));
  hstd::Str text;
  static constexpr std::string const unidata_id = "TrivialText";
  static hstd::ext::unidata::VerifyResult __check_text_textcheck(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyCheckCollection const* get_unidata_checks();
};

struct Base {
  BOOST_DESCRIBE_CLASS(Base, (), (), (), (id, unidata_id));
  int64_t id;
  static constexpr std::string const unidata_id = "Base";
  static hstd::ext::unidata::VerifyResult __check_record_basepositiveid(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyCheckCollection const* get_unidata_checks();
};

struct Derived : public hstd::unidata_dsl::test::Base {
  BOOST_DESCRIBE_CLASS(Derived, (Base), (), (), (weight, unidata_id));
  int64_t weight;
  static constexpr std::string const unidata_id = "Derived";
  static hstd::ext::unidata::VerifyResult __check_record_derivedpositiveweight(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyCheckCollection const* get_unidata_checks();
};

struct Choice {
  struct First {
    BOOST_DESCRIBE_CLASS(First, (), (), (), (value, unidata_id));
    int64_t value;
    static constexpr std::string const unidata_id = "Choice::First";
  };

  struct Second {
    BOOST_DESCRIBE_CLASS(Second, (), (), (), (label, unidata_id));
    hstd::Str label;
    static constexpr std::string const unidata_id = "Choice::Second";
  };

  BOOST_DESCRIBE_CLASS(Choice, (), (), (), (unidata_id));
  static constexpr std::string const unidata_id = "Choice";
};

struct OperationChecks {
  BOOST_DESCRIBE_CLASS(OperationChecks, (), (), (), (operation,
                                                     number,
                                                     real,
                                                     flag,
                                                     text,
                                                     numbers,
                                                     optionals,
                                                     mapping,
                                                     optional,
                                                     coords,
                                                     status,
                                                     base,
                                                     derived,
                                                     choice,
                                                     unidata_id));
  hstd::unidata_dsl::test::CheckKind operation;
  int64_t number;
  double real;
  bool flag;
  hstd::Str text;
  hstd::Vec<int64_t> numbers;
  hstd::Vec<hstd::Opt<int64_t>> optionals;
  hstd::UnorderedMap<hstd::Str, int64_t> mapping;
  hstd::Opt<int64_t> optional;
  std::tuple<int64_t, hstd::Str> coords;
  hstd::unidata_dsl::test::Status status;
  hstd::unidata_dsl::test::Base base;
  hstd::unidata_dsl::test::Derived derived;
  hstd::unidata_dsl::test::Choice choice;
  static constexpr std::string const unidata_id = "OperationChecks";
  static hstd::ext::unidata::VerifyResult __check_record_poc.eq(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.ne(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.lt(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.le(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.add(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.sub(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.mul(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.div(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.constfloat(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.constbool(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.and(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.or(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.not(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.cond(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.condlazy(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.all(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.exists(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.existsone(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.map(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.filter(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.filtermap(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.takewhile(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.groupby(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.fold(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.walk(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.sum(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.min(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.max(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.strsize(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.strmatches(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.strformat(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.listsize(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.listcontains(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.listat(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.listslice(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.listslicebounds(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.listconcat(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.listempty(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.mapsize(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.mapcontains(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.mapget(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.mapinsert(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.mapreplace(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.mapkeys(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.mapvalues(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.mapempty(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.opthasvalue(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.optvalue(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.caseis(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.casewhich(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.casefield(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.enumis(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.nthget(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.isderived(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.typecond(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.typecondoptional(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.typeof(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.pathof(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc.emptycollections(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyCheckCollection const* get_unidata_checks();
};

struct FieldChecks {
  BOOST_DESCRIBE_CLASS(FieldChecks, (), (), (), (padding, text, numbers, unidata_id));
  int64_t padding;
  hstd::Str text;
  hstd::Vec<int64_t> numbers;
  static constexpr std::string const unidata_id = "FieldChecks";
  static hstd::ext::unidata::VerifyResult __check_text_textcheck(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_numbers_numberscheck(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyCheckCollection const* get_unidata_checks();
};

struct MessageChecks {
  BOOST_DESCRIBE_CLASS(MessageChecks, (), (), (), (number,
                                                   real,
                                                   flag,
                                                   text,
                                                   numbers,
                                                   details,
                                                   unidata_id));
  int64_t number;
  double real;
  bool flag;
  hstd::Str text;
  hstd::Vec<int64_t> numbers;
  hstd::UnorderedMap<hstd::Str, int64_t> details;
  static constexpr std::string const unidata_id = "MessageChecks";
  static hstd::ext::unidata::VerifyResult __check_record_formatmessage(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyCheckCollection const* get_unidata_checks();
};

struct Node {
  BOOST_DESCRIBE_CLASS(Node, (), (), (), (id, unidata_id));
  hstd::Str id;
  static constexpr std::string const unidata_id = "Node";
};

struct Edge {
  BOOST_DESCRIBE_CLASS(Edge, (), (), (), (source, target, unidata_id));
  hstd::Str source;
  hstd::Str target;
  static constexpr std::string const unidata_id = "Edge";
};

struct Graph {
  BOOST_DESCRIBE_CLASS(Graph, (), (), (), (nodes, edges, unidata_id));
  hstd::Vec<hstd::unidata_dsl::test::Node> nodes;
  hstd::Vec<hstd::unidata_dsl::test::Edge> edges;
  static constexpr std::string const unidata_id = "Graph";
  static hstd::ext::unidata::VerifyResult __check_record_graphuniquenodeids(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_graphnodanglingedges(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyCheckCollection const* get_unidata_checks();
};

}
/* clang-format on */