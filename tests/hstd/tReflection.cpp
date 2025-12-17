#include <gtest/gtest.h>
#include <hstd/system/reflection.hpp>
#include <hstd/system/macros.hpp>
#include <hstd/stdlib/Formatter.hpp>
#include <hstd/system/aux_utils.hpp>
#include <hstd/stdlib/reflection_visitor.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/stdlib/Ranges.hpp>
#include "hstd_tests_common.hpp"
#include <hstd/stdlib/VariantFormatter.hpp>


using namespace hstd;

enum class TestEnum_EnumToString
{
    First,
    Second,
    Third
};
BOOST_DESCRIBE_ENUM(TestEnum_EnumToString, First, Second, Third);

TEST(Reflection, EnumToString) {


    std::string result = enum_serde<TestEnum_EnumToString>::to_string(
        TestEnum_EnumToString::Second);
    ASSERT_EQ(result, "Second");
}

enum class TestEnum_StringToEnum
{
    First,
    Second,
    Third
};
BOOST_DESCRIBE_ENUM(TestEnum_StringToEnum, First, Second, Third);

TEST(Reflection, StringToEnum) {


    auto result = enum_serde<TestEnum_StringToEnum>::from_string("Third");
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result.value(), TestEnum_StringToEnum::Third);
}

enum class TestEnum_DescribeEnumerator
{
    First,
    Second,
    Third
};
BOOST_DESCRIBE_ENUM(TestEnum_DescribeEnumerator, First, Second, Third);


TEST(Reflection, DescribeEnumerators) {
    auto enumerators = describe_enumerators<TestEnum_DescribeEnumerator>();
    ASSERT_EQ(enumerators.size(), 3);
    ASSERT_EQ(enumerators[0].name, "First");
    ASSERT_EQ(enumerators[1].name, "Second");
    ASSERT_EQ(enumerators[2].name, "Third");
}

enum class TestEnum_EnumeratorNames
{
    First,
    Second,
    Third
};
BOOST_DESCRIBE_ENUM(TestEnum_EnumeratorNames, First, Second, Third);


TEST(Reflection, EnumeratorNames) {

    auto names = enumerator_names<TestEnum_EnumeratorNames>();
    ASSERT_EQ(names.size(), 3);
    ASSERT_EQ(names[0], "First");
    ASSERT_EQ(names[1], "Second");
    ASSERT_EQ(names[2], "Third");
}

enum class TestEnum_ValueDomain
{
    First,
    Second,
    Third
};
BOOST_DESCRIBE_ENUM(TestEnum_ValueDomain, First, Second, Third);

TEST(Reflection, ValueDomain) {
    using E  = TestEnum_ValueDomain;
    using VD = value_domain<TestEnum_ValueDomain>;
    ASSERT_EQ(VD::low(), E::First);
    ASSERT_EQ(VD::high(), E::Third);
    ASSERT_EQ(VD::succ(E::Second), E::Third);
    ASSERT_EQ(VD::prev(E::Second), E::First);
    ASSERT_EQ(VD::ord(E::First), 0);
    ASSERT_EQ(VD::ord(E::Third), 2);
}

struct TestClass_DescribedClassPrinter1 {
    int a;
    int b;
};

BOOST_DESCRIBE_STRUCT(TestClass_DescribedClassPrinter1, (), (a, b));

struct TestClass_DescribedClassPrinter {
    int                              a;
    TestClass_DescribedClassPrinter1 b;
};

BOOST_DESCRIBE_STRUCT(TestClass_DescribedClassPrinter, (), (a, b));

TEST(Reflection, DescribedClassPrinter) {
    TestClass_DescribedClassPrinter obj{1, {2, 3}};

    std::string result   = fmt1(obj);
    std::string expected = std::string{"{.a = 1, .b = {.a = 2, .b = 3}}"};
    ASSERT_EQ(result, expected);
}

struct TestClass_EqualOnAllFields {
    int   a;
    float b;
};
BOOST_DESCRIBE_STRUCT(TestClass_EqualOnAllFields, (), (a, b));

TEST(Reflection, EqualOnAllFields) {

    TestClass_EqualOnAllFields obj1{1, 2.5f};
    TestClass_EqualOnAllFields obj2{1, 2.5f};
    ASSERT_TRUE(equal_on_all_fields(obj1, obj2));

    TestClass_EqualOnAllFields obj3{1, 3.5f};
    ASSERT_FALSE(equal_on_all_fields(obj1, obj3));
}

struct Type_FieldIterator_A {
    int base_field;
    BOOST_DESCRIBE_CLASS(Type_FieldIterator_A, (), (base_field), (), ());
};


struct Type_FieldIterator_1 : Type_FieldIterator_A {
    int a;
    int b;
    int c;
    BOOST_DESCRIBE_CLASS(
        Type_FieldIterator_1,
        (Type_FieldIterator_A),
        (a, b, c),
        (),
        ());
};

TEST(Reflection, FieldIterator) {
    {
        std::vector<std::string> visits;

        for_each_field_with_bases<Type_FieldIterator_1>(
            [&](auto&& field) { visits.push_back(field.name); });

        EXPECT_EQ(visits.size(), 4);
        EXPECT_EQ(visits.at(0), "base_field");
        EXPECT_EQ(visits.at(1), "a");
        EXPECT_EQ(visits.at(2), "b");
        EXPECT_EQ(visits.at(3), "c");
    }

    {
        std::vector<std::string> visits;

        for_each_field_with_bases<Type_FieldIterator_1>(
            [&](auto&& field) { visits.push_back(field.name); }, false);

        EXPECT_EQ(visits.size(), 4);
        EXPECT_EQ(visits.at(0), "a");
        EXPECT_EQ(visits.at(1), "b");
        EXPECT_EQ(visits.at(2), "c");
        EXPECT_EQ(visits.at(3), "base_field");
    }
}

struct Type_SubVariants {
    struct First {
        int f;
        DESC_FIELDS(First, (f));
    };
    struct Second {
        int f;
        DESC_FIELDS(Second, (f));
    };
    struct Third {
        int f;
        DESC_FIELDS(Third, (f));
    };
    SUB_VARIANTS(Kind, Data, data, getKind, First, Second, Third);
    Data data;
    DESC_FIELDS(Type_SubVariants, (data));
};

TEST(Reflection, SubVariants) {
    using T = Type_SubVariants;
    {
        T it{};
        EXPECT_EQ(it.getKind(), T::Kind::First);
        EXPECT_EQ(it.getFirst().f, T::First{}.f);
        EXPECT_THROW(it.getSecond(), ::bad_variant_access);
        EXPECT_EQ(fmt1(it), "First({.f = 0})");
    }

    {
        T it{T::Second{}};
        EXPECT_EQ(it.getKind(), T::Kind::Second);
        EXPECT_EQ(it.getSecond().f, T::Second{}.f);
        EXPECT_THROW(it.getFirst(), ::bad_variant_access);
    }

    {
        T it{T::Second{.f = 12}};
        EXPECT_EQ(it.getKind(), T::Kind::Second);
        EXPECT_EQ(it.getSecond().f, 12);
        EXPECT_THROW(it.getFirst(), ::bad_variant_access);

        it.data = T::First{.f = 24};

        EXPECT_EQ(it.getKind(), T::Kind::First);
        EXPECT_EQ(it.getFirst().f, 24);
        EXPECT_THROW(it.getSecond(), ::bad_variant_access);
    }
}

struct FieldIndexing_0items {
    BOOST_DESCRIBE_CLASS(FieldIndexing_0items, (), (), (), ());
};

struct FieldIndexing_1item {
    int field1;
    BOOST_DESCRIBE_CLASS(FieldIndexing_1item, (), (field1), (), ());
};

struct FieldIndexing_3items {
    int         field1;
    double      field2;
    std::string field3;
    BOOST_DESCRIBE_CLASS(
        FieldIndexing_3items,
        (),
        (field1, field2, field3),
        (),
        ());
};

struct FieldIndexing_Base {
    int   baseField1;
    float baseField2;
    BOOST_DESCRIBE_CLASS(
        FieldIndexing_Base,
        (),
        (baseField1, baseField2),
        (),
        ());
};

struct FieldIndexing_Derived : FieldIndexing_Base {
    std::string derivedField1;
    bool        derivedField2;
    BOOST_DESCRIBE_CLASS(
        FieldIndexing_Derived,
        (FieldIndexing_Base),
        (derivedField1, derivedField2),
        (),
        ());
};

struct FieldIndexing_Private {
  private:
    int f1;

  public:
    int  f2;
    int  getF1() { return f1; }
    void setF1(int value) { f1 = value; }


  public:
    BOOST_DESCRIBE_CLASS(FieldIndexing_Private, (), (f2), (), (f1));
};


TEST(Reflection, FieldIndexing) {
    auto own_tuple_size = []<typename T>(T const& t) {
        return std::tuple_size_v<decltype(class_to_total_ptr_tuple(t))>;
    };

    {
        using T = FieldIndexing_0items;
        T t;
        EXPECT_EQ(hstd::get_own_field_count<T>(), 0);
        EXPECT_EQ(hstd::get_total_field_count<T>(), 0);
        EXPECT_EQ(own_tuple_size(t), 0);
        EXPECT_THROW(
            hstd::get_field_ptr_by_own_index(t, 0), std::out_of_range);
        EXPECT_THROW(
            hstd::get_field_ptr_by_total_index(t, 0), std::out_of_range);
        EXPECT_THROW(
            hstd::get_field_ptr_by_own_index(t, -1), std::out_of_range);
        EXPECT_THROW(
            hstd::get_field_ptr_by_total_index(t, -1), std::out_of_range);
    }

    {
        using T = FieldIndexing_1item;
        T t{42};
        EXPECT_EQ(hstd::get_own_field_count<T>(), 1);
        EXPECT_EQ(hstd::get_total_field_count<T>(), 1);
        EXPECT_EQ(own_tuple_size(t), 1);

        void* ptr0 = hstd::get_field_ptr_by_own_index(t, 0);
        EXPECT_EQ(ptr0, static_cast<void*>(&t.field1));
        EXPECT_EQ(*static_cast<int*>(ptr0), 42);

        void* totalPtr0 = hstd::get_field_ptr_by_total_index(t, 0);
        EXPECT_EQ(totalPtr0, static_cast<void*>(&t.field1));

        EXPECT_THROW(
            hstd::get_field_ptr_by_own_index(t, 1), std::out_of_range);
        EXPECT_THROW(
            hstd::get_field_ptr_by_total_index(t, 1), std::out_of_range);
        EXPECT_THROW(
            hstd::get_field_ptr_by_own_index(t, -1), std::out_of_range);
    }

    {
        using T = FieldIndexing_3items;
        T t{123, 45.67, "test"};
        EXPECT_EQ(hstd::get_own_field_count<T>(), 3);
        EXPECT_EQ(hstd::get_total_field_count<T>(), 3);
        EXPECT_EQ(own_tuple_size(t), 3);

        void* ptr0 = hstd::get_field_ptr_by_own_index(t, 0);
        void* ptr1 = hstd::get_field_ptr_by_own_index(t, 1);
        void* ptr2 = hstd::get_field_ptr_by_own_index(t, 2);

        EXPECT_EQ(ptr0, static_cast<void*>(&t.field1));
        EXPECT_EQ(ptr1, static_cast<void*>(&t.field2));
        EXPECT_EQ(ptr2, static_cast<void*>(&t.field3));

        EXPECT_EQ(*static_cast<int*>(ptr0), 123);
        EXPECT_DOUBLE_EQ(*static_cast<double*>(ptr1), 45.67);
        EXPECT_EQ(*static_cast<std::string*>(ptr2), "test");

        void* totalPtr0 = hstd::get_field_ptr_by_total_index(t, 0);
        void* totalPtr1 = hstd::get_field_ptr_by_total_index(t, 1);
        void* totalPtr2 = hstd::get_field_ptr_by_total_index(t, 2);

        EXPECT_EQ(totalPtr0, ptr0);
        EXPECT_EQ(totalPtr1, ptr1);
        EXPECT_EQ(totalPtr2, ptr2);

        EXPECT_THROW(
            hstd::get_field_ptr_by_own_index(t, 3), std::out_of_range);
        EXPECT_THROW(
            hstd::get_field_ptr_by_total_index(t, 3), std::out_of_range);

        static_assert(
            std::is_same_v<decltype(&T::field1), decltype(&T::field1)>);

        EXPECT_EQ(hstd::get_own_field_index_by_ptr(&T::field1), 0);
        EXPECT_EQ(hstd::get_own_field_index_by_ptr(&T::field2), 1);
        EXPECT_EQ(hstd::get_own_field_index_by_ptr(&T::field3), 2);

        EXPECT_EQ(hstd::get_total_field_index_by_ptr(&T::field1), 0);
        EXPECT_EQ(hstd::get_total_field_index_by_ptr(&T::field2), 1);
        EXPECT_EQ(hstd::get_total_field_index_by_ptr(&T::field3), 2);
    }

    {
        using T = FieldIndexing_Base;
        T t{100, 3.14f};
        EXPECT_EQ(hstd::get_own_field_count<T>(), 2);
        EXPECT_EQ(hstd::get_total_field_count<T>(), 2);
        EXPECT_EQ(own_tuple_size(t), 2);

        void* ptr0 = hstd::get_field_ptr_by_own_index(t, 0);
        void* ptr1 = hstd::get_field_ptr_by_own_index(t, 1);

        EXPECT_EQ(*static_cast<int*>(ptr0), 100);
        EXPECT_FLOAT_EQ(*static_cast<float*>(ptr1), 3.14f);
    }

    {
        using T = FieldIndexing_Derived;
        T t{};
        t.baseField1    = 200;
        t.baseField2    = 2.71f;
        t.derivedField1 = "derived";
        t.derivedField2 = true;


        EXPECT_EQ(hstd::get_own_field_count<T>(), 2);
        static_assert(boost::describe::has_describe_bases<T>::value);
        EXPECT_EQ(hstd::get_total_field_count<T>(), 4);
        EXPECT_EQ(own_tuple_size(t), 4);

        void* ownPtr0 = hstd::get_field_ptr_by_own_index(t, 0);
        void* ownPtr1 = hstd::get_field_ptr_by_own_index(t, 1);

        EXPECT_EQ(ownPtr0, static_cast<void*>(&t.derivedField1));
        EXPECT_EQ(ownPtr1, static_cast<void*>(&t.derivedField2));
        EXPECT_EQ(*static_cast<std::string*>(ownPtr0), "derived");
        EXPECT_EQ(*static_cast<bool*>(ownPtr1), true);

        void* totalPtr0 = hstd::get_field_ptr_by_total_index(t, 0);
        void* totalPtr1 = hstd::get_field_ptr_by_total_index(t, 1);
        void* totalPtr2 = hstd::get_field_ptr_by_total_index(t, 2);
        void* totalPtr3 = hstd::get_field_ptr_by_total_index(t, 3);

        EXPECT_EQ(totalPtr0, static_cast<void*>(&t.baseField1));
        EXPECT_EQ(totalPtr1, static_cast<void*>(&t.baseField2));
        EXPECT_EQ(totalPtr2, static_cast<void*>(&t.derivedField1));
        EXPECT_EQ(totalPtr3, static_cast<void*>(&t.derivedField2));

        EXPECT_EQ(*static_cast<int*>(totalPtr0), 200);
        EXPECT_FLOAT_EQ(*static_cast<float*>(totalPtr1), 2.71f);
        EXPECT_EQ(*static_cast<std::string*>(totalPtr2), "derived");
        EXPECT_EQ(*static_cast<bool*>(totalPtr3), true);

        EXPECT_THROW(
            hstd::get_field_ptr_by_own_index(t, 2), std::out_of_range);
        EXPECT_THROW(
            hstd::get_field_ptr_by_total_index(t, 4), std::out_of_range);
        EXPECT_THROW(
            hstd::get_field_ptr_by_own_index(t, -1), std::out_of_range);
        EXPECT_THROW(
            hstd::get_field_ptr_by_total_index(t, -1), std::out_of_range);


        EXPECT_EQ(hstd::get_own_field_index_by_ptr(&T::baseField1), 0);
        EXPECT_EQ(hstd::get_own_field_index_by_ptr(&T::baseField2), 1);
        EXPECT_EQ(hstd::get_total_field_index_by_ptr(&T::baseField1), 0);
        EXPECT_EQ(hstd::get_total_field_index_by_ptr(&T::baseField2), 1);

        EXPECT_EQ(hstd::get_own_field_index_by_ptr(&T::derivedField1), 0);
        EXPECT_EQ(hstd::get_own_field_index_by_ptr(&T::derivedField2), 1);
        EXPECT_EQ(
            hstd::get_total_field_index_by_ptr(&T::derivedField1), 2);
        EXPECT_EQ(
            hstd::get_total_field_index_by_ptr(&T::derivedField2), 3);
    }

    {
        using T = FieldIndexing_Private;
        T t{};
        t.f2 = 1233;
        t.setF1(2000);
        EXPECT_EQ(hstd::get_own_field_count<T>(), 2);
        EXPECT_EQ(hstd::get_total_field_count<T>(), 2);
        EXPECT_EQ(own_tuple_size(t), 2);
        auto tuple = class_to_total_ptr_tuple(t);
        EXPECT_EQ(*std::get<0>(tuple), 1233);
        EXPECT_EQ(*std::get<1>(tuple), 2000);
        *const_cast<int*>(std::get<1>(tuple)) = 123333;
        EXPECT_EQ(t.getF1(), 123333);
    }
}

// Insert this test after the existing FieldIndexing test:

HSTD_REGISTER_TYPE_FIELD_NAMES(FieldIndexing_0items);
HSTD_REGISTER_TYPE_FIELD_NAMES(FieldIndexing_3items);
HSTD_REGISTER_TYPE_FIELD_NAMES(FieldIndexing_Base);
HSTD_REGISTER_TYPE_FIELD_NAMES(FieldIndexing_Derived);

TEST(Reflection, GlobalFieldNamingRegistry) {
    // Register types

    // Test 0 items type
    {
        using T            = FieldIndexing_0items;
        std::type_index id = std::type_index(typeid(T));
        EXPECT_EQ(hstd::get_registered_field_count<T>(), 0);
        EXPECT_EQ(hstd::get_registered_field_count(id), 0);
        EXPECT_THROW(
            hstd::get_registered_field_name<T>(0), std::out_of_range);
        EXPECT_THROW(
            hstd::get_registered_field_name(id, 0), std::out_of_range);
    }

    // Test 3 items type
    {
        using T            = FieldIndexing_3items;
        std::type_index id = std::type_index(typeid(T));
        EXPECT_EQ(hstd::get_registered_field_count<T>(), 3);
        EXPECT_EQ(hstd::get_registered_field_count(id), 3);

        EXPECT_EQ(hstd::get_registered_field_name<T>(0), "field1");
        EXPECT_EQ(hstd::get_registered_field_name<T>(1), "field2");
        EXPECT_EQ(hstd::get_registered_field_name<T>(2), "field3");

        EXPECT_EQ(hstd::get_registered_field_name(id, 0), "field1");
        EXPECT_EQ(hstd::get_registered_field_name(id, 1), "field2");
        EXPECT_EQ(hstd::get_registered_field_name(id, 2), "field3");

        EXPECT_THROW(
            hstd::get_registered_field_name<T>(3), std::out_of_range);
        EXPECT_THROW(
            hstd::get_registered_field_name(id, 3), std::out_of_range);
    }

    // Test base type
    {
        using T            = FieldIndexing_Base;
        std::type_index id = std::type_index(typeid(T));
        EXPECT_EQ(hstd::get_registered_field_count<T>(), 2);
        EXPECT_EQ(hstd::get_registered_field_count(id), 2);

        EXPECT_EQ(hstd::get_registered_field_name<T>(0), "baseField1");
        EXPECT_EQ(hstd::get_registered_field_name<T>(1), "baseField2");

        EXPECT_EQ(hstd::get_registered_field_name(id, 0), "baseField1");
        EXPECT_EQ(hstd::get_registered_field_name(id, 1), "baseField2");
    }

    // Test derived type (should include base fields)
    {
        using T            = FieldIndexing_Derived;
        std::type_index id = std::type_index(typeid(T));
        EXPECT_EQ(hstd::get_registered_field_count<T>(), 4);
        EXPECT_EQ(hstd::get_registered_field_count(id), 4);

        // Base fields should come first
        EXPECT_EQ(hstd::get_registered_field_name<T>(0), "baseField1");
        EXPECT_EQ(hstd::get_registered_field_name<T>(1), "baseField2");
        // Then derived fields
        EXPECT_EQ(hstd::get_registered_field_name<T>(2), "derivedField1");
        EXPECT_EQ(hstd::get_registered_field_name<T>(3), "derivedField2");

        // Test with type_index
        EXPECT_EQ(hstd::get_registered_field_name(id, 0), "baseField1");
        EXPECT_EQ(hstd::get_registered_field_name(id, 1), "baseField2");
        EXPECT_EQ(hstd::get_registered_field_name(id, 2), "derivedField1");
        EXPECT_EQ(hstd::get_registered_field_name(id, 3), "derivedField2");

        EXPECT_THROW(
            hstd::get_registered_field_name<T>(4), std::out_of_range);
        EXPECT_THROW(
            hstd::get_registered_field_name(id, 4), std::out_of_range);
    }

    // Test unregistered type throws
    {
        struct UnregisteredType {
            int field;
        };
        EXPECT_THROW(
            hstd::get_registered_field_count(
                std::type_index(typeid(UnregisteredType))),
            std::runtime_error);
        EXPECT_THROW(
            hstd::get_registered_field_name(
                std::type_index(typeid(UnregisteredType)), 0),
            std::runtime_error);
    }

    {
        std::type_index id = std::type_index(
            typeid(reflection_test::reflection_named));

        EXPECT_EQ(hstd::get_registered_field_count(id), 2);
        EXPECT_EQ(hstd::get_registered_field_name(id, 0), "f1");
        EXPECT_EQ(hstd::get_registered_field_name(id, 1), "f2");
    }
}


struct ReflData {
    int         f1;
    std::string f2;
    char        f3;
    DESC_FIELDS(ReflData, (f1, f2, f3));
};

struct ReflTag1 {
    using field_name_type = std::string;
};

template <>
struct ReflTypeTraits<ReflTag1> {
    using AnyTypeTuple     = std::tuple<Str, std::string>;
    using AnyFormatterType = AnyFormatter<Str, std::string>;
    using AnyHasherType    = AnyHasher<Str, std::string>;
    using AnyEqualType     = AnyEqual<Str, std::string>;

    using ReflPathStoreType = SmallVec<ReflPathItem<ReflTag1>, 2>;

    template <typename T>
    static Str InitFieldName(T const& value, auto const& field) {
        return field.name;
    }

    static ReflPath<ReflTag1> AddPathItem(
        ReflPath<ReflTag1>     res,
        ReflPathItem<ReflTag1> item) {
        res.path.push_back(item);
        return res;
    }
};

TEST(ReflectionVisitor, FieldNames) {
    auto items = reflSubItems<ReflData, ReflTag1>(ReflData{});
    EXPECT_EQ(items.size(), 3);
    EXPECT_EQ(items.at(0).getFieldName().name, "f1");
    EXPECT_EQ(items.at(1).getFieldName().name, "f2");
    EXPECT_EQ(items.at(2).getFieldName().name, "f3");

    std::vector<std::string>  visitNames;
    ReflRecursiveVisitContext ctx;
    reflVisitAll<ReflData, ReflTag1>(
        ReflData{},
        {},
        ctx,
        overloaded{
            [&](ReflPath<ReflTag1> const& path, ReflData const& field) {
                visitNames.push_back("ReflData");
            },
            [&](ReflPath<ReflTag1> const& path, std::string const& field) {
                visitNames.push_back("std::string");
            },
            [&](ReflPath<ReflTag1> const& path, int const& field) {
                visitNames.push_back("int");
            },
            [&](ReflPath<ReflTag1> const& path, char const& field) {
                visitNames.push_back("char");
            },
        });

    EXPECT_EQ(
        visitNames,
        (Vec<std::string>{
            "ReflData",
            "int",
            "std::string",
            "char",
        }));
}


TEST(ReflectionVisitor, UnorderedMap) {
    using Type = UnorderedMap<std::string, int>;
    Type map;
    map["f1"] = 2;
    map["f2"] = 3;
    map["f3"] = 4;

    auto items = reflSubItems<Type, ReflTag1>(map);
    EXPECT_EQ(items.size(), 3);
    EXPECT_EQ(items.at(0).getAnyKey().get<std::string>(), "f1");
    EXPECT_EQ(items.at(1).getAnyKey().get<std::string>(), "f2");
    EXPECT_EQ(items.at(2).getAnyKey().get<std::string>(), "f3");

    std::vector<std::string>  visitNames;
    ReflRecursiveVisitContext ctx;
    reflVisitAll<Type, ReflTag1>(
        map,
        {},
        ctx,
        overloaded{
            [&](ReflPath<ReflTag1> const&             path,
                UnorderedMap<std::string, int> const& field) {
                visitNames.push_back("map");
            },
            [&](ReflPath<ReflTag1> const& path, int const& field) {
                visitNames.push_back("int");
            },
        });

    EXPECT_EQ(
        visitNames,
        (Vec<std::string>{
            "map",
            "int",
            "int",
            "int",
        }));
}

TEST(ReflectionVisitor, Vector) {
    using Type = Vec<std::string>;
    Type map{"f1", "f2", "f3"};

    auto items = reflSubItems<Type, ReflTag1>(map);
    EXPECT_EQ(items.size(), 3);
    EXPECT_EQ(items.at(0).getIndex().index, 0);
    EXPECT_EQ(items.at(1).getIndex().index, 1);
    EXPECT_EQ(items.at(2).getIndex().index, 2);

    std::vector<std::string>  visitNames;
    ReflRecursiveVisitContext ctx;
    reflVisitAll<Type, ReflTag1>(
        map,
        {},
        ctx,
        overloaded{
            [&](ReflPath<ReflTag1> const& path,
                Vec<std::string> const&   field) {
                visitNames.push_back("vec");
            },
            [&](ReflPath<ReflTag1> const& path, std::string const& field) {
                visitNames.push_back("std::string");
            },
        });

    EXPECT_EQ(
        visitNames,
        (Vec<std::string>{
            "vec",
            "std::string",
            "std::string",
            "std::string",
        }));
}

struct CustomData {
    int value;
    DESC_FIELDS(CustomData, (value));
};

using VariantType = std::variant<int, std::string, CustomData>;
using TupleType   = std::tuple<int, std::string, CustomData>;

struct DataStructure {
    std::unordered_set<int>              uset;
    std::unordered_map<std::string, int> umap;
    std::vector<std::string>             vec;
    std::string                          str;
    CustomData                           custom;
    VariantType                          variant;
    std::pair<int, std::string>          pair;
    TupleType                            tuple;
    std::nullptr_t                       nullp;
    std::optional<int>                   opt;
    int                                  regularField;
    std::shared_ptr<int>                 sharedPtr;
    std::unique_ptr<int>                 uniquePtr;
    DESC_FIELDS(
        DataStructure,
        (uset,
         umap,
         vec,
         str,
         custom,
         variant,
         pair,
         tuple,
         nullp,
         opt,
         regularField,
         sharedPtr,
         uniquePtr));
};

TEST(ReflectionVisitor, ComplexDataStructure) {

    DataStructure data;
    ReflVisitor<DataStructure, ReflTag1>::subitems(data);

    std::vector<std::string>  visitNames;
    ReflRecursiveVisitContext ctx;
    reflVisitAll<DataStructure, ReflTag1>(
        data,
        {},
        ctx,
        overloaded{
            [&](ReflPath<ReflTag1> const& path,
                DataStructure const&      field) {
                visitNames.push_back("DataStructure");
            },
            [&](ReflPath<ReflTag1> const&      path,
                std::unordered_set<int> const& field) {
                visitNames.push_back("std::unordered_set<int>");
            },
            [&](ReflPath<ReflTag1> const&                   path,
                std::unordered_map<std::string, int> const& field) {
                visitNames.push_back(
                    "std::unordered_map<std::string, int>");
            },
            [&](ReflPath<ReflTag1> const&       path,
                std::vector<std::string> const& field) {
                visitNames.push_back("std::vector<std::string>");
            },
            [&](ReflPath<ReflTag1> const& path, std::string const& field) {
                visitNames.push_back("std::string");
            },
            [&](ReflPath<ReflTag1> const& path, CustomData const& field) {
                visitNames.push_back("CustomData");
            },
            [&](ReflPath<ReflTag1> const& path, VariantType const& field) {
                visitNames.push_back("VariantType");
            },
            [&](ReflPath<ReflTag1> const&          path,
                std::pair<int, std::string> const& field) {
                visitNames.push_back("std::pair<int, std::string>");
            },
            [&](ReflPath<ReflTag1> const& path, TupleType const& field) {
                visitNames.push_back("TupleType");
            },
            [&](ReflPath<ReflTag1> const& path,
                std::nullptr_t const&     field) {
                visitNames.push_back("std::nullptr_t");
            },
            [&](ReflPath<ReflTag1> const& path,
                std::optional<int> const& field) {
                visitNames.push_back("std::optional<int>");
            },
            [&](ReflPath<ReflTag1> const& path, int const& field) {
                visitNames.push_back("int");
            },
            [&](ReflPath<ReflTag1> const&   path,
                std::shared_ptr<int> const& field) {
                visitNames.push_back("std::shared_ptr<int>");
            },
            [&](ReflPath<ReflTag1> const&   path,
                std::unique_ptr<int> const& field) {
                visitNames.push_back("std::unique_ptr<int>");
            },
        });

    EXPECT_EQ(
        visitNames,
        (std::vector<std::string>{
            "DataStructure",
            "std::unordered_set<int>",
            "std::unordered_map<std::string, int>",
            "std::vector<std::string>",
            "std::string",
            "CustomData",
            "int",
            "VariantType",
            "int",
            "std::pair<int, std::string>",
            "int",
            "std::string",
            "TupleType",
            "int",
            "std::string",
            "CustomData",
            "int",
            "std::nullptr_t",
            "std::optional<int>",
            "int",
            "std::shared_ptr<int>",
            "std::unique_ptr<int>",
        }));
}

TEST(ReflectionVisitor, PopulatedDataStructure) {
    DataStructure data;
    data.uset    = {1, 2, 3};
    data.umap    = {{"one", 1}, {"two", 2}};
    data.vec     = {"hello", "world"};
    data.str     = "test string";
    data.custom  = CustomData{42};
    data.variant = std::string("variant string");
    data.pair    = std::make_pair(10, "pair string");
    data.tuple   = std::make_tuple(20, "tuple string", CustomData{84});
    data.nullp   = nullptr;
    data.opt     = 100;
    data.regularField = 200;
    data.sharedPtr    = std::make_shared<int>(300);
    data.uniquePtr    = std::make_unique<int>(400);

    std::unordered_map<
        ReflPath<ReflTag1>,
        std::string,
        ReflPathHasher<ReflTag1>,
        ReflPathComparator<ReflTag1>>
                              visitedValues;
    ReflRecursiveVisitContext ctx;
    reflVisitAll<DataStructure, ReflTag1>(
        data,
        {},
        ctx,
        overloaded{[&](ReflPath<ReflTag1> const& path, auto const& field) {
            std::stringstream ss;
            ss << fmt1(field);
            visitedValues[path] = ss.str();
        }});

    std::unordered_map<
        ReflPath<ReflTag1>,
        Opt<std::string>,
        ReflPathHasher<ReflTag1>,
        ReflPathComparator<ReflTag1>>
        expectedValues;

    { // root item
        ReflPath<ReflTag1> path;
        expectedValues[path] = std::nullopt;
    }

    {
        ReflPath<ReflTag1> path;
        path.path.push_back(ReflPathItem<ReflTag1>::FromFieldName("pair"));
        expectedValues[path] = std::nullopt;
    }
    {
        ReflPath<ReflTag1> path;
        path.path.push_back(ReflPathItem<ReflTag1>::FromFieldName("uset"));
        expectedValues[path] = std::nullopt;
    }

    {
        ReflPath<ReflTag1> path;
        path.path.push_back(
            ReflPathItem<ReflTag1>::FromFieldName("tuple"));
        expectedValues[path] = std::nullopt;
    }
    {
        ReflPath<ReflTag1> path;
        path.path.push_back(ReflPathItem<ReflTag1>::FromFieldName("vec"));
        expectedValues[path] = std::nullopt;
    }
    {
        ReflPath<ReflTag1> path;
        path.path.push_back(
            ReflPathItem<ReflTag1>::FromFieldName("sharedPtr"));
        expectedValues[path] = std::nullopt;
    }
    {
        ReflPath<ReflTag1> path;
        path.path.push_back(ReflPathItem<ReflTag1>::FromFieldName("umap"));
        expectedValues[path] = std::nullopt;
    }
    {
        ReflPath<ReflTag1> path;
        path.path.push_back(ReflPathItem<ReflTag1>::FromFieldName("opt"));
        expectedValues[path] = std::nullopt;
    }
    {
        ReflPath<ReflTag1> path;
        path.path.push_back(
            ReflPathItem<ReflTag1>::FromFieldName("uniquePtr"));
        expectedValues[path] = std::nullopt;
    }
    {
        ReflPath<ReflTag1> path;
        path.path.push_back(
            ReflPathItem<ReflTag1>::FromFieldName("custom"));
        expectedValues[path] = std::nullopt;
    }
    {
        ReflPath<ReflTag1> path;
        path.path.push_back(ReflPathItem<ReflTag1>::FromFieldName("str"));
        expectedValues[path] = "test string";
    }
    {
        ReflPath<ReflTag1> path;
        path.path.push_back(
            ReflPathItem<ReflTag1>::FromFieldName("regularField"));
        expectedValues[path] = "200";
    }
    {
        ReflPath<ReflTag1> path;
        path.path.push_back(
            ReflPathItem<ReflTag1>::FromFieldName("custom"));
        path.path.push_back(
            ReflPathItem<ReflTag1>::FromFieldName("value"));
        expectedValues[path] = "42";
    }
    {
        Vec<int> sorted_uset = sorted(data.uset | rs::to<Vec>());
        for (int i = 0; i < data.uset.size(); ++i) {
            ReflPath<ReflTag1> path;
            path.path.push_back(
                ReflPathItem<ReflTag1>::FromFieldName("uset"));
            path.path.push_back(ReflPathItem<ReflTag1>::FromIndex(i));
            expectedValues[path] = fmt1(sorted_uset.at(i));
        }
    }
    for (auto const& [key, val] : data.umap) {
        ReflPath<ReflTag1> path;
        path.path.push_back(ReflPathItem<ReflTag1>::FromFieldName("umap"));
        path.path.push_back(ReflPathItem<ReflTag1>::FromAnyKey(key));
        expectedValues[path] = std::to_string(val);
    }
    for (size_t i = 0; i < data.vec.size(); ++i) {
        ReflPath<ReflTag1> path;
        path.path.push_back(ReflPathItem<ReflTag1>::FromFieldName("vec"));
        path.path.push_back(
            ReflPathItem<ReflTag1>::FromIndex(static_cast<int>(i)));
        expectedValues[path] = data.vec[i];
    }
    {
        ReflPath<ReflTag1> path;
        path.path.push_back(
            ReflPathItem<ReflTag1>::FromFieldName("variant"));
        path.path.push_back(ReflPathItem<ReflTag1>::FromIndex(1));
        expectedValues[path] = std::get<std::string>(data.variant);
    }
    {
        ReflPath<ReflTag1> path;
        path.path.push_back(
            ReflPathItem<ReflTag1>::FromFieldName("variant"));
        expectedValues[path] = std::nullopt;
    }
    {
        ReflPath<ReflTag1> path;
        path.path.push_back(ReflPathItem<ReflTag1>::FromFieldName("opt"));
        path.path.push_back(ReflPathItem<ReflTag1>::FromDeref());
        expectedValues[path] = "100";
    }
    {
        ReflPath<ReflTag1> path;
        path.path.push_back(
            ReflPathItem<ReflTag1>::FromFieldName("sharedPtr"));
        path.path.push_back(ReflPathItem<ReflTag1>::FromDeref());
        expectedValues[path] = "300";
    }
    {
        ReflPath<ReflTag1> path;
        path.path.push_back(
            ReflPathItem<ReflTag1>::FromFieldName("uniquePtr"));
        path.path.push_back(ReflPathItem<ReflTag1>::FromDeref());
        expectedValues[path] = "400";
    }
    { // `data.pair`
        ReflPath<ReflTag1> path_first;
        path_first.path.push_back(
            ReflPathItem<ReflTag1>::FromFieldName("pair"));
        path_first.path.push_back(ReflPathItem<ReflTag1>::FromIndex(0));
        expectedValues[path_first] = "10";

        ReflPath<ReflTag1> path_second;
        path_second.path.push_back(
            ReflPathItem<ReflTag1>::FromFieldName("pair"));
        path_second.path.push_back(ReflPathItem<ReflTag1>::FromIndex(1));
        expectedValues[path_second] = "pair string";
    }
    {
        ReflPath<ReflTag1> path0;
        path0.path.push_back(
            ReflPathItem<ReflTag1>::FromFieldName("tuple"));
        path0.path.push_back(ReflPathItem<ReflTag1>::FromIndex(0));
        expectedValues[path0] = "20";

        ReflPath<ReflTag1> path1;
        path1.path.push_back(
            ReflPathItem<ReflTag1>::FromFieldName("tuple"));
        path1.path.push_back(ReflPathItem<ReflTag1>::FromIndex(1));
        expectedValues[path1] = "tuple string";

        ReflPath<ReflTag1> path2;
        path2.path.push_back(
            ReflPathItem<ReflTag1>::FromFieldName("tuple"));
        path2.path.push_back(ReflPathItem<ReflTag1>::FromIndex(2));
        path2.path.push_back(
            ReflPathItem<ReflTag1>::FromFieldName("value"));
        expectedValues[path2] = "84";

        ReflPath<ReflTag1> path3;
        path3.path.push_back(
            ReflPathItem<ReflTag1>::FromFieldName("tuple"));
        path3.path.push_back(ReflPathItem<ReflTag1>::FromIndex(2));
        expectedValues[path3] = std::nullopt;
    }
    {
        ReflPath<ReflTag1> path;
        path.path.push_back(
            ReflPathItem<ReflTag1>::FromFieldName("nullp"));
        expectedValues[path] = "0x0";
    }

    for (const auto& [path, value] : expectedValues) {
        auto it = visitedValues.find(path);
        EXPECT_NE(it, visitedValues.end()) << fmt("No path {}", path);
        if (value) {
            EXPECT_EQ(it->second, value.value())
                << fmt("{} -> {} != {}", path, it->second, value);
        }
    }

    for (const auto& [path, value] : visitedValues) {
        auto it = expectedValues.find(path);
        EXPECT_NE(it, expectedValues.end())
            << fmt("Unexpected path {}", path);
    }
}
