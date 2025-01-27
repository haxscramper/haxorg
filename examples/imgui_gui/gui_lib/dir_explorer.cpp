#include "dir_explorer.hpp"
#include "gui_lib/im_org_ui_common.hpp"
#include <haxorg/sem/SemBaseApi.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <haxorg/sem/ImmOrg.hpp>
#include <gui_lib/org_logger.hpp>

struct DirContext {
    org::ImmAstContext::Ptr ctx;
    fs::path                root;
};


struct ContentNode {
    Vec<ContentNode> nested;
    org::ImmAdapter  a;

    struct Subtree {
        Str title;
        DESC_FIELDS(Subtree, (title));
    };

    struct Document {
        DESC_FIELDS(Document, ());
    };

    SUB_VARIANTS(Kind, Data, data, getKind, Subtree, Document);
    Data data;

    void render(DirContext& ctx) {
        if (isDocument()) {
            for (auto& sub : nested) { sub.render(ctx); }
        } else if (isSubtree()) {
            if (ImGui::TreeNodeEx(
                    c_fmt("content_{}", a.id),
                    ImGuiTreeNodeFlags_DefaultOpen,
                    "%s",
                    getSubtree().title.c_str())) {
                for (auto& sub : nested) { sub.render(ctx); }
                ImGui::TreePop();
            }
        }
    }

    static ContentNode from_node(
        DirContext&            ctx,
        org::ImmAdapter const& a) {
        ContentNode res;
        res.a = a;
        if (auto tree = a.asOpt<org::ImmSubtree>()) {
            res.data = Subtree{
                .title = tree->getCleanTitle(),
            };

            for (auto const& sub : tree->subAs<org::ImmSubtree>()) {
                res.nested.push_back(ContentNode::from_node(ctx, sub));
            }
        } else if (auto doc = a.asOpt<org::ImmDocument>()) {
            res.data = Document{};
            for (auto const& sub : doc->subAs<org::ImmSubtree>()) {
                res.nested.push_back(ContentNode::from_node(ctx, sub));
            }
        }


        return res;
    }
};

struct FileNode {
    org::ImmAdapter root;
    Opt<Str>        title;
    ContentNode     document;
    Str             relative;

    void render(DirContext& ctx) {
        if (ImGui::TreeNodeEx(
                c_fmt("file_{}", relative),
                ImGuiTreeNodeFlags_DefaultOpen,
                "%s",
                relative.c_str())) {
            document.render(ctx);
            ImGui::TreePop();
        }
    }

    static FileNode from_file(DirContext& ctx, fs::path const& file) {
        Str relative = fs::relative(file, ctx.root).native();
        OLOG_INFO("load", "Loading file ", relative);
        OLOG_DEPTH_SCOPE_ANON();
        auto     node = sem::parseString(readFile(file));
        auto     root = ctx.ctx->addRoot(node);
        FileNode res{root.getRootAdapter()};
        res.document = ContentNode::from_node(ctx, res.root);
        res.relative = relative;

        return res;
    }
};

struct DirNode {
    Str              relative;
    Opt<ContentNode> readme;
    Vec<FileNode>    files;
    Vec<DirNode>     nested;

    bool empty() const {
        return !readme.has_value() && files.empty() && nested.empty();
    }

    void render(DirContext& ctx) {
        if (ImGui::TreeNodeEx(
                c_fmt("dir_{}", relative),
                ImGuiTreeNodeFlags_DefaultOpen,
                "%s",
                relative.c_str())) {
            for (auto& file : files) { file.render(ctx); }
            for (auto& dir : nested) { dir.render(ctx); }
            ImGui::TreePop();
        }
    }

    static DirNode from_dir(DirContext& ctx, fs::path const& dir) {
        DirNode res;
        res.relative = fs::relative(dir, ctx.root).native();
        LOGIC_ASSERTION_CHECK(
            !res.relative.empty(),
            "Relative directory is empty, root {} is not a parent of {}",
            escape_literal(ctx.root.native()),
            escape_literal(dir.native()));

        if (res.relative.starts_with(".") && 2 < res.relative.size()) {
            return res;
        }

        OLOG_INFO(
            "load", "Loading directory ", escape_literal(res.relative));
        OLOG_DEPTH_SCOPE_ANON();

        for (const auto& entry : fs::directory_iterator(dir)) {
            if (entry.is_directory()) {
                auto sub = DirNode::from_dir(ctx, entry);
                if (!sub.empty()) { res.nested.push_back(sub); }
            } else if (
                entry.is_regular_file()
                && entry.path().extension() == ".org") {
                res.files.push_back(FileNode::from_file(ctx, entry));
            }
        }

        return res;
    }
};

void dir_explorer_loop(GLFWwindow* window, CVec<Str> directories) {
    auto       start = org::ImmAstContext::init_start_context();
    DirContext ctx{start};
    ctx.ctx      = start;
    ctx.root     = directories.front().toBase();
    DirNode node = DirNode::from_dir(ctx, ctx.root);

    LOG(INFO) << "Parsed root directory";

    while (!glfwWindowShouldClose(window)) {
        frame_start();
        fullscreen_window_begin();

        { node.render(ctx); }

        ImGui::End();
        frame_end(window);
        quit_on_q(window);
    }
}
