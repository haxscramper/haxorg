#pragma once

#include <string>

namespace elk_jni {

class ElkLayoutEngine {
  public:
    ElkLayoutEngine();
    ~ElkLayoutEngine();

    bool        initialize(std::string const& classPathJar);
    void        shutdown();
    std::string performLayout(const std::string& inputJson);
    bool        isInitialized() const;

  private:
    class Impl;
    Impl* pImpl;
};

} // namespace elk_jni
