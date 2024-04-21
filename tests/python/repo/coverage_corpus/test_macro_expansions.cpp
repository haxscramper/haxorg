#define multi_statement1()                                                \
    int a = 2 + 3;                                                        \
    int b = 4 + 6;

#define multi_statement2()                                                \
    int c = 2 + 3;                                                        \
    int d = 4 + 6;

void func() {
    multi_statement1();
    multi_statement2();
}

int main() {
    func(); //
}
