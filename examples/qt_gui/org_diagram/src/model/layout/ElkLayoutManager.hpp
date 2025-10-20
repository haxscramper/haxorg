#pragma once
#include "elk_jni_wrapper.hpp"
#include <memory>
#include <hstd/stdlib/Exception.hpp>

class ElkLayoutManager {
  private:
    std::unique_ptr<elk_jni::ElkLayoutEngine> elkEngine;
    std::string                               classPath;

  public:
    ElkLayoutManager(std::string const& classPath)
        : elkEngine(std::make_unique<elk_jni::ElkLayoutEngine>())
        , classPath{classPath} {
        LOGIC_ASSERTION_CHECK(
            elkEngine->initialize(classPath),
            "Failed to initialize ELK layout engine");
    }

    ~ElkLayoutManager() {
        if (elkEngine) { elkEngine->shutdown(); }
    }

    std::string layoutDiagram(const std::string& graphJson) {
        LOGIC_ASSERTION_CHECK(
            elkEngine->isInitialized(),
            "Initialization failed earlier, cannot execute layout");

        return elkEngine->performLayout(graphJson);
    }
};
