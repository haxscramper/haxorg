#include <gtest/gtest.h>
#include <hstd/system/reflection.hpp>
#include <hstd/system/macros.hpp>
#include <hstd/system/Formatter.hpp>
#include <hstd/system/aux_utils.hpp>
#include <hstd/stdlib/reflection_visitor.hpp>


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

    std::string result   = described_class_printer(obj);
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
    };
    struct Second {
        int f;
    };
    struct Third {
        int f;
    };
    SUB_VARIANTS(Kind, Data, data, getKind, First, Second, Third);
    Data data;
};

TEST(Reflection, SubVariants) {
    using T = Type_SubVariants;
    {
        T it{};
        EXPECT_EQ(it.getKind(), T::Kind::First);
        EXPECT_EQ(it.getFirst().f, T::First{}.f);
        EXPECT_THROW(it.getSecond(), std::bad_variant_access);
    }

    {
        T it{T::Second{}};
        EXPECT_EQ(it.getKind(), T::Kind::Second);
        EXPECT_EQ(it.getSecond().f, T::Second{}.f);
        EXPECT_THROW(it.getFirst(), std::bad_variant_access);
    }

    {
        T it{T::Second{.f = 12}};
        EXPECT_EQ(it.getKind(), T::Kind::Second);
        EXPECT_EQ(it.getSecond().f, 12);
        EXPECT_THROW(it.getFirst(), std::bad_variant_access);

        it.data = T::First{.f = 24};

        EXPECT_EQ(it.getKind(), T::Kind::First);
        EXPECT_EQ(it.getFirst().f, 24);
        EXPECT_THROW(it.getSecond(), std::bad_variant_access);
    }
}


struct ReflData {
    int         f1;
    std::string f2;
    char        f3;
    DESC_FIELDS(ReflData, (f1, f2, f3));
};

TEST(ReflectionVisitor, FieldNames) {
    auto items = reflSubItems(ReflData{});
    EXPECT_EQ(items.size(), 3);
    EXPECT_EQ(items.at(0).getFieldName().name, "f1");
    EXPECT_EQ(items.at(1).getFieldName().name, "f2");
    EXPECT_EQ(items.at(2).getFieldName().name, "f3");

    std::vector<std::string> visitNames;
    reflVisitAll(
        ReflData{},
        {},
        overloaded{
            [&](ReflPath const& path, ReflData const& field) {
                visitNames.push_back("ReflData");
            },
            [&](ReflPath const& path, std::string const& field) {
                visitNames.push_back("std::string");
            },
            [&](ReflPath const& path, int const& field) {
                visitNames.push_back("int");
            },
            [&](ReflPath const& path, char const& field) {
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
