#pragma once

#include <src/model/HistoryManager.hpp>
#include <src/model/nodes/DiagramTreeNode.hpp>

namespace test {
struct ScopeV12 {
    org::imm::ImmAstContext::Ptr         context;
    HistoryManager                       manager;
    hstd::SPtr<DiagramTreeNode::Context> tree_context;
    ScopeV12()
        : context{org::imm::ImmAstContext::init_start_context()}
        , manager{context}
        , tree_context{DiagramTreeNode::Context::shared()} //
    {}

    org::imm::ImmAdapter getRootV1() const { return manager.getRoot(0); }
    org::imm::ImmAdapter getRootV2() const { return manager.getRoot(1); }
};

struct ScopeDiagramTree {
    org::imm::ImmAstContext::Ptr         context;
    hstd::SPtr<DiagramTreeNode::Context> tree_context;

    ScopeDiagramTree()
        : context{org::imm::ImmAstContext::init_start_context()}
        , tree_context{DiagramTreeNode::Context::shared()} //
    {}
};

} // namespace test
