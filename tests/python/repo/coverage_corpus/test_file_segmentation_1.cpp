void action() {}
void coverage_branches(int arg) {
    if (arg > 0) {
        if (arg > 10) {
            if (arg > 20) {
                action();
            } else {
                action();
            }
        } else {
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

    if (arg == 0 || arg == 1 || arg == 2
        || ((arg <= 5 || arg <= 5) && arg < 10)) {
        action();
    }
}


int main() {
    coverage_branches(25);  // Cover Branch 1.1.1 (arg > 20)
    coverage_branches(15);  // Cover Branch 1.1.2 (10 < arg <= 20)
    coverage_branches(7);   // Cover Branch 1.2.1 (5 < arg <= 10)
    coverage_branches(3);   // Cover Branch 1.2.2 (0 < arg <= 5)
    coverage_branches(-25); // Cover Branch 2.1.1 (arg < -20)
    coverage_branches(-15); // Cover Branch 2.1.2 (-20 <= arg < -10)
    coverage_branches(-7);  // Cover Branch 2.2.1 (-10 < arg <= -5)
    coverage_branches(-3);  // Cover Branch 2.2.2 (-5 < arg < 0)
    coverage_branches(0);   // Cover Branch 3 (arg == 0)
    return 0;
}
