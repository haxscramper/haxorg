void action() {}

struct NonTemplateClass {
    void non_template_1(int arg) {
        if (arg == 2) {
            action();
        } else {
            action();
        }
    }
    void non_template_2() {
        action();
        action();
    }

    template <typename M>
    void template_1() {
        action();
        action();
    }
};

template <typename T>
struct TemplateClass {
    void non_template_1(int arg) {
        if (arg == 2) {
            action();
        } else {
            action();
        }
    }

    void non_template_2() {
        action();
        action();
    }

    template <typename M>
    void template_1() {
        action();
        action();
    }

    void never_called_but_references() {
        action();
        action();
    }

    void never_called_not_referenced() {
        action();
        action();
    }
};

template <typename T>
void called_many_instantiations() {
    action();
    action();
}

int main(int argc, char** argv) {
    if (argc == 2) {
        NonTemplateClass{}.non_template_1(argc);
        TemplateClass<float>{}.non_template_1(argc);
    }

    if (argc == 3) {
        NonTemplateClass{}.non_template_1(argc);
        TemplateClass<int>{}.non_template_1(argc);
    }

    if (argc == 4) { NonTemplateClass{}.non_template_2(); }
    if (argc == 5) { NonTemplateClass{}.template_1<int>(); }
    if (argc == 6) { TemplateClass<int>{}.non_template_2(); }
    if (argc == 7) { TemplateClass<int>{}.template_1<int>(); }
    if (false) { TemplateClass<int>{}.never_called_but_references(); }

    if (argc == 10) {
        called_many_instantiations<float>();
        called_many_instantiations<int>();
        called_many_instantiations<double>();
        called_many_instantiations<char>();
    }
}
