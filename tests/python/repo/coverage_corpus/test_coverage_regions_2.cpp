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
    int assign       = 12;
    int other_assign = assign * 2;
    if (argc == 1) {
        function_3("text argument");
    } else {
        function_3(argc);
    }

    switch (argc) {
        case 0: function_3("0"); break;
        case 1: function_3("1"); break;
        case 2: function_3("2"); break;
        case 3: function_3("3"); break;
    }

    if (false) {
        // Not executed
        function_2();
    }
}
