struct PlainToplevelStruct {
    struct PlainNestedStruct {};

    int direct_field;
    struct NestedStructField {
        int field;
    } nested_struct_field;
    struct {
        int field;
    } anon_struct_field;
    struct {
        int embedded_struct_field;
    };

    union NestedUnionField {
        int field;
    } nested_union_field;
    union {
        int field;
    } anon_union_field;
    union {
        int embedded_union_field;
    };
};

namespace NameSpace {
struct PlainNamespaceStruct {
    struct PlainNamespaceNestedStruct {};
};
} // namespace NameSpace


enum PlainToplevelEnum
{
    top_EnumField_1,
    top_EnumField_2
};

enum class ClassToplevelEnum
{
    class_EnumField_1,
    class_EnumField_2,
};
