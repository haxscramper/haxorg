#include <string>

class Calculator {
  public:
    int add(int a, int b) { return a + b; }

    int multiply(int a, int b) { return a * b; }

    std::string createMessage(const std::string& name) {
        return "Hello, " + name + "!";
    }
};


#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(my_module) {
    class_<Calculator>("Calculator")
        .constructor<>()
        .function("add", &Calculator::add)
        .function("multiply", &Calculator::multiply)
        .function("createMessage", &Calculator::createMessage);

    // You can also expose free functions if needed
    emscripten::function("globalAdd", +[](int a, int b) { return a + b; });
}
