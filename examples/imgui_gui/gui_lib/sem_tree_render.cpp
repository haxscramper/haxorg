#include "sem_tree_render.hpp"

#include <imgui.h>
#include <haxorg/exporters/ExporterBase.hpp>
#include <cstdlib>
#include <haxorg/exporters/Exporter.cpp>

#pragma clang diagnostic ignored "-Wc99-extensions"


ImVec4 theme[] = {
    [(int)ColorName::Black]        = ImVec4(0.157f, 0.165f, 0.180f, 1.00f),
    [(int)ColorName::Red]          = ImVec4(0.647f, 0.259f, 0.259f, 1.00f),
    [(int)ColorName::Green]        = ImVec4(0.549f, 0.580f, 0.251f, 1.00f),
    [(int)ColorName::Yellow]       = ImVec4(0.871f, 0.576f, 0.373f, 1.00f),
    [(int)ColorName::Blue]         = ImVec4(0.373f, 0.506f, 0.616f, 1.00f),
    [(int)ColorName::Magenta]      = ImVec4(0.522f, 0.404f, 0.561f, 1.00f),
    [(int)ColorName::Cyan]         = ImVec4(0.369f, 0.553f, 0.529f, 1.00f),
    [(int)ColorName::White]        = ImVec4(0.439f, 0.470f, 0.502f, 1.00f),
    [(int)ColorName::BrightBlack]  = ImVec4(0.216f, 0.231f, 0.255f, 1.00f),
    [(int)ColorName::BrightRed]    = ImVec4(0.800f, 0.400f, 0.400f, 1.00f),
    [(int)ColorName::BrightGreen]  = ImVec4(0.710f, 0.741f, 0.408f, 1.00f),
    [(int)ColorName::BrightYellow] = ImVec4(0.941f, 0.776f, 0.455f, 1.00f),
    [(int)ColorName::BrightBlue]   = ImVec4(0.506f, 0.635f, 0.745f, 1.00f),
    [(int)ColorName::BrightMagenta] = ImVec4(
        0.698f,
        0.580f,
        0.733f,
        1.00f),
    [(int)ColorName::BrightCyan]  = ImVec4(0.541f, 0.745f, 0.718f, 1.00f),
    [(int)ColorName::BrightWhite] = ImVec4(0.773f, 0.784f, 0.776f, 1.00f),
    [(int)ColorName::Background]  = ImVec4(0.114f, 0.122f, 0.129f, 1.00f),
    [(int)ColorName::Foreground]  = ImVec4(0.773f, 0.784f, 0.776f, 1.00f)};


ImVec4 const& color(ColorName const& name) { return theme[(int)name]; }

struct ExporterVisual : public Exporter<ExporterVisual, int> {
    using Base = Exporter<ExporterVisual, int>;
    using VR   = VisitReport;
    using VK   = VisitReport::Kind;

#define __ExporterBase Base
    EXPORTER_USING()
#undef __ExporterBase


    VisualExporterConfig& config;

    SemSet LeafKinds{
        OrgSemKind::Newline,
        OrgSemKind::Word,
        OrgSemKind::RawText,
        OrgSemKind::Space,
        OrgSemKind::Punctuation,
    };

    bool ImOrgTree(std::string const& name) {
        ImGui::SetNextItemOpen(true, ImGuiCond_Once);
        return ImGui::TreeNode(name.c_str());
    }

    void FieldEqLine() {
        ImGui::SameLine();
        ImGui::Text("=");
        ImGui::SameLine();
    }

    void FieldName(
        char const* name,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION()) {
        if (false) {
            ImGui::Text("%d", line);
            ImGui::SameLine();
        }
        ImGui::TextColored(color(ColorName::Green), "%s", name);
    }


    void visitField(
        int&                                 i,
        const char*                          name,
        CVec<org::sem::SemId<org::sem::Org>> org) {
        auto __scope = trace_scope(trace(VK::VisitField).with_field(name));
        for (const auto& [idx, sub] : enumerate(org)) {
            if (LeafKinds.contains(sub->getKind())) {
                ImGui::Text("%s", fmt("[{}]", idx).c_str());
                ImGui::SameLine();
                visit(i, sub);
            } else if (ImOrgTree(fmt("[{}] {}", idx, sub->getKind()))) {
                visit(i, sub);
                ImGui::TreePop();
            }
        }
    }

    void visitSpace(int& j, org::sem::SemId<org::sem::Space> s) {
        if (config.showSpace) {
            ImGui::Text("Space");
            ImGui::SameLine();
            ImGui::TextColored(
                color(ColorName::Yellow),
                "%s",
                escape_literal(s->text).c_str());
        }
    }

#define _visit_leaf(__Kind)                                               \
    void visit##__Kind(int& j, org::sem::SemId<org::sem::__Kind> s) {     \
        ImGui::Text(#__Kind);                                             \
        ImGui::SameLine();                                                \
        ImGui::TextColored(                                               \
            color(ColorName::Yellow),                                     \
            "%s",                                                         \
            escape_literal(s->text).c_str());                             \
    }

    _visit_leaf(Word);
    _visit_leaf(Newline);
    _visit_leaf(Punctuation);


    template <typename T>
    void visitField(int& j, const char* name, Opt<T> const& value) {
        auto __scope = trace_scope(trace(VK::VisitField).with_field(name));
        if (value) {
            visitField(j, name, *value);
        } else if (config.showNullopt) {
            FieldName(name);
            FieldEqLine();
            ImGui::TextColored(color(ColorName::Cyan), "nullopt");
        }
    }

    void visitField(int&, const char* name, bool const& value) {
        auto __scope = trace_scope(trace(VK::VisitField).with_field(name));
        FieldName(name);
        FieldEqLine();
        ImGui::TextColored(
            color(value ? ColorName::Green : ColorName::Red),
            "%s",
            value ? "true" : "false");
    }

    void visitField(int&, const char* name, int const& value) {
        auto __scope = trace_scope(trace(VK::VisitField).with_field(name));
        FieldName(name);
        FieldEqLine();
        ImGui::TextColored(color(ColorName::Cyan), "%d", value);
    }

    void visitField(int&, const char* name, Str const& value) {
        auto __scope = trace_scope(trace(VK::VisitField).with_field(name));
        FieldName(name);
        FieldEqLine();
        ImGui::TextColored(
            color(ColorName::Yellow), "%s", escape_literal(value).c_str());
    }

    template <typename T>
    void visitField(
        int&                   j,
        const char*            name,
        CR<org::sem::SemId<T>> field) {
        auto __scope = trace_scope(trace(VK::VisitField).with_field(name));
        if (ImOrgTree(name)) {
            visit(j, field);
            ImGui::TreePop();
        }
    }

    template <typename T>
    void visitField(int&, const char* name, CR<T> field) {
        auto __scope = trace_scope(trace(VK::VisitField).with_field(name));
        ImGui::TextColored(
            color(ColorName::Red),
            "%s %s",
            name,
            value_metadata<T>::typeName().c_str());
    }

    template <typename T>
    void visit(int& arg, org::sem::SemId<T> const& org) {
        auto __scope = trace_scope(
            trace(VK::VisitGeneric).with_node(org.asOrg()));
        if (ImOrgTree(fmt1(org->getKind()).c_str())) {
            visit(arg, org.asOrg());
            ImGui::TreePop();
        }
    }
};

template class org::algo::Exporter<ExporterVisual, int>;

void render_sem_tree(
    org::sem::SemId<org::sem::Org> tree,
    VisualExporterConfig&          config) {
    ExporterVisual exp{.config = config};
    if (config.doTrace) {
        exp.setTraceFile("/tmp/ExportWalker.txt");
        config.doTrace = false;
    }
    exp.evalTop(tree);
}
