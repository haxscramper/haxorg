void action() {}

struct NonTemplateClass {
    void non_template_methods(int arg) {
        if (arg == 2) {
            action();
        } else {
            action();
        }
    }
    void non_template_never_called() {
        action();
        action();
    }

    template <typename M>
    void template_never_called() {
        action();
        action();
    }
};

template <typename T>
struct TemplateClass {
    void non_template_methods(int arg) {
        if (arg == 2) {
            action();
        } else {
            action();
        }
    }

    void non_template_never_called() {
        action();
        action();
    }

    template <typename M>
    void template_never_called() {
        action();
        action();
    }
};

int main(int argc, char** argv) {
    if (argc == 2) {
        NonTemplateClass{}.non_template_methods(argc);
        TemplateClass<float>{}.non_template_methods(argc);
    } else {
        NonTemplateClass{}.non_template_methods(argc);
        TemplateClass<int>{}.non_template_methods(argc);
    }
}
