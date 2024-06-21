void action() {}
void action(char const*) {}

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

#define parameter_macro(par1, par2)                                       \
    action(#par1);                                                        \
    action(#par2);

void parameter_call() {
    parameter_macro(SubtreeTodo, lex);
    parameter_macro(SubtreeUrgency, lex);
    parameter_macro(SubtreeTitle, lex);
    parameter_macro(SubtreeCompletion, lex);
    parameter_macro(SubtreeTags, lex);
}

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
    parameter_call();
}
