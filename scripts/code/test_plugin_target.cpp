

struct Other {
    struct Nested {};
};
namespace A::B::C {
struct Other {};
} // namespace A::B::C

struct [[refl]] annotated {
    void           cull_me() {}
    int            field;
    Other          other;
    A::B::C::Other oth2;
    Other::Nested  oth3;
};

int main() {
    annotated it;
    it.cull_me();
    return 0;
}
