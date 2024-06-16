void action() {}

#define macro_1() action();


void function_1() { macro_1(); }
void function_2() { macro_1(); }

int main() {
    function_1();
    function_2();
}
