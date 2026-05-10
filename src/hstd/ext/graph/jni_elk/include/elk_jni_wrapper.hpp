#pragma once

#include <string>

namespace elk_jni {

class ElkLayoutEngine {
  public:
    ElkLayoutEngine();
    ~ElkLayoutEngine();

    bool        initialize(std::string const& classPathJar);
    void        shutdown();
    std::string performLayout(std::string const& inputJson);
    bool        isInitialized() const;

  private:
    class Impl;
    Impl* pImpl;
};

} // namespace elk_jni
