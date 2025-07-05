#include "im_test_common.hpp"
#include <gui_lib/story_grid.hpp>
#include <haxorg/sem/ImmOrgBase.hpp>
#include <haxorg/sem/SemOrgFormat.hpp>

#define TEST_GRP_NAME "story_grid"

template <typename T>
struct hstd::JsonSerde<immer::vector<T>> {
    static json to_json(immer::vector<T> const& it) {
        auto result = json::array();
        for (auto const& i : it) {
            result.push_back(JsonSerde<T>::to_json(i));
        }

        return result;
    }
    static immer::vector<T> from_json(json const& j) {
        immer::vector<T> result;
        auto             tmp = result.transient();
        for (auto const& i : j) {
            tmp.push_back(JsonSerde<T>::from_json(i));
        }
        return tmp.persistent();
    }
};

template <typename Tag>
struct hstd::JsonSerde<hstd::ReflPathItem<Tag>> {
    static json to_json(ReflPathItem<Tag> const it) { return json{}; }

    static ReflPathItem<Tag> from_json(json const& j) {
        auto res = SerdeDefaultProvider<ReflPathItem<Tag>>::get();
        return res;
    }
};

struct StoryGridVars : public ImTestVarsBase {
    org::imm::ImmAstContext::Ptr         start;
    EditableOrgDocGroup                  history;
    StoryGridModel                       model;
    StoryGridConfig                      conf;
    hstd::Vec<hstd::log::log_sink_scope> debug_scopes;
    DocRootId                            root = DocRootId::Nil();

    StoryGridVars()
        : start{org::imm::ImmAstContext::init_start_context()}
        , history{start}
        , model{&history} {
        using Col          = TreeGridColumn;
        conf.gridViewport  = ImGui::GetMainViewport()->Size;
        conf.getDefaultDoc = []() -> TreeGridDocument {
            TreeGridDocument doc;
            doc.columns = {
                // Col{.name = "title", .width = 200},
                // Col{.name = "event", .width = 400},
                // Col{.name = "note", .width = 400},
                // Col{.name = "turning_point", .width = 300},
                // Col{.name = "value", .width = 200},
                // Col{
                //     .name  = "location",
                //     .width = 240,
                //     .edit  = EditableOrgText::Mode::SingleLine,
                // },
                // Col{.name = "pov", .width = 100},
            };
            return doc;
        };
    }

    void add_text(std::string const& text) {
        root            = model.history->addRoot(org::parseString(text));
        model.documents = model.history->migrate(model.documents).value();
        model.addDocument(root);
        model.rebuild(conf);
    }

    hstd::Str get_text() {
        auto sem = org::imm::sem_from_immer(
            model.history->getRoot(root).id, *model.history->getContext());
        return org::algo::Formatter::format(sem);
    }

    void init_section(ImGuiTestContext* ctx, std::string const& text) {
        if (ctx->IsFirstGuiFrame()) {
            model.ctx.setTraceFile(
                getDebugFile(ctx->Test, "story_grid.log"));

            trace.setTraceFile(
                getDebugFile(ctx->Test, "imgui_render.log"));

            add_text(text);
        }
    }

    void run_app_loop_iteration(ImGuiTestContext* ctx) {
        {
            auto __scope = IM_SCOPE_BEGIN("App loop iteration", "");
            model.shift  = getContentPos(ctx);
            run_story_grid_cycle(model, conf);
            model.applyChanges(conf);
        }

        if (is_im_traced()) { ImRenderTraceRecord::WriteTrace(trace); }
    }
};

namespace {

ImGuiTest* _init(ImGuiTestEngine* e, char const* name) {
    ImGuiTest* t = IM_REGISTER_TEST(e, TEST_GRP_NAME, name);
    t->SetVarsDataType<StoryGridVars>();
    return t;
}

void _StoryGrid_SingleView(ImGuiTestEngine* e) {
    ImTestFuncStartupParams params;
    params.windowSize.x = 700;
    params.windowSize.y = 700;
    auto t              = _init(e, "Single view");
    t->GuiFunc          = ImWrapGuiFuncT<StoryGridVars>(
        params, [](ImGuiTestContext* ctx, StoryGridVars& vars) {
            if (ctx->IsFirstGuiFrame()) {
                vars.conf.annotated = false;
                vars.init_section(ctx, R"(
* One subtree in grid
** Subtree 2
*** Subtree 2 3

- =story_event= :: Event 2
- =story_location= :: Location 2
- =story_note= :: Note 4


** Sub-tad 2
* sub-eq

- =story_event= :: Event 1
- =story_location= :: Location 1
- =story_note= :: Note 2
)");
            }

            vars.run_app_loop_iteration(ctx);
        });


    t->TestFunc = ImWrapTestFuncT<StoryGridVars>(
        params, [](ImGuiTestContext* ctx, StoryGridVars& vars) {
            // ctx->SuspendTestFunc();
        });
}

void _Load_One_Paragraph(ImGuiTestEngine* e) {
    ImGuiTest* t = IM_REGISTER_TEST(
        e, TEST_GRP_NAME, "Load one paragraph");
    t->SetVarsDataType<StoryGridVars>();
    ImTestFuncStartupParams params;
    params.windowSize.x = 700;
    params.windowSize.y = 700;
    t->GuiFunc          = ImWrapGuiFuncT<StoryGridVars>(
        params, [params](ImGuiTestContext* ctx, StoryGridVars& vars) {
            if (ctx->IsFirstGuiFrame()) {
                vars.conf.gridViewport = params.windowSize;
                vars.conf.blockGraphConf.getDefaultLaneMargin =
                    [](int lane) -> hstd::Pair<int, int> {
                    return {lane == 0 ? 0 : 50, 50};
                };
            }

            vars.init_section(ctx, R"(
* One subtree in grid
** Subtree 2
*** Subtree 2 3

- =story_event= :: Event 2
- =story_location= :: Location 2
- =story_note= :: Note 4


** Sub-tad 2
* sub-eq

- =story_event= :: Event 1
- =story_location= :: Location 1
- =story_note= :: Note 2

)");

            vars.run_app_loop_iteration(ctx);
        });

    t->TestFunc = ImWrapTestFuncT<StoryGridVars>(
        params, [](ImGuiTestContext* ctx, StoryGridVars& vars) {
            ImVec2 wpos = getContentPos(ctx);
            auto&  doc  = vars.model.graph.getGridNodes()
                            .at(0)
                            ->getTreeGrid()
                            .node;
            ctx->MouseMoveToPos(
                wpos + doc.getCellPos(0, "title") + ImVec2{0, 5});
            IM_CHECK_EQ(
                doc.getExistingCell(0, "title").getFinalTextValue(),
                "One subtree in grid");
            IM_CHECK_EQ(
                doc.getExistingCell(2, "event").getFinalTextValue(),
                "Event 2");
            IM_CHECK_EQ(
                doc.getExistingCell(2, "location").getFinalTextValue(),
                "Location 2");
            IM_CHECK_EQ(
                doc.getExistingCell(2, "note").getFinalTextValue(),
                "Note 4");
            vars.set_im_trace(1);
            ctx->Yield(2);
            ctx->MouseClick(0);
            vars.set_im_trace(1);
            ctx->Yield(2);
            ctx->MouseClick(0);
            ctx->KeyChars("test");
        });
}

void _FootnoteAnnotation(ImGuiTestEngine* e) {
    ImGuiTest* t = IM_REGISTER_TEST(
        e, TEST_GRP_NAME, "Load subtree with footnote annotations");
    t->SetVarsDataType<StoryGridVars>();
    ImTestFuncStartupParams params;
    params.windowSize.x = 1500;
    params.windowSize.y = 700;
    t->GuiFunc          = ImWrapGuiFuncT<StoryGridVars>(
        params, [params](ImGuiTestContext* ctx, StoryGridVars& vars) {
            if (ctx->IsFirstGuiFrame()) {
                vars.conf.gridViewport = params.windowSize;
                vars.debug_scopes.emplace_back(
                    HSLOG_SINK_FACTORY_SCOPED([ctx]() {
                        return hstd::log::set_sink_filter(
                            ::hstd::log::init_file_sink(getDebugFile(
                                ctx->Test, "scintilla_sink.log")),
                            [](hstd::log::log_record const& rec) -> bool {
                                return rec.data.category == "surface"
                                    && rec.data.source_scope
                                           == hstd::Vec<hstd::Str>{
                                               "gui",
                                               "widget",
                                               "scintilla_editor"};
                            });
                    }));
            }
            vars.init_section(ctx, R"(
* Subtree entry without any annotations
* One subtree in grid

#+begin_comment
some random shit about the comments or whatever, need to render as annotation [fn:annotation-529] more text [fn:text-529] more text [fn:text-333]
#+end_comment

[fn:annotation-529] Footnote inside of a comment block

[fn:text-529] More footnotes on the same block

[fn:text-333] And some more text, followed but [fn:but-536] and then another [fn:another-536]

[fn:but-536] recursive footnote that will contain more text to render somewhere

[fn:another-536] recursive footnote

* Another subtree w/o annotations
)");
            vars.run_app_loop_iteration(ctx);
        });

    t->TestFunc = ImWrapTestFuncT<StoryGridVars>(
        params, [](ImGuiTestContext* ctx, StoryGridVars& vars) {
            ImVec2 wpos = getContentPos(ctx);
            auto&  m    = vars.model;
            auto&  doc  = m.graph.getGridNodes().at(0)->getTreeGrid().node;
            auto&  ir   = m.graph.getLayer().block.ir;
            auto const& spans = ir.getLaneSpans();
            auto&       rg    = m.graph;
            IM_CHECK_EQ(spans.size(), 4);
            IM_CHECK_EQ(ir.lanes.at(1).scrollOffset, 0);
            IM_CTX_ACT(
                MouseMoveToPos,
                wpos
                    + ImVec2{
                        static_cast<float>(spans.at(1).first + 50), 5});

            // m.ctx.message(to_json_eval(rg.nodes).dump(2));

            IM_CHECK_BINARY_PRED(
                rg.getPosition({0, 0}),
                ImVec2(spans.at(0).first, 0),
                is_within_distance,
                5);


            IM_CHECK_BINARY_PRED(
                rg.getPosition({1, 0}),
                ImVec2(spans.at(1).first, 0),
                is_within_distance,
                5);

            {
                m.ctx.message("Scroll");
                auto __scope = m.ctx.scopeLevel();
                IM_CTX_ACT(MouseWheelY, -5);
                vars.set_im_trace(2);
                IM_CTX_ACT(Yield, 5);
                IM_CHECK_EQ(
                    ir.lanes.at(1).scrollOffset,
                    vars.conf.mouseScrollMultiplier * 5);
            }

            // m.ctx.message(to_json_eval(rg.nodes).dump(2));

            IM_CHECK_BINARY_PRED(
                rg.getPosition({1, 0}),
                ImVec2(spans.at(1).first, 50),
                is_within_distance,
                5);
        });
}

} // namespace


void RegisterApptests_story_grid(ImGuiTestEngine* e) {
    _FootnoteAnnotation(e);
    _StoryGrid_SingleView(e);
    _Load_One_Paragraph(e);
}
