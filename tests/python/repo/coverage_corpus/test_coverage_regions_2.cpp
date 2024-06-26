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

void action() {}
void coverage_branches(int arg) {
    if (arg > 0) {
        int asgn = arg + 1;
        if (arg > 10) {
            asgn += arg;
            if (arg > 20) {
                asgn += arg;
                action();
            } else {
                asgn += arg;
                action();
            }
        } else {
            asgn += arg;
            if (arg > 5) {
                action();
            } else {
                action();
            }
        }
    } else if (arg < 0) {
        if (arg < -10) {
            if (arg < -20) {
                action();
            } else {
                action();
            }
        } else {
            if (arg < -5) {
                action();
            } else {
                action();
            }
        }
    } else {
        action();
    }

    if (0 < arg     //
        || 10 < arg //
        || 5 < arg  //
        || arg < 0  //
    ) {
        action();
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
        case 1: {
            coverage_branches(25); // Cover Branch 1.1.1 (arg > 20)
            coverage_branches(15); // Cover Branch 1.1.2 (10 < arg <= 20)
            coverage_branches(7);  // Cover Branch 1.2.1 (5 < arg <= 10)
            coverage_branches(3);  // Cover Branch 1.2.2 (0 < arg <= 5);
            break;
        }
        case 2: {
            coverage_branches(-25); // Cover Branch 2.1.1 (arg < -20)
            coverage_branches(-15); // Cover Branch 2.1.2 (-20 <= arg <
                                    // -10)
            coverage_branches(-7);  // Cover Branch 2.2.1 (-10 < arg <= -5)
            coverage_branches(-3);  // Cover Branch 2.2.2 (-5 < arg < 0)
            break;
        }
        case 3: {
            coverage_branches(0); // Cover Branch 3 (arg == 0)
            break;
        }
    }

    if (false) {
        // Not executed
        function_2();
    }
}
