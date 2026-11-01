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
  static void __populate_expression_runtime(hstd::ext::unidata::EvalRuntime& expression_runtime);
  static hstd::ext::unidata::VerifyResult __check_text_text_check(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyCheckCollection const* get_unidata_checks();
};

struct Base {
  BOOST_DESCRIBE_CLASS(Base, (), (), (), (id, unidata_id));
  int64_t id;
  static constexpr std::string const unidata_id = "Base";
  static void __populate_expression_runtime(hstd::ext::unidata::EvalRuntime& expression_runtime);
  static hstd::ext::unidata::VerifyResult __check_record_base_positive_id(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyCheckCollection const* get_unidata_checks();
};

struct Derived : public hstd::unidata_dsl::test::Base {
  BOOST_DESCRIBE_CLASS(Derived, (Base), (), (), (weight, unidata_id));
  int64_t weight;
  static constexpr std::string const unidata_id = "Derived";
  static void __populate_expression_runtime(hstd::ext::unidata::EvalRuntime& expression_runtime);
  static hstd::ext::unidata::VerifyResult __check_record_derived_positive_weight(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
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

  using Data = std::variant<hstd::unidata_dsl::test::Choice::First, hstd::unidata_dsl::test::Choice::Second>;
  enum class Kind : short int { First, Second, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, First, Second)
  using variant_enum_type = hstd::unidata_dsl::test::Choice::Kind;
  using variant_data_type = hstd::unidata_dsl::test::Choice::Data;
  BOOST_DESCRIBE_CLASS(Choice, (), (), (), (data, unidata_id));
  hstd::unidata_dsl::test::Choice::Data data;
  static constexpr std::string const unidata_id = "Choice";
  bool isFirst() const;
  hstd::unidata_dsl::test::Choice::First const& getFirst() const;
  hstd::unidata_dsl::test::Choice::First& getFirst();
  bool isSecond() const;
  hstd::unidata_dsl::test::Choice::Second const& getSecond() const;
  hstd::unidata_dsl::test::Choice::Second& getSecond();
  static hstd::unidata_dsl::test::Choice::Kind getKind(hstd::unidata_dsl::test::Choice::Data const& __input);
  hstd::unidata_dsl::test::Choice::Kind getKind() const;
  char const* sub_variant_get_name() const;
  hstd::unidata_dsl::test::Choice::Data const& sub_variant_get_data() const;
  hstd::unidata_dsl::test::Choice::Kind sub_variant_get_kind() const;
};

struct OperationChecks {
  BOOST_DESCRIBE_CLASS(OperationChecks, (), (), (), (operation
                                                     , number
                                                     , real
                                                     , flag
                                                     , text
                                                     , numbers
                                                     , optionals
                                                     , mapping
                                                     , optional
                                                     , coords
                                                     , status
                                                     , base
                                                     , derived
                                                     , choice
                                                     , unidata_id));
  hstd::unidata_dsl::test::CheckKind operation;
  int64_t number;
  double real;
  bool flag;
  hstd::Str text;
  hstd::Vec<int64_t> numbers;
  hstd::Vec<hstd::Opt<int64_t>> optionals;
  hstd::UnorderedMap<hstd::Str, int64_t> mapping;
  hstd::Opt<int64_t> optional;
  hstd::Tuple<int64_t, hstd::Str> coords;
  hstd::unidata_dsl::test::Status status;
  hstd::unidata_dsl::test::Base base;
  hstd::unidata_dsl::test::Derived derived;
  hstd::unidata_dsl::test::Choice choice;
  static constexpr std::string const unidata_id = "OperationChecks";
  static void __populate_expression_runtime(hstd::ext::unidata::EvalRuntime& expression_runtime);
  static hstd::ext::unidata::VerifyResult __check_record_poc_Eq(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_Ne(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_Lt(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_Le(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_Add(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_Sub(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_Mul(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_Div(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_ConstFloat(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_ConstBool(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_And(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_Or(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_Not(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_Cond(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_CondLazy(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_Let(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_All(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_Exists(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_ExistsOne(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_Map(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_Filter(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_FilterMap(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_TakeWhile(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_GroupBy(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_Fold(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_Walk(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_Sum(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_Min(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_Max(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_StrSize(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_StrMatches(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_StrFormat(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_ListSize(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_ListContains(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_ListAt(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_ListSlice(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_ListSliceBounds(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_ListConcat(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_ListEmpty(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_MapSize(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_MapContains(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_MapGet(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_MapInsert(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_MapReplace(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_MapKeys(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_MapValues(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_MapEmpty(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_OptHasValue(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_OptValue(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_CaseIs(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_CaseWhich(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_CaseField(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_EnumIs(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_NthGet(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_IsDerived(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_TypeCond(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_TypeCondOptional(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_TypeOf(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_PathOf(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_poc_EmptyCollections(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyCheckCollection const* get_unidata_checks();
};

struct FieldChecks {
  BOOST_DESCRIBE_CLASS(FieldChecks, (), (), (), (padding, text, numbers, unidata_id));
  int64_t padding;
  hstd::Str text;
  hstd::Vec<int64_t> numbers;
  static constexpr std::string const unidata_id = "FieldChecks";
  static void __populate_expression_runtime(hstd::ext::unidata::EvalRuntime& expression_runtime);
  static hstd::ext::unidata::VerifyResult __check_text_text_check(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_numbers_numbers_check(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyCheckCollection const* get_unidata_checks();
};

struct MessageChecks {
  BOOST_DESCRIBE_CLASS(MessageChecks, (), (), (), (number
                                                   , real
                                                   , flag
                                                   , text
                                                   , numbers
                                                   , details
                                                   , unidata_id));
  int64_t number;
  double real;
  bool flag;
  hstd::Str text;
  hstd::Vec<int64_t> numbers;
  hstd::UnorderedMap<hstd::Str, int64_t> details;
  static constexpr std::string const unidata_id = "MessageChecks";
  static void __populate_expression_runtime(hstd::ext::unidata::EvalRuntime& expression_runtime);
  static hstd::ext::unidata::VerifyResult __check_record_format_message(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
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
  static void __populate_expression_runtime(hstd::ext::unidata::EvalRuntime& expression_runtime);
  static hstd::ext::unidata::VerifyResult __check_record_graph_unique_node_ids(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyResult __check_record_graph_no_dangling_edges(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyCheckCollection const* get_unidata_checks();
};

struct MultiValueCond {
  BOOST_DESCRIBE_CLASS(MultiValueCond, (), (), (), (field, unidata_id));
  int64_t field;
  static constexpr std::string const unidata_id = "MultiValueCond";
  static void __populate_expression_runtime(hstd::ext::unidata::EvalRuntime& expression_runtime);
  static hstd::ext::unidata::VerifyResult __check_field_field_check(hstd::ext::unidata::VerifyContext const* ctx, void const* value);
  static hstd::ext::unidata::VerifyCheckCollection const* get_unidata_checks();
};

}
/* clang-format on */