void function_1() {}
void function_2() {}

void function_3(char const* with_ptr_argument) {}

void function_3(int with_int_argument) {
    if (with_int_argument == 2) {
        function_1();
    } else {
        function_2();
    }
}

int main(int argc, char** argv) {
    if (argc == 1) {
        function_3("text argument");
    } else {
        function_3(argc);
    }
}
