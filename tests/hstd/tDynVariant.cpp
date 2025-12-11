#include <gtest/gtest.h>
#include <string>
#include <hstd/stdlib/DynVariant.hpp>

struct Shape {
    enum struct Kind
    {
        Circle,
        Rectangle,
        Triangle
    };
    virtual ~Shape()                = default;
    virtual Kind   get_kind() const = 0;
    virtual double area() const     = 0;
};

struct Circle : Shape {
    static const inline Kind staticKind = Kind::Circle;
    double                   radius;
    Circle(double r) : radius{r} {}
    Kind   get_kind() const override { return Kind::Circle; }
    double area() const override {
        return 3.14159265359 * radius * radius;
    }
};

struct Rectangle : Shape {
    static const inline Kind staticKind = Kind::Rectangle;
    double                   width;
    double                   height;
    Rectangle(double w, double h) : width{w}, height{h} {}
    Kind   get_kind() const override { return Kind::Rectangle; }
    double area() const override { return width * height; }
};

struct Triangle : Shape {
    static const inline Kind staticKind = Kind::Triangle;
    double                   base;
    double                   height;
    Triangle(double b, double h) : base{b}, height{h} {}
    Kind   get_kind() const override { return Kind::Triangle; }
    double area() const override { return 0.5 * base * height; }
};

DEFINE_DYN_VARIANT_TAG(
    ShapeTag,
    Shape,
    Shape::Kind,
    ptr->get_kind(),
    Circle,
    Rectangle,
    Triangle);

using ShapeVariant = hstd::dyn_variant<ShapeTag>;

struct DynVariantTest : ::testing::Test {
    ShapeVariant circle;
    ShapeVariant rectangle;
    ShapeVariant triangle;
    ShapeVariant empty;

    void SetUp() override {
        circle    = ShapeVariant::make<Circle>(5.0);
        rectangle = ShapeVariant::make<Rectangle>(3.0, 4.0);
        triangle  = ShapeVariant::make<Triangle>(6.0, 4.0);
    }
};

TEST_F(DynVariantTest, DefaultConstructorCreatesEmptyVariant) {
    EXPECT_FALSE(empty);
    EXPECT_TRUE(empty.valueless_by_exception());
    EXPECT_EQ(empty.get(), nullptr);
}

TEST_F(DynVariantTest, MakeCreatesValidVariant) {
    EXPECT_TRUE(circle);
    EXPECT_FALSE(circle.valueless_by_exception());
    EXPECT_NE(circle.get(), nullptr);
}

TEST_F(DynVariantTest, KindReturnsCorrectEnumValue) {
    EXPECT_EQ(circle.kind(), Shape::Kind::Circle);
    EXPECT_EQ(rectangle.kind(), Shape::Kind::Rectangle);
    EXPECT_EQ(triangle.kind(), Shape::Kind::Triangle);
}

TEST_F(DynVariantTest, IndexReturnsCorrectValue) {
    EXPECT_EQ(circle.index(), 0);
    EXPECT_EQ(rectangle.index(), 1);
    EXPECT_EQ(triangle.index(), 2);
}

TEST_F(DynVariantTest, GetIfReturnsPointerForMatchingType) {
    Circle* c = get_if<Circle>(&circle);
    ASSERT_NE(c, nullptr);
    EXPECT_DOUBLE_EQ(c->radius, 5.0);
}

TEST_F(DynVariantTest, GetIfReturnsNullptrForNonMatchingType) {
    Rectangle* r = get_if<Rectangle>(&circle);
    EXPECT_EQ(r, nullptr);
}

TEST_F(DynVariantTest, GetIfReturnsNullptrForEmptyVariant) {
    Circle* c = get_if<Circle>(&empty);
    EXPECT_EQ(c, nullptr);
}

TEST_F(DynVariantTest, GetIfReturnsNullptrForNullPointer) {
    ShapeVariant* null_ptr = nullptr;
    Circle*       c        = get_if<Circle>(null_ptr);
    EXPECT_EQ(c, nullptr);
}

TEST_F(DynVariantTest, GetReturnsReferenceForMatchingType) {
    Circle& c = get<Circle>(circle);
    EXPECT_DOUBLE_EQ(c.radius, 5.0);
}

TEST_F(DynVariantTest, GetThrowsForNonMatchingType) {
    EXPECT_THROW(get<Rectangle>(circle), std::bad_variant_access);
}

TEST_F(DynVariantTest, GetThrowsForEmptyVariant) {
    EXPECT_THROW(get<Circle>(empty), std::bad_variant_access);
}

TEST_F(DynVariantTest, ConstGetIfWorks) {
    ShapeVariant const& const_circle = circle;
    Circle const*       c            = get_if<Circle>(&const_circle);
    ASSERT_NE(c, nullptr);
    EXPECT_DOUBLE_EQ(c->radius, 5.0);
}

TEST_F(DynVariantTest, ConstGetWorks) {
    ShapeVariant const& const_circle = circle;
    Circle const&       c            = get<Circle>(const_circle);
    EXPECT_DOUBLE_EQ(c.radius, 5.0);
}

TEST_F(DynVariantTest, HoldsAlternativeReturnsTrueForMatchingType) {
    EXPECT_TRUE(holds_alternative<Circle>(circle));
    EXPECT_TRUE(holds_alternative<Rectangle>(rectangle));
    EXPECT_TRUE(holds_alternative<Triangle>(triangle));
}

TEST_F(DynVariantTest, HoldsAlternativeReturnsFalseForNonMatchingType) {
    EXPECT_FALSE(holds_alternative<Rectangle>(circle));
    EXPECT_FALSE(holds_alternative<Triangle>(circle));
    EXPECT_FALSE(holds_alternative<Circle>(rectangle));
}

TEST_F(DynVariantTest, HoldsAlternativeReturnsFalseForEmptyVariant) {
    EXPECT_FALSE(holds_alternative<Circle>(empty));
}

TEST_F(DynVariantTest, VisitCallsCorrectOverload) {
    double area = hstd::dyn_visit(
        []<typename T>(std::shared_ptr<T> const& shape) {
            return shape->area();
        },
        circle);
    EXPECT_DOUBLE_EQ(area, 3.14159265359 * 25.0);
}

TEST_F(DynVariantTest, VisitWorksWithAllTypes) {
    auto get_area = []<typename T>(std::shared_ptr<T> const& shape) {
        return shape->area();
    };

    EXPECT_DOUBLE_EQ(
        hstd::dyn_visit(get_area, circle), 3.14159265359 * 25.0);
    EXPECT_DOUBLE_EQ(hstd::dyn_visit(get_area, rectangle), 12.0);
    EXPECT_DOUBLE_EQ(hstd::dyn_visit(get_area, triangle), 12.0);
}

TEST_F(DynVariantTest, VisitThrowsForEmptyVariant) {
    EXPECT_THROW(
        hstd::dyn_visit(
            []<typename T>(std::shared_ptr<T> const& shape) {}, empty),
        std::bad_variant_access);
}

TEST_F(DynVariantTest, VisitWithConstVariant) {
    ShapeVariant const& const_circle = circle;
    double              area         = hstd::dyn_visit(
        []<typename T>(std::shared_ptr<T> const& shape) {
            return shape->area();
        },
        const_circle);
    EXPECT_DOUBLE_EQ(area, 3.14159265359 * 25.0);
}

TEST_F(DynVariantTest, VisitCanModifyVariant) {
    hstd::dyn_visit(
        []<typename T>(std::shared_ptr<T> const& shape) {
            if constexpr (std::is_same_v<T, Circle>) {
                shape->radius = 10.0;
            }
        },
        circle);

    Circle& c = get<Circle>(circle);
    EXPECT_DOUBLE_EQ(c.radius, 10.0);
}

TEST_F(DynVariantTest, VisitWithTypeSpecificLogic) {
    std::string result = hstd::dyn_visit(
        []<typename T>(std::shared_ptr<T> const& shape) -> std::string {
            if constexpr (std::is_same_v<T, Circle>) {
                return std::format("Circle with radius {}", shape->radius);
            } else if constexpr (std::is_same_v<T, Rectangle>) {
                return std::format(
                    "Rectangle {}x{}", shape->width, shape->height);
            } else {
                return std::format(
                    "Triangle base {} height {}",
                    shape->base,
                    shape->height);
            }
        },
        circle);

    EXPECT_EQ(result, "Circle with radius 5");
}

TEST_F(DynVariantTest, ConstructFromSharedPtr) {
    auto         ptr = std::make_shared<Circle>(7.0);
    ShapeVariant v{ptr};

    EXPECT_TRUE(v);
    EXPECT_EQ(v.kind(), Shape::Kind::Circle);
    Circle& c = get<Circle>(v);
    EXPECT_DOUBLE_EQ(c.radius, 7.0);
}

TEST_F(DynVariantTest, MemberGetIfWorks) {
    Circle* c = circle.get_if<Circle>();
    ASSERT_NE(c, nullptr);
    EXPECT_DOUBLE_EQ(c->radius, 5.0);

    Rectangle* r = circle.get_if<Rectangle>();
    EXPECT_EQ(r, nullptr);
}

TEST_F(DynVariantTest, CopySemantics) {
    ShapeVariant copy = circle;
    EXPECT_TRUE(copy);
    EXPECT_EQ(copy.kind(), Shape::Kind::Circle);
    EXPECT_EQ(copy.get(), circle.get());
}

TEST_F(DynVariantTest, MoveSemantics) {
    ShapeVariant moved = std::move(circle);
    EXPECT_TRUE(moved);
    EXPECT_EQ(moved.kind(), Shape::Kind::Circle);
}

TEST_F(DynVariantTest, Assignment) {
    ShapeVariant v;
    EXPECT_FALSE(v);

    v = rectangle;
    EXPECT_TRUE(v);
    EXPECT_EQ(v.kind(), Shape::Kind::Rectangle);
}

TEST_F(DynVariantTest, BaseClassPointerAccess) {
    Shape* base = circle.get();
    ASSERT_NE(base, nullptr);
    EXPECT_DOUBLE_EQ(base->area(), 3.14159265359 * 25.0);
}

TEST_F(DynVariantTest, PolymorphicBehaviorThroughBasePointer) {
    std::vector<ShapeVariant> shapes     = {circle, rectangle, triangle};
    double                    total_area = 0.0;

    for (auto const& shape : shapes) { total_area += shape.get()->area(); }

    double expected = 3.14159265359 * 25.0 + 12.0 + 12.0;
    EXPECT_DOUBLE_EQ(total_area, expected);
}


namespace nested_in_parent_test {

struct Parent {
    struct Shape {
        DEFINE_DYN_VARIANT_BASE_TYPE_BODY(
            Shape,
            Kind,
            getKind,
            Circle,
            Rectangle,
            Triangle);
    };

    struct Circle : Shape {
        DEFINE_DYN_VARIANT_DERIVED_TYPE_BODY(Circle, Kind, getKind);
        double radius = 0;
    };

    struct Rectangle : Shape {
        DEFINE_DYN_VARIANT_DERIVED_TYPE_BODY(Rectangle, Kind, getKind);
        double width  = 0;
        double height = 0;
    };

    struct Triangle : Shape {
        DEFINE_DYN_VARIANT_DERIVED_TYPE_BODY(Triangle, Kind, getKind);
        double base   = 0;
        double height = 0;
    };

    DEFINE_DYN_VARIANT_TAG(
        ShapeTag,
        Shape,
        Shape::Kind,
        ptr->getKind(),
        Circle,
        Rectangle,
        Triangle);

    using ShapeVariant = hstd::dyn_variant<ShapeTag>;

    ShapeVariant shape;
    std::string  name;
};

} // namespace nested_in_parent_test

TEST(DynVariantNestedInParent, CreateCircle) {
    using namespace nested_in_parent_test;

    Parent p{
        .shape = Parent::ShapeVariant::make<Parent::Circle>(),
        .name  = "CircleParent"};

    hstd::get<Parent::Circle>(p.shape).radius = 5.0;

    EXPECT_TRUE(hstd::holds_alternative<Parent::Circle>(p.shape));
    EXPECT_EQ(hstd::get<Parent::Circle>(p.shape).radius, 5.0);
    EXPECT_EQ(p.name, "CircleParent");
}

TEST(DynVariantNestedInParent, CreateRectangle) {
    using namespace nested_in_parent_test;

    Parent p{
        .shape = Parent::ShapeVariant::make<Parent::Rectangle>(),
        .name  = "RectParent"};

    hstd::get<Parent::Rectangle>(p.shape).width  = 4.0;
    hstd::get<Parent::Rectangle>(p.shape).height = 3.0;

    EXPECT_TRUE(hstd::holds_alternative<Parent::Rectangle>(p.shape));
    EXPECT_EQ(hstd::get<Parent::Rectangle>(p.shape).width, 4.0);
    EXPECT_EQ(hstd::get<Parent::Rectangle>(p.shape).height, 3.0);
}

TEST(DynVariantNestedInParent, VisitNestedTypes) {
    using namespace nested_in_parent_test;

    Parent p{
        .shape = Parent::ShapeVariant::make<Parent::Triangle>(),
        .name  = "TriParent"};

    hstd::get<Parent::Triangle>(p.shape).base   = 6.0;
    hstd::get<Parent::Triangle>(p.shape).height = 4.0;

    double area = hstd::dyn_visit(
        []<typename T>(std::shared_ptr<T> const& s) -> double {
            if constexpr (std::is_same_v<T, Parent::Circle>) {
                return 3.14159 * s->radius * s->radius;
            } else if constexpr (std::is_same_v<T, Parent::Rectangle>) {
                return s->width * s->height;
            } else {
                return 0.5 * s->base * s->height;
            }
        },
        p.shape);

    EXPECT_DOUBLE_EQ(area, 12.0);
}

TEST(DynVariantNestedInParent, VectorOfParents) {
    using namespace nested_in_parent_test;

    std::vector<Parent> parents;

    Parent p1{
        .shape = Parent::ShapeVariant::make<Parent::Circle>(),
        .name  = "P1"};
    hstd::get<Parent::Circle>(p1.shape).radius = 2.0;
    parents.push_back(p1);

    Parent p2{
        .shape = Parent::ShapeVariant::make<Parent::Rectangle>(),
        .name  = "P2"};
    hstd::get<Parent::Rectangle>(p2.shape).width  = 3.0;
    hstd::get<Parent::Rectangle>(p2.shape).height = 4.0;
    parents.push_back(p2);

    Parent p3{
        .shape = Parent::ShapeVariant::make<Parent::Triangle>(),
        .name  = "P3"};
    hstd::get<Parent::Triangle>(p3.shape).base   = 5.0;
    hstd::get<Parent::Triangle>(p3.shape).height = 6.0;
    parents.push_back(p3);

    std::vector<std::string> descriptions;
    for (auto const& parent : parents) {
        std::string desc = hstd::dyn_visit(
            [&parent]<typename T>(
                std::shared_ptr<T> const& s) -> std::string {
                if constexpr (std::is_same_v<T, Parent::Circle>) {
                    return std::format(
                        "{}: Circle(r={})", parent.name, s->radius);
                } else if constexpr (std::
                                         is_same_v<T, Parent::Rectangle>) {
                    return std::format(
                        "{}: Rect({}x{})",
                        parent.name,
                        s->width,
                        s->height);
                } else {
                    return std::format(
                        "{}: Tri(b={},h={})",
                        parent.name,
                        s->base,
                        s->height);
                }
            },
            parent.shape);
        descriptions.push_back(desc);
    }

    EXPECT_EQ(descriptions.at(0), "P1: Circle(r=2)");
    EXPECT_EQ(descriptions.at(1), "P2: Rect(3x4)");
    EXPECT_EQ(descriptions.at(2), "P3: Tri(b=5,h=6)");
}


namespace many_types_test {

struct Node {
    DEFINE_DYN_VARIANT_BASE_TYPE_BODY(
        Node,
        Kind,
        getKind,
        Type00,
        Type01,
        Type02,
        Type03,
        Type04,
        Type05,
        Type06,
        Type07,
        Type08,
        Type09,
        Type10,
        Type11,
        Type12,
        Type13,
        Type14,
        Type15,
        Type16,
        Type17,
        Type18,
        Type19,
        Type20,
        Type21,
        Type22,
        Type23,
        Type24,
        Type25,
        Type26,
        Type27,
        Type28,
        Type29,
        Type30,
        Type31,
        Type32,
        Type33,
        Type34,
        Type35,
        Type36,
        Type37,
        Type38,
        Type39,
        Type40,
        Type41,
        Type42,
        Type43,
        Type44,
        Type45,
        Type46,
        Type47,
        Type48,
        Type49,
        Type50,
        Type51);
};

#define DEFINE_NODE_TYPE(Name)                                            \
    struct Name : Node {                                                  \
        DEFINE_DYN_VARIANT_DERIVED_TYPE_BODY(Name, Kind, getKind);        \
        int value;                                                        \
    };

DEFINE_NODE_TYPE(Type00);
DEFINE_NODE_TYPE(Type01);
DEFINE_NODE_TYPE(Type02);
DEFINE_NODE_TYPE(Type03);
DEFINE_NODE_TYPE(Type04);
DEFINE_NODE_TYPE(Type05);
DEFINE_NODE_TYPE(Type06);
DEFINE_NODE_TYPE(Type07);
DEFINE_NODE_TYPE(Type08);
DEFINE_NODE_TYPE(Type09);
DEFINE_NODE_TYPE(Type10);
DEFINE_NODE_TYPE(Type11);
DEFINE_NODE_TYPE(Type12);
DEFINE_NODE_TYPE(Type13);
DEFINE_NODE_TYPE(Type14);
DEFINE_NODE_TYPE(Type15);
DEFINE_NODE_TYPE(Type16);
DEFINE_NODE_TYPE(Type17);
DEFINE_NODE_TYPE(Type18);
DEFINE_NODE_TYPE(Type19);
DEFINE_NODE_TYPE(Type20);
DEFINE_NODE_TYPE(Type21);
DEFINE_NODE_TYPE(Type22);
DEFINE_NODE_TYPE(Type23);
DEFINE_NODE_TYPE(Type24);
DEFINE_NODE_TYPE(Type25);
DEFINE_NODE_TYPE(Type26);
DEFINE_NODE_TYPE(Type27);
DEFINE_NODE_TYPE(Type28);
DEFINE_NODE_TYPE(Type29);
DEFINE_NODE_TYPE(Type30);
DEFINE_NODE_TYPE(Type31);
DEFINE_NODE_TYPE(Type32);
DEFINE_NODE_TYPE(Type33);
DEFINE_NODE_TYPE(Type34);
DEFINE_NODE_TYPE(Type35);
DEFINE_NODE_TYPE(Type36);
DEFINE_NODE_TYPE(Type37);
DEFINE_NODE_TYPE(Type38);
DEFINE_NODE_TYPE(Type39);
DEFINE_NODE_TYPE(Type40);
DEFINE_NODE_TYPE(Type41);
DEFINE_NODE_TYPE(Type42);
DEFINE_NODE_TYPE(Type43);
DEFINE_NODE_TYPE(Type44);
DEFINE_NODE_TYPE(Type45);
DEFINE_NODE_TYPE(Type46);
DEFINE_NODE_TYPE(Type47);
DEFINE_NODE_TYPE(Type48);
DEFINE_NODE_TYPE(Type49);
DEFINE_NODE_TYPE(Type50);
DEFINE_NODE_TYPE(Type51);

#undef DEFINE_NODE_TYPE

DEFINE_DYN_VARIANT_TAG(
    NodeTag,
    Node,
    Node::Kind,
    ptr->getKind(),
    Type00,
    Type01,
    Type02,
    Type03,
    Type04,
    Type05,
    Type06,
    Type07,
    Type08,
    Type09,
    Type10,
    Type11,
    Type12,
    Type13,
    Type14,
    Type15,
    Type16,
    Type17,
    Type18,
    Type19,
    Type20,
    Type21,
    Type22,
    Type23,
    Type24,
    Type25,
    Type26,
    Type27,
    Type28,
    Type29,
    Type30,
    Type31,
    Type32,
    Type33,
    Type34,
    Type35,
    Type36,
    Type37,
    Type38,
    Type39,
    Type40,
    Type41,
    Type42,
    Type43,
    Type44,
    Type45,
    Type46,
    Type47,
    Type48,
    Type49,
    Type50,
    Type51);

using NodeVariant = hstd::dyn_variant<NodeTag>;

} // namespace many_types_test

TEST(DynVariantManyTypes, InstantiateAndVisitFirst) {
    using namespace many_types_test;

    NodeVariant v              = NodeVariant::make<Type00>();
    hstd::get<Type00>(v).value = 100;

    int result = hstd::dyn_visit(
        []<typename T>(std::shared_ptr<T> const& n) -> int {
            return n->value;
        },
        v);

    EXPECT_EQ(result, 100);
    EXPECT_TRUE(hstd::holds_alternative<Type00>(v));
}

TEST(DynVariantManyTypes, InstantiateAndVisitLast) {
    using namespace many_types_test;

    NodeVariant v              = NodeVariant::make<Type39>();
    hstd::get<Type39>(v).value = 3900;

    int result = hstd::dyn_visit(
        []<typename T>(std::shared_ptr<T> const& n) -> int {
            return n->value;
        },
        v);

    EXPECT_EQ(result, 3900);
    EXPECT_TRUE(hstd::holds_alternative<Type39>(v));
}

TEST(DynVariantManyTypes, InstantiateAndVisitMiddle) {
    using namespace many_types_test;

    NodeVariant v              = NodeVariant::make<Type20>();
    hstd::get<Type20>(v).value = 2000;

    int result = hstd::dyn_visit(
        []<typename T>(std::shared_ptr<T> const& n) -> int {
            return n->value;
        },
        v);

    EXPECT_EQ(result, 2000);
    EXPECT_TRUE(hstd::holds_alternative<Type20>(v));
}

TEST(DynVariantManyTypes, VisitWithTypeSpecificBehavior) {
    using namespace many_types_test;

    NodeVariant v              = NodeVariant::make<Type15>();
    hstd::get<Type15>(v).value = 15;

    std::string result = hstd::dyn_visit(
        []<typename T>(std::shared_ptr<T> const& n) -> std::string {
            if constexpr (std::is_same_v<T, Type15>) {
                return std::format("Type15: {}", n->value);
            } else {
                return std::format("Other: {}", n->value);
            }
        },
        v);

    EXPECT_EQ(result, "Type15: 15");
}

TEST(DynVariantManyTypes, MultipleVariantsInVector) {
    using namespace many_types_test;

    std::vector<NodeVariant> nodes;

    for (int i = 0; i < 40; ++i) {
        NodeVariant v;
        switch (i % 4) {
            case 0:
                v                          = NodeVariant::make<Type00>();
                hstd::get<Type00>(v).value = i;
                break;
            case 1:
                v                          = NodeVariant::make<Type10>();
                hstd::get<Type10>(v).value = i;
                break;
            case 2:
                v                          = NodeVariant::make<Type20>();
                hstd::get<Type20>(v).value = i;
                break;
            case 3:
                v                          = NodeVariant::make<Type30>();
                hstd::get<Type30>(v).value = i;
                break;
        }
        nodes.push_back(v);
    }

    int sum = 0;
    for (auto const& n : nodes) {
        sum += hstd::dyn_visit(
            []<typename T>(std::shared_ptr<T> const& node) -> int {
                return node->value;
            },
            n);
    }

    EXPECT_EQ(sum, (39 * 40) / 2);
}
