void action() {}

#define macro_1() action();

#define layer_macro_2() action();
#define layer_macro_1()                                                   \
    layer_macro_2();                                                      \
    layer_macro_2();                                                      \
    action();
#define layer_macro_0()                                                   \
    layer_macro_1();                                                      \
    layer_macro_1();                                                      \
    action();

void layer_call() { layer_macro_0(); }

void function_1() {
    macro_1();
    macro_1();
}

void function_2() {
    macro_1();
    if (false) { macro_1(); }
}

int main() {
    function_1();
    function_2();
    layer_call();
}
