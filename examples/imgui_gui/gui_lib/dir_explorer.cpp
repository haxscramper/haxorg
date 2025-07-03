#include "dir_explorer.hpp"
#include "gui_lib/im_org_ui_common.hpp"
#include <haxorg/sem/SemBaseApi.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <haxorg/sem/ImmOrg.hpp>
#include <hstd/ext/logger.hpp>
#include <hstd/stdlib/Ptrs.hpp>

#include <sys/inotify.h>
#include <unistd.h>
#include <unordered_map>
#include <vector>
#include <filesystem>
#include <stdexcept>

using namespace hstd;

struct FileState {
    std::filesystem::file_time_type modified;

    static FileState from_file(fs::path const& p) {
        return FileState{.modified = fs::last_write_time(p)};
    }
};

struct ContentNode;

struct DirContext {
    org::imm::ImmAstContext::Ptr         ctx;
    fs::path                             root;
    UnorderedMap<Str, FileState>         fileStates;
    UnorderedMap<Str, SPtr<ContentNode>> cache;

    bool hadChanges(fs::path const& path) {
        if (auto old_state = fileStates.get(path.native())) {
            auto new_state = FileState::from_file(path);
            return old_state->modified < new_state.modified;
        } else {
            return true;
        }
    }

    void registerFile(fs::path const& path) {
        fileStates.insert_or_assign(
            path.native(), FileState::from_file(path));
    }

    SPtr<ContentNode> getFileNode(fs::path const& file);
};


struct ContentNode : public SharedPtrApi<ContentNode> {
    Vec<ContentNode::Ptr> nested;
    org::imm::ImmAdapter  a;

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
            for (auto& sub : nested) { sub->render(ctx); }
        } else if (isSubtree()) {
            if (ImGui::TreeNodeEx(
                    c_fmt("content_{}", a.id),
                    a.as<org::imm::ImmSubtree>()->level == 1
                        ? ImGuiTreeNodeFlags_DefaultOpen
                        : ImGuiTreeNodeFlags_None,
                    "%s",
                    getSubtree().title.c_str())) {
                for (auto& sub : nested) { sub->render(ctx); }
                ImGui::TreePop();
            }
        }
    }

    static ContentNode::Ptr from_node(
        DirContext&                 ctx,
        org::imm::ImmAdapter const& a) {
        auto res = ContentNode::shared();
        res->a   = a;
        if (auto tree = a.asOpt<org::imm::ImmSubtree>()) {
            res->data = Subtree{
                .title = tree->getCleanTitle(),
            };

            for (auto const& sub : tree->subAs<org::imm::ImmSubtree>()) {
                res->nested.push_back(ContentNode::from_node(ctx, sub));
            }
        } else if (auto doc = a.asOpt<org::imm::ImmDocument>()) {
            res->data = Document{};
            for (auto const& sub : doc->subAs<org::imm::ImmSubtree>()) {
                res->nested.push_back(ContentNode::from_node(ctx, sub));
            }
        }


        return res;
    }
};


SPtr<ContentNode> DirContext::getFileNode(const fs::path& file) {
    if (hadChanges(file)) {
        HSLOG_INFO(
            "load", "Loading file ", fs::relative(file, root).native());
        auto node = org::parseString(readFile(file));
        auto root = ctx->addRoot(node);
        auto res  = ContentNode::from_node(*this, root.getRootAdapter());
        cache.insert_or_assign(file.native(), res);
    }

    return cache.at(file.native());
}


struct FileNode : public SharedPtrApi<FileNode> {
    org::imm::ImmAdapter root;
    Str                  title;
    ContentNode::Ptr     document;
    Str                  relative;

    void render(DirContext& ctx) {
        if (ImGui::TreeNodeEx(
                c_fmt("file_{}", relative),
                ImGuiTreeNodeFlags_DefaultOpen,
                "%s",
                title.c_str())) {
            document->render(ctx);
            ImGui::TreePop();
        }
    }

    static FileNode::Ptr from_file(DirContext& ctx, fs::path const& file) {
        Str relative = fs::relative(file, ctx.root).native();
        HSLOG_DEPTH_SCOPE_ANON();

        auto doc      = ctx.getFileNode(file);
        auto res      = FileNode::shared();
        res->root     = doc->a;
        res->document = doc;
        res->relative = relative;
        if (true) {
            res->title = file.filename().native();
        } else {
            if (auto doc_node = doc->a.asOpt<org::imm::ImmDocument>();
                doc_node && doc_node.value()->title->has_value()) {
                res->title = org::getCleanText(doc_node.value().pass(
                    doc_node.value()->title->value()));
            } else {
                res->title = file.filename().native();
            }
        }

        return res;
    }
};

struct DirNode : public SharedPtrApi<DirNode> {
    Str                   relative;
    Opt<ContentNode::Ptr> readme;
    Vec<FileNode::Ptr>    files;
    Vec<DirNode::Ptr>     nested;

    bool empty() const {
        return !readme.has_value() && files.empty() && nested.empty();
    }

    void render(DirContext& ctx) {
        if (ImGui::TreeNodeEx(
                c_fmt("dir_{}", relative),
                ImGuiTreeNodeFlags_DefaultOpen,
                "%s",
                relative.c_str())) {
            for (auto& file : files) { file->render(ctx); }
            for (auto& dir : nested) { dir->render(ctx); }
            ImGui::TreePop();
        }
    }

    static DirNode::Ptr from_dir(DirContext& ctx, fs::path const& dir) {
        auto res      = DirNode::shared();
        res->relative = fs::relative(dir, ctx.root).native();
        LOGIC_ASSERTION_CHECK(
            !res->relative.empty(),
            "Relative directory is empty, root {} is not a parent of {}",
            escape_literal(ctx.root.native()),
            escape_literal(dir.native()));

        if (res->relative.starts_with(".") && 2 < res->relative.size()) {
            return res;
        }

        HSLOG_INFO(
            "load", "Loading directory ", escape_literal(res->relative));
        HSLOG_DEPTH_SCOPE_ANON();

        for (const auto& entry : fs::directory_iterator(dir)) {
            if (entry.is_directory()) {
                auto sub = DirNode::from_dir(ctx, entry);
                if (!sub->empty()) { res->nested.push_back(sub); }
            } else if (
                entry.is_regular_file()
                && entry.path().extension() == ".org") {
                res->files.push_back(FileNode::from_file(ctx, entry));
            }
        }

        return res;
    }
};

std::string format_event(const inotify_event& event) {
    std::string description = std::format(
        "Watch Descriptor: {}, Mask: {}, Cookie: {}, Length: {}, Name: {}",
        event.wd,
        event.mask,
        event.cookie,
        event.len,
        event.len > 0 ? std::string(event.name) : "None");

    if (event.mask & IN_CREATE) { description += " [Created]"; }
    if (event.mask & IN_DELETE) { description += " [Deleted]"; }
    if (event.mask & IN_MODIFY) { description += " [Modified]"; }
    if (event.mask & IN_MOVED_FROM) { description += " [Moved From]"; }
    if (event.mask & IN_MOVED_TO) { description += " [Moved To]"; }
    if (event.mask & IN_ISDIR) { description += " [Directory]"; }
    if (event.mask & IN_ACCESS) { description += " [Accessed]"; }
    if (event.mask & IN_ATTRIB) { description += " [Metadata Changed]"; }
    if (event.mask & IN_CLOSE_NOWRITE) {
        description += " [Closed (Read-only)]";
    }
    if (event.mask & IN_CLOSE_WRITE) {
        description += " [Closed (Write)]";
    }
    if (event.mask & IN_OPEN) { description += " [Opened]"; }

    return description;
}


class InotifyWatcher {
    int                               inotifyFd;
    std::unordered_map<int, fs::path> watchDescriptors;

  public:
    InotifyWatcher() : inotifyFd{inotify_init1(IN_NONBLOCK)} {
        if (inotifyFd == -1) {
            throw std::runtime_error("Failed to initialize inotify");
        }
    }

    ~InotifyWatcher() {
        for (const auto& [wd, path] : watchDescriptors) {
            inotify_rm_watch(inotifyFd, wd);
        }
        close(inotifyFd);
    }

    void update(DirContext& ctx, DirNode::Ptr const& dir) {
        Vec<fs::path>            files;
        Func<void(DirNode::Ptr)> aux;
        aux = [&](DirNode::Ptr dir) {
            files.push_back(ctx.root / fs::path{dir->relative.toBase()});
            for (auto const& file : dir->files) {
                files.push_back(ctx.root / file->relative.toBase());
            }
            for (auto const& sub : dir->nested) { aux(sub); }
        };

        aux(dir);
        update(files);
    }

    void update(const Vec<fs::path>& files) {
        for (const auto& [wd, path] : watchDescriptors) {
            inotify_rm_watch(inotifyFd, wd);
        }
        watchDescriptors.clear();

        for (const auto& file : files) {
            // HSLOG_INFO(
            //     "watch",
            //     "Watching for changes in ",
            //     escape_literal(file.native()));
            int wd = inotify_add_watch(
                inotifyFd,
                file.c_str(),
                IN_CREATE | IN_DELETE | IN_MODIFY | IN_ISDIR
                    | IN_MOVED_FROM | IN_MOVED_TO);
            if (wd == -1) {
                throw std::runtime_error(
                    "Failed to add inotify watch for: " + file.string());
            }
            watchDescriptors[wd] = file;
        }
    }

    bool hasChanges() {
        char buffer[4096]
            __attribute__((aligned(alignof(struct inotify_event))));
        ssize_t length = read(inotifyFd, buffer, sizeof(buffer));

        if (0 < length) {
            HSLOG_DEPTH_SCOPE_ANON();
            HSLOG_INFO("watch", "Changes in the filesystem");
            int  i           = 0;
            bool had_changes = false;
            while (i < length) {
                struct inotify_event* event = (struct
                                               inotify_event*)&buffer[i];
                if (event->len) {
                    fs::path const& path = watchDescriptors.at(event->wd);
                    std::string     description = format_event(*event);
                    HSLOG_INFO(
                        "watch", "Path ", path.native(), description);
                    had_changes = true;
                }
                i += sizeof(struct inotify_event) + event->len;
            }

            return had_changes;

        } else {
            return false;
        }
    }
};


void dir_explorer_loop(GLFWwindow* window, CVec<Str> directories) {
    auto       start = org::imm::ImmAstContext::init_start_context();
    DirContext ctx{start};
    ctx.ctx           = start;
    ctx.root          = directories.front().toBase();
    DirNode::Ptr node = DirNode::from_dir(ctx, ctx.root);

    InotifyWatcher watch;
    watch.update(ctx, node);

    HSLOG_INFO("dir-explorer", "Parsed root directory");

    while (!glfwWindowShouldClose(window)) {
        frame_start();
        fullscreen_window_begin();

        if (watch.hasChanges()) {
            node = DirNode::from_dir(ctx, ctx.root);
            watch.update(ctx, node);
        }

        { node->render(ctx); }

        ImGui::End();
        frame_end(window);
        quit_on_q(window);
    }
}
