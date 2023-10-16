#include "token.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

int main() {
  std::ifstream inFile(
      "/home/maxim_artemov/defaultdirs/notes/personal/indexed/notes.org");

  if (!inFile.is_open()) {
    std::cerr << "Failed to open input.txt\n";
    return 1;
  }

  std::stringstream buffer;
  buffer << inFile.rdbuf();
  std::string content = buffer.str();

  std::vector<Token> tokens = tokenize(content.data(), content.size());
  std::ofstream out{"/tmp/token.txt"};
  for (const Token &token : tokens) {
    // out << "Token value: '" << token.value
    //     << "', kind: " << static_cast<int>(token.kind) << "\n";
  }
  std::cout << "Found " << tokens.size() << " tokens\n";

  return 0;
}
