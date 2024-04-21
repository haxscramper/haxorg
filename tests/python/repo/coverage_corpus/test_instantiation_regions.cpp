template <typename T>
void template_func() {}


int main(int argc, char** argv) {
    template_func<int>();
    template_func<float>();
    if (argc == 2) {
        template_func<int>();
    } else {
        template_func<float>();
    }
}
