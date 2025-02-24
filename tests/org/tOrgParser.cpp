#include "tOrgTestCommon.hpp"

using namespace org;
using namespace hstd;


TEST(OrgParseSem, NamedPropertyModification) {
    auto doc = testParseString(R"(* Subtree)");

    auto tree = doc.at(0).as<sem::Subtree>();
    tree->setPropertyStrValue("123", "bookmark_pos");

    Str formatted = org::formatToString(doc);
    EXPECT_NE(formatted.find(":bookmark_pos: 123"), -1) << formatted;

    tree->removeProperty("bookmark_pos");
    formatted = org::formatToString(doc);
    EXPECT_EQ(formatted.find(":bookmark_pos: 123"), -1) << formatted;
}

TEST(OrgParseSem, LinkAttachedGet1) {
    auto doc = testParseString(
        R"(#+attr_link: :attach-method copy :attach-on-export t
[[attachment:image 1.jpg]]
)");

    EXPECT_EQ2(doc->getKind(), OrgSemKind::Document);
    auto par = doc->subnodes.at(0);
    EXPECT_EQ2(par->getKind(), OrgSemKind::Paragraph);
    auto link = par->subnodes.at(0);
    EXPECT_EQ2(link->getKind(), OrgSemKind::Link);

    auto link1 = link.getAs<sem::Link>();
    ASSERT_TRUE(link1 != nullptr);

    auto args = link1->getAttrs("attach-on-export");
    EXPECT_EQ(args.size(), 1);
    auto arg0 = args.at(0);
    EXPECT_EQ(arg0.getBool(), true);
    EXPECT_EQ(arg0.getString(), "t");
}

TEST(OrgParseSem, TracerOperations1) {
    auto                text = R"(
* Subtree
  :properties:
  :key: value
  :end:
)";
    org::test::MockFull p{true, true};
    fs::path tokenizer_trace{"/tmp/TraceOperations1_tokenizer_trace.txt"};
    p.tokenizer->setTraceFile(tokenizer_trace);
    p.tokenizer->traceStructured = true;

    fs::path parser_trace{"/tmp/TraceOperations1_parser_trace.txt"};
    p.parser->setTraceFile(parser_trace);
    p.parser->traceStructured = true;

    sem::OrgConverter converter{};
    fs::path          sem_trace{"/tmp/TraceOperations1_sem_trace.txt"};
    converter.setTraceFile(sem_trace);
    converter.traceStructured = true;

    fs::path      lex_trace{"/tmp/TraceOperations1_lex_trace.txt"};
    std::ofstream fileTrace{lex_trace.c_str()};

    org::parse::LexerParams params;
    params.traceStructured = true;
    params.maxUnknown      = 1;
    params.traceStream     = &fileTrace;
    p.tokenizeBase(text, params);
    p.tokenizeConvert();
    p.parse();

    auto document = converter.toDocument(
        org::parse::OrgAdapter(&p.nodes, org::parse::OrgId(0)));

    org::algo::ExporterJson exp{};
    fs::path exp_trace{"/tmp/TraceOperations1_exp_trace.txt"};
    exp.setTraceFile(exp_trace);
    exp.traceStructured = true;
    exp.evalTop(document);
}


TEST(OrgParseSem, ParagraphBody) {
    {
        auto par = parseOne<sem::Paragraph>("NOTE: content");
        EXPECT_TRUE(par->hasAdmonition());
        EXPECT_EQ(par->getAdmonitions().at(0), "NOTE");
        EXPECT_FALSE(par.isNil());
        auto body = par->getBody();
        EXPECT_EQ(body.size(), 1);
        EXPECT_TRUE(body.at(0)->is(OrgSemKind::Word));
    }

    {
        auto par = parseOne<sem::Paragraph>("NOTE:");
        EXPECT_FALSE(par.isNil());
        auto body = par->getBody();
        EXPECT_EQ(body.size(), 0);
    }

    {
        auto par  = immConv(parseOne<sem::Paragraph>("NOTE: content"));
        auto body = par.node.getBody();
        EXPECT_EQ(body.size(), 1);
        EXPECT_TRUE(body.at(0)->is(OrgSemKind::Word));
    }

    {
        auto par = parseOne<sem::Paragraph>("[fn:footnote] content");
        EXPECT_FALSE(par.isNil());
        auto body = par->getBody();
        EXPECT_EQ(body.size(), 1);
        EXPECT_TRUE(body.at(0)->is(OrgSemKind::Word));
    }

    {
        auto par = parseOne<sem::Paragraph>(
            "[fn::inline footnote] content");
        EXPECT_FALSE(par.isNil());
        auto body = par->getBody();
        EXPECT_EQ(body.size(), 3);
        EXPECT_TRUE(body.at(0)->is(OrgSemKind::InlineFootnote));
        EXPECT_TRUE(body.at(2)->is(OrgSemKind::Word));
    }
}

TEST(OrgParseSem, CustomBlocks) {
    auto block = parseOne<sem::BlockDynamicFallback>(
        R"(#+begin_random_content
body of the random
#+end_random_content)");

    EXPECT_EQ(block->name, "randomcontent");
    auto body = block.at(0);
    EXPECT_EQ(body->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(body.at(0)->getKind(), OrgSemKind::Word);
    EXPECT_EQ(body.at(0).as<sem::Word>()->text, "body");
}

TEST(OrgParseSem, BlockAttachment) {
    {
        auto block = parseOne<sem::BlockExample>(
            R"(#+caption: example *caption*
#+begin_example
content
#+end_example)");

        auto caption = block->getCaption();
        // dbgString(caption);
        EXPECT_EQ(caption.size(), 1);
        auto cap0 = caption.at(0);
        EXPECT_EQ(cap0->getKind(), OrgSemKind::Paragraph);
        EXPECT_EQ(cap0.size(), 3);
        EXPECT_EQ(cap0.at(0)->getKind(), OrgSemKind::Word);
        EXPECT_EQ(cap0.at(2)->getKind(), OrgSemKind::Bold);
    }

    {
        auto block = parseOne<sem::BlockExample>(
            R"(#+name: example-block-one
#+begin_example
content
#+end_example)");

        auto name = block->getName();
        EXPECT_EQ(name.size(), 1);
        EXPECT_EQ(name.at(0), "example-block-one");
    }
}

TEST(OrgParseSem, SubtreeProperties) {
    {
        auto t = parseOne<sem::Subtree>(
            R"(* Parent capturing statistics
  :PROPERTIES:
  :COOKIE_DATA: todo recursive
  :END:)",
            getDebugFile("cookie_data"));

        auto p = org::getSubtreeProperties<sem::NamedProperty::CookieData>(
            t);
        EXPECT_EQ(p.size(), 1);
        EXPECT_EQ(p.at(0).isRecursive, true);
        EXPECT_EQ(
            p.at(0).source,
            sem::NamedProperty::CookieData::TodoSource::Todo);
    }
    {
        auto tree = parseOne<sem::Subtree>(
            R"(** COMPLETED Usable code coverage output generator
     CLOSED: [2024-11-01 Fri 20:59:49 +04]
     :PROPERTIES:
     :CREATED:  [2024-05-31 Fri 23:38:18 +04]
     :ID:       5ab53c80-6d65-4768-84c6-d881ce47cf0e
     :ARCHIVE_TIME: 2024-11-01 Fri 21:00:18 +04
     :ARCHIVE_FILE: ~/projects.org
     :ARCHIVE_OLPATH: Haxorg/Infrastructure/Code coverage
     :ARCHIVE_CATEGORY: projects
     :ARCHIVE_TODO: COMPLETED
     :ARCHIVE:  %s_archive::* Misc
     :END:
)",
            getDebugFile("trace"));

        // dbgString(tree);

        {
            auto olpath = org::getSubtreeProperties<
                sem::NamedProperty::ArchiveOlpath>(tree);
            EXPECT_EQ(olpath.size(), 1);
            auto const& p = olpath.at(0).path.path;
            EXPECT_EQ(p.at(0), "Haxorg");
            EXPECT_EQ(p.at(1), "Infrastructure");
            EXPECT_EQ(p.at(2), "Code coverage");
        }

        {
            auto p = org::getSubtreeProperties<
                sem::NamedProperty::ArchiveFile>(tree);
            EXPECT_EQ(p.size(), 1);
            EXPECT_EQ(p.at(0).file, "~/projects.org");
        }


        {
            auto p = org::getSubtreeProperties<
                sem::NamedProperty::ArchiveCategory>(tree);
            EXPECT_EQ(p.size(), 1);
            EXPECT_EQ(p.at(0).category, "projects");
        }
        {
            auto p = org::getSubtreeProperties<
                sem::NamedProperty::ArchiveTodo>(tree);
            EXPECT_EQ(p.size(), 1);
            EXPECT_EQ(p.at(0).todo, "COMPLETED");
        }

        {
            auto p = org::getSubtreeProperties<
                sem::NamedProperty::ArchiveTarget>(tree);
            EXPECT_EQ(p.size(), 1);
            EXPECT_EQ(p.at(0).pattern, "%s_archive");
            EXPECT_EQ(p.at(0).path.path.size(), 1);
            EXPECT_EQ(p.at(0).path.path.at(0), "Misc");
        }
    }
    {
        auto tree = parseOne<sem::Subtree>(
            R"(* Tree
:properties:
:visibility: content
:prop_json:NaME: {"key": "value"}
:prop_args:NAMe: :key value
:end:)",
            getDebugFile("prop_json"));
        {
            auto p = org::getSubtreeProperties<
                sem::NamedProperty::CustomSubtreeJson>(tree);
            EXPECT_EQ(p.size(), 1);
            EXPECT_EQ(p.at(0).name, "name"_ss);
            EXPECT_EQ(p.at(0).value.getField("key").getString(), "value");
        }
        {
            auto p = org::getSubtreeProperties<
                sem::NamedProperty::CustomSubtreeFlags>(tree);
            EXPECT_EQ(p.size(), 1);
            EXPECT_EQ(p.at(0).value.getNamedSize(), 1);
            EXPECT_EQ(p.at(0).name, "name"_ss);
            EXPECT_EQ(
                p.at(0).value.getFirstNamed("key")->getString(), "value");
        }
    }
}

TEST(OrgParseSem, HashtagParse) {
    using V = Vec<sem::HashTagFlat>;
    {
        auto h = parseOne<sem::HashTag>("#hashtag");
        EXPECT_EQ(h->text.head, "hashtag"_ss);
        EXPECT_EQ(h->text.subtags.size(), 0);
        EXPECT_EQ(
            h->text.getFlatHashes(), V{sem::HashTagFlat{{"hashtag"_ss}}});
    }
    {
        auto h = parseOne<sem::HashTag>("#hashtag##[sub]");
        EXPECT_EQ(h->text.head, "hashtag");
        EXPECT_EQ(h->text.subtags.size(), 1);
        auto flat = h->text.getFlatHashes();
        EXPECT_EQ(flat.size(), 2);
        EXPECT_EQ(flat.at(0), sem::HashTagFlat{{"hashtag"}});
        EXPECT_EQ(flat.at(1), (sem::HashTagFlat{{"hashtag", "sub"}}));
    }

    {
        auto h = parseOne<sem::HashTag>("#one##[two##[three,four,five]]");
        EXPECT_EQ(h->text.head, "one");
        EXPECT_EQ(h->text.subtags.size(), 1);
        auto flat = h->text.getFlatHashes();
        EXPECT_EQ(flat.size(), 5);
        EXPECT_EQ(flat.at(0), sem::HashTagFlat{{"one"}});
        EXPECT_EQ(flat.at(1), (sem::HashTagFlat{{"one", "two"}}));
        EXPECT_EQ(flat.at(2), (sem::HashTagFlat{{"one", "two", "three"}}));
        EXPECT_EQ(flat.at(3), (sem::HashTagFlat{{"one", "two", "four"}}));
        EXPECT_EQ(flat.at(4), (sem::HashTagFlat{{"one", "two", "five"}}));
    }

    {
        auto par = immConv(parseOne<sem::HashTag>("#hashtag##[sub]"));
        auto h   = par.node;
        EXPECT_EQ(h->text.head, "hashtag");
        EXPECT_EQ(h->text.subtags.size(), 1);
        auto flat = h->text.getFlatHashes();
        EXPECT_EQ(flat.size(), 2);
        EXPECT_EQ(flat.at(0), sem::HashTagFlat{{"hashtag"}});
        EXPECT_EQ(flat.at(1), (sem::HashTagFlat{{"hashtag", "sub"}}));
    }
}

TEST(OrgParseSem, SubtreeLogParsing) {
    {
        auto s = parseOne<sem::Subtree>(R"(**** COMPLETED Subtree
     CLOSED: [2000-01-03 Wed 10:43:40 +04]
     :PROPERTIES:
     :CREATED:  [2000-01-03 Wed 09:51:41 +04]
     :END:
     :LOGBOOK:
     - Tag "#work##xasd" Added on [2000-01-03 Wed 09:52:00 +04]
     CLOCK: [2000-01-03 Wed 09:51:50 +04]--[2000-01-03 Wed 10:43:40 +04] =>  0:52
     - State "WIP"        from "TODO"       [2000-01-03 Wed 09:51:50 +04]
     - State "COMPLETED"  from "WIP"        [2000-01-03 Wed 10:43:40 +04]
     :END:)");

        EXPECT_EQ(s->logbook.size(), 4);
        auto const& l = s->logbook;
        EXPECT_TRUE(l.at(0)->head.isTag());
        EXPECT_TRUE(l.at(1)->head.isClock());
        EXPECT_TRUE(l.at(2)->head.isState());
        EXPECT_TRUE(l.at(3)->head.isState());
        EXPECT_EQ(l.at(0)->head.getTag().on.getBreakdown().year, 2000);
        EXPECT_EQ(l.at(0)->head.getTag().on.getBreakdown().minute, 52);
        EXPECT_EQ(l.at(1)->head.getClock().from.getBreakdown().minute, 51);
        EXPECT_EQ(
            l.at(1)->head.getClock().to.value().getBreakdown().minute, 43);
        EXPECT_EQ(l.at(2)->head.getState().from, "TODO"_ss);
        EXPECT_EQ(l.at(2)->head.getState().to, "WIP"_ss);
        EXPECT_EQ(l.at(3)->head.getState().to, "COMPLETED"_ss);
        EXPECT_EQ(l.at(3)->head.getState().from, "WIP"_ss);
    }
    {
        auto t = parseOne<sem::Subtree>(
            R"(* COMPLETED Prolog homework [60%]
  CLOSED: [2019-11-07 Thu 19:35] DEADLINE: <2019-12-15 Sun>
  :LOGBOOK:
  - State "COMPLETED"  from "TODO"       [2019-11-07 Thu 19:35]
  - New deadline from "[2019-10-01 Tue]" on [2019-10-11 Fri 13:50] \\
    Updated whatever
  - New deadline from "[2019-09-26 Thu]" on [2019-09-27 Fri 22:36] \\
    New week deadline
  :END:
)");
        EXPECT_TRUE(t->deadline.has_value());
        auto d = t->deadline->getBreakdown();
        EXPECT_EQ(d.day, 15);
        EXPECT_EQ(d.year, 2019);
        EXPECT_EQ(d.month, 12);

        EXPECT_TRUE(t->closed.has_value());
        auto c = t->closed->getBreakdown();
        EXPECT_EQ(c.year, 2019);
        EXPECT_EQ(c.day, 07);
        EXPECT_EQ(c.month, 11);
        EXPECT_EQ(c.minute, 35);

        auto log = t->logbook;

        auto state = log.at(0);
        auto dead1 = log.at(1);
        auto dead2 = log.at(2);
        EXPECT_TRUE(state->head.isState());
        EXPECT_TRUE(dead1->head.isDeadline());
        EXPECT_TRUE(dead2->head.isDeadline());
    }
    {
        auto t = parseOne<sem::Subtree>(
            R"(** COMPLETED Elisp improvements [0/2]
   :LOGBOOK:
   - Refiled on [2020-05-02 Sat 14:40] from [[id:e2de69d4-4073-477f-af6b-cc2cd8d5a122][Quick latex input [17/26]]]
   :END:
)");

        EXPECT_TRUE(t->logbook.at(0)->head.isRefile());
        auto l = t->logbook.at(0)->head.getRefile();
        EXPECT_EQ(l.on.getBreakdown().year, 2020);
        EXPECT_EQ(l.on.getBreakdown().minute, 40);
    }

    {
        auto const t = parseOne<sem::Subtree>(
            R"(**** COMPLETED [#A] Priority
  :LOGBOOK:
  - Priority "B" Added on [2023-07-20 Thu 13:43:21 +04]
  - Priority "A" Changed From "B" on [2023-07-20 Thu 13:43:21 +04]
  - Priority "A" Changed From "S" on [2023-07-20 Thu 13:43:23 +04]
  :END:)",
            getDebugFile("priority"));

        auto const& l = t->logbook;
        EXPECT_TRUE(l.at(0)->head.isPriority());
        EXPECT_TRUE(l.at(1)->head.isPriority());
        EXPECT_TRUE(l.at(2)->head.isPriority());
        auto p0 = l.at(0)->head.getPriority();
        EXPECT_FALSE(p0.oldPriority.has_value());
        EXPECT_TRUE(p0.newPriority.has_value());
        EXPECT_EQ(p0.newPriority.value(), "B");

        auto p1 = l.at(1)->head.getPriority();
        EXPECT_TRUE(p1.oldPriority.has_value());
        EXPECT_TRUE(p1.newPriority.has_value());
        EXPECT_EQ(p1.oldPriority.value(), "B");
        EXPECT_EQ(p1.newPriority.value(), "A");
        EXPECT_EQ(p1.on.getBreakdown().second, 21);
    }

    {
        auto        t = parseOne<sem::Subtree>(R"(**** Notes
  :LOGBOOK:
  - Note taken on [2023-07-14 Fri 14:34:03 +04] \\
    Increasing complexity  ranking because this  is already spread  to multiple
    people and a set of non-trivial tasks.
  :END:)");
        auto const& l = t->logbook;
        EXPECT_TRUE(l.at(0)->head.isNote());
        auto const& n = l.at(0)->head.getNote();
        EXPECT_EQ(n.on.getBreakdown().year, 2023);
        EXPECT_EQ(n.on.getBreakdown().second, 03);
        EXPECT_TRUE(l.at(0)->desc.has_value());
        Vec<Str> desc = org::getDfsLeafText(
            l.at(0)->desc.value().asOrg(), {OrgSemKind::Word});
        EXPECT_EQ(desc.at(0), "Increasing");
        EXPECT_NE(desc.indexOf("tasks"), -1);
    }

    {
        auto t = parseOne<sem::Subtree>(
            R"(* Note
  :LOGBOOK:
  - Note taken on [2023-07-14 Fri 14:34:03 +04] \\
    - Nested list in logbook
    - Two items in log
      - More nesting1
      - More nesting2
  :END:)",
            getDebugFile("nested_log"));

        auto const& l    = t->logbook;
        auto const& d    = l.at(0)->desc.value();
        auto const& nest = d->at(0);
        EXPECT_EQ(nest->getKind(), OrgSemKind::List);
        EXPECT_EQ(nest.size(), 2);
        auto const& it1 = nest->at(1);
        EXPECT_EQ(it1->getKind(), OrgSemKind::ListItem);
        EXPECT_EQ(it1->at(0)->getKind(), OrgSemKind::Paragraph);
        EXPECT_EQ(it1->at(1)->getKind(), OrgSemKind::List);
        EXPECT_EQ(it1->at(1)->at(0)->getKind(), OrgSemKind::ListItem);
        EXPECT_EQ(it1->at(1)->at(1)->getKind(), OrgSemKind::ListItem);
        EXPECT_EQ(
            org::getCleanText(it1->at(1)->at(0)), "More nesting1"_ss);
        EXPECT_EQ(
            org::getCleanText(it1->at(1)->at(1)), "More nesting2"_ss);
    }
}


TEST(OrgParseSem, SubtreeTimesParsing) {

    {
        auto t = parseOne<sem::Subtree>(R"(* Subtree
    CLOSED: [2019-11-08 Thu 19:35]
)");
        EXPECT_EQ(
            t->closed.value().getBreakdown(),
            (UserTimeBreakdown{
                .year   = 2019,
                .month  = 11,
                .day    = 8,
                .hour   = 19,
                .minute = 35,
            }));
    }
    {
        auto t = parseOne<sem::Subtree>(
            R"(* Subtree
CLOSED: [2019-11-08 Thu 19:35]
)",
            getDebugFile("closed_no_indent"));
        EXPECT_EQ(
            t->closed.value().getBreakdown(),
            (UserTimeBreakdown{
                .year   = 2019,
                .month  = 11,
                .day    = 8,
                .hour   = 19,
                .minute = 35,
            }));
    }
    {
        auto t = parseOne<sem::Subtree>(R"(* Subtree
    CLOSED: [2019-11-08 Thu 19:35] DEADLINE: [2019-11-07 Thu 19:35] SCHEDULED: [2019-11-02 Thu 19:35]
)");
        EXPECT_EQ(
            t->closed.value().getBreakdown(),
            (UserTimeBreakdown{
                .year   = 2019,
                .month  = 11,
                .day    = 8,
                .hour   = 19,
                .minute = 35,
            }));

        EXPECT_EQ(
            t->deadline.value().getBreakdown(),
            (UserTimeBreakdown{
                .year   = 2019,
                .month  = 11,
                .day    = 7,
                .hour   = 19,
                .minute = 35,
            }));

        EXPECT_EQ(
            t->scheduled.value().getBreakdown(),
            (UserTimeBreakdown{
                .year   = 2019,
                .month  = 11,
                .day    = 2,
                .hour   = 19,
                .minute = 35,
            }));
    }
    {
        auto t = parseOne<sem::Subtree>(
            R"(* Subtree
CLOSED: [2019-11-12 Thu 19:35]
DEADLINE: [2019-11-13 Thu 19:35]
SCHEDULED: [2019-11-14 Thu 19:35]
)",
            getDebugFile("multiline_times"));

        EXPECT_EQ(
            t->closed.value().getBreakdown(),
            (UserTimeBreakdown{
                .year   = 2019,
                .month  = 11,
                .day    = 12,
                .hour   = 19,
                .minute = 35,
            }));

        EXPECT_EQ(
            t->deadline.value().getBreakdown(),
            (UserTimeBreakdown{
                .year   = 2019,
                .month  = 11,
                .day    = 13,
                .hour   = 19,
                .minute = 35,
            }));

        EXPECT_EQ(
            t->scheduled.value().getBreakdown(),
            (UserTimeBreakdown{
                .year   = 2019,
                .month  = 11,
                .day    = 14,
                .hour   = 19,
                .minute = 35,
            }));
    }
}

TEST(OrgParseSem, SubtreeTitleParsing) {
    {
        auto t = parseOne<sem::Subtree>(R"(* Title [0/1])");
        auto c = t->completion.value();
        EXPECT_EQ(c.full, 1);
        EXPECT_EQ(c.done, 0);
        EXPECT_EQ(c.isPercent, false);
    }
    {
        auto t = parseOne<sem::Subtree>(R"(* Title [33%])");
        auto c = t->completion.value();
        EXPECT_EQ(c.full, 100);
        EXPECT_EQ(c.done, 33);
        EXPECT_EQ(c.isPercent, true);
    }
}

TEST(OrgParseSem, TextParsing) {
    {
        auto w = parseOne<sem::Word>("test");
        EXPECT_EQ(w->text, "test"_ss);
    }
    {
        auto w = parseOne<sem::Word>("test-one");
        EXPECT_EQ(w->text, "test-one"_ss);
    }
    {
        auto w = parseOne<sem::Word>("don't");
        EXPECT_EQ(w->text, "don't"_ss);
    }
    {
        auto par = parseOne<sem::Paragraph>(
            R"(@@html:<b>@@bold text@@html:</b>@@)",
            getDebugFile("inline_export"));
        EXPECT_EQ(par.size(), 5);
        EXPECT_EQ(par.at(0)->getKind(), OrgSemKind::InlineExport);
        EXPECT_EQ(par.at(1)->getKind(), OrgSemKind::Word);
        EXPECT_EQ(par.at(2)->getKind(), OrgSemKind::Space);
        EXPECT_EQ(par.at(3)->getKind(), OrgSemKind::Word);
        EXPECT_EQ(par.at(4)->getKind(), OrgSemKind::InlineExport);

        auto ex0 = par.at(0).as<sem::InlineExport>();
        EXPECT_EQ(ex0->exporter, "html"_ss);
        EXPECT_EQ(ex0->content, "<b>"_ss);

        auto ex4 = par.at(4).as<sem::InlineExport>();
        EXPECT_EQ(ex4->exporter, "html"_ss);
        EXPECT_EQ(ex4->content, "</b>"_ss);
    }

    {
        auto par = parseOne<sem::Paragraph>(R"([2024])");
        EXPECT_EQ(par.size(), 3);
    }

    {
        auto par = parseOne<sem::Paragraph>(R"([2024-12])");
        EXPECT_EQ(par.size(), 3);
    }
}

TEST(OrgParseSem, TblfmExpression) {
    {
        auto t = parseOne<sem::CmdTblfm>(
            R"(#+TBLFM: $6=vsum($P1..$P3)::$7=10*$Tot/$max;%.1f::$at=vmean(@-2..@-1);%.1f)",
            getDebugFile("trace"));
    }
}

TEST(OrgParseSem, LinkTarget) {
    {
        auto l = parseOne<sem::Link>(
            R"([[* Title]])", getDebugFile("subtree_title"));
        auto const& t = l->target;
        EXPECT_EQ(t.getKind(), sem::LinkTarget::Kind::SubtreeTitle);
        EXPECT_EQ(t.getSubtreeTitle().level, 1);
        EXPECT_EQ(t.getSubtreeTitle().title.path.size(), 1);
        EXPECT_EQ(t.getSubtreeTitle().title.path.at(0), "Title");
    }
    {
        auto l = parseOne<sem::Link>(
            R"([[** Title/Sub]])", getDebugFile("subtree_title"));
        auto const& t = l->target;
        EXPECT_EQ(t.getKind(), sem::LinkTarget::Kind::SubtreeTitle);
        EXPECT_EQ(t.getSubtreeTitle().level, 2);
        EXPECT_EQ(t.getSubtreeTitle().title.path.size(), 2);
        EXPECT_EQ(t.getSubtreeTitle().title.path.at(0), "Title");
        EXPECT_EQ(t.getSubtreeTitle().title.path.at(1), "Sub");
    }
    {
        auto l = parseOne<sem::Link>(
            R"([[#custom-id]])", getDebugFile("custom_id"));
        auto const& t = l->target;
        EXPECT_EQ(t.getKind(), sem::LinkTarget::Kind::CustomId);
        EXPECT_EQ(t.getCustomId().text, "custom-id");
    }
}

TEST(OrgParseSem, ColumnView) {
    {
        auto doc = parseOne<sem::Document>(
            R"(#+columns: %20ITEM %9Approved(Approved?){X} %Owner %11Status %10Time_Spent{:})",
            getDebugFile("column_view"));
        sem::ColumnView const& v = doc->options->columns.value();
        EXPECT_EQ(v.columns.size(), 5);
        auto const& c0 = v.columns.at(0);
        EXPECT_EQ(c0.width.value(), 20);
        EXPECT_EQ(c0.property.value(), "ITEM"_ss);
        auto const& c1 = v.columns.at(1);
        EXPECT_EQ(c1.width.value(), 9);
        EXPECT_EQ(c1.propertyTitle.value(), "Approved?"_ss);
        EXPECT_TRUE(c1.summary.value().isCheckboxAggregate());
        EXPECT_EQ(
            c1.summary.value().getCheckboxAggregate().kind,
            sem::ColumnView::Summary::CheckboxAggregate::Kind::
                IfAllNested);
    }
}

TEST(OrgParseSem, List) {
    {
        auto l = parseOne<sem::List>("- Desc :: value");
        EXPECT_EQ(l.size(), 1);
        auto it = l.at(0).as<sem::ListItem>();
        EXPECT_EQ(it->getCleanHeader().value(), "Desc");

        auto conv = immConv(l);
        EXPECT_EQ(
            conv.node.at(0).as<imm::ImmListItem>().getCleanHeader(),
            "Desc");
    }
    {
        auto l = parseOne<sem::List>("- Desc :: value");
        EXPECT_EQ(l.size(), 1);
        org::setDescriptionListItemBody(
            l, "Desc", {parseOne<sem::Paragraph>("value")});

        EXPECT_EQ(l.size(), 1);
        org::setDescriptionListItemBody(
            l, "Desc2", {parseOne<sem::Paragraph>("value")});
        EXPECT_EQ(l.size(), 2);
    }
    {
        auto l = parseOne<sem::List>("- Item");
        EXPECT_EQ(l.size(), 1);
        org::insertListItemBody(l, 0, {parseOne<sem::Paragraph>("Item2")});
        EXPECT_EQ(l.size(), 2);
        EXPECT_EQ(org::getCleanText(l.at(0)), "Item2"_ss);
        EXPECT_EQ(org::getCleanText(l.at(1)), "Item"_ss);
    }
}

TEST(OrgParseSem, SubtreePropertyContext) {
    {
        auto t1 = parseOne<sem::Subtree>(
            R"(* Subtree
:properties:
:header-args:nim: :cache yes
:end:

** Subtree 2
:properties:
:header-args:nim: :results silent
:end:
)",
            getDebugFile("subtree_property"));

        auto t2 = t1.at(0).as<sem::Subtree>();
        auto h1 = t1->getProperty("header-args");
        EXPECT_TRUE(h1.has_value());
        EXPECT_EQ(
            h1.value().getKind(), sem::NamedProperty::Kind::CustomArgs);
        auto attrs1 = h1.value().getCustomArgs().attrs;
        EXPECT_EQ(attrs1.getAttrs("cache").size(), 1);
        EXPECT_EQ(attrs1.getAttrs("cache").at(0).name.value(), "cache");
        EXPECT_EQ(attrs1.getAttrs("cache").at(0).value, "yes");
        EXPECT_EQ(attrs1.getAttrs("cache").at(0).getBool(), true);

        auto h2     = t2->getProperty("header-args");
        auto attrs2 = h2.value().getCustomArgs().attrs;
        EXPECT_TRUE(h2.has_value());
        EXPECT_EQ(attrs2.getAttrs("results").size(), 1);
        EXPECT_EQ(
            attrs2.getAttrs("results").at(0).name.value(), "results");
        EXPECT_EQ(attrs2.getAttrs("results").at(0).value, "silent");

        auto stacked = org::getFinalProperty({t1, t2}, "header-args");
        EXPECT_TRUE(stacked.has_value());
        auto s = stacked.value();
        EXPECT_EQ(
            s.getCustomArgs().attrs.getAttrs("results").at(0).value,
            "silent");

        EXPECT_EQ(
            s.getCustomArgs().attrs.getAttrs("cache").at(0).value, "yes");
    }
}

TEST(OrgParseSem, Macro) {
    {
        auto m = parseOne<sem::Macro>(R"({{{simple}}})");
        EXPECT_EQ(m->name, "simple"_ss);
    }
    {
        auto m = parseOne<sem::Macro>(R"({{{simple(arg)}}})");
        EXPECT_EQ(m->name, "simple"_ss);
        EXPECT_EQ(m->attrs.getPositionalSize(), 1);
        EXPECT_EQ(m->attrs.atPositional(0).getString(), "arg"_ss);
    }
    {
        auto m = parseOne<sem::Macro>(R"({{{dashed-name}}})");
        EXPECT_EQ(m->name, "dashed-name"_ss);
    }
    {
        auto m = parseOne<sem::Macro>(
            R"({{{property(PROPERTY-NAME, SEARCH OPTION)}}})");
        EXPECT_EQ(m->name, "property");
        EXPECT_EQ(m->attrs.getPositionalSize(), 2);
        EXPECT_EQ(
            m->attrs.atPositional(0).getString(), "PROPERTY-NAME"_ss);
        EXPECT_EQ(m->attrs.atPositional(1).getString(), "SEARCH OPTION");
    }
    {
        auto m = parseOne<sem::Macro>(R"({{{named(key=value)}}})");
        EXPECT_EQ(m->name, "named"_ss);
        EXPECT_EQ(m->attrs.getPositionalSize(), 0);
        EXPECT_EQ(m->attrs.getNamedSize(), 1);
        EXPECT_EQ(m->attrs.getFirstNamed("key")->getString(), "value"_ss);
    }
    {
        auto par = parseOne<sem::Paragraph>(
            R"({{{partial}})", getDebugFile("broken_macro"));
        // _dbg(sem::exportToTreeString(par, sem::OrgTreeExportOpts{}));
        EXPECT_EQ2(par.size(), 1);
        EXPECT_EQ2(par.at(0)->getKind(), OrgSemKind::ErrorGroup);
        auto err = par.at(0).as<sem::ErrorGroup>();
        EXPECT_EQ2(err.size(), 1);
        EXPECT_EQ2(err->diagnostics.size(), 1);
        EXPECT_EQ2(err.at(0)->getKind(), OrgSemKind::Macro);
        auto m = err.at(0).as<sem::Macro>();
        EXPECT_EQ2(m->name, "partial"_ss);
    }
}

TEST(OrgParseSem, SubtreeTitle) {
    {
        auto t    = parseOne<sem::Subtree>(R"(* Subtree)");
        auto conv = immConv(t);
        auto i    = conv.node;
        EXPECT_EQ(t->getCleanTitle(), "Subtree"_ss);
        EXPECT_EQ(i->getKind(), OrgSemKind::Subtree);
        EXPECT_EQ(i.getCleanTitle(), "Subtree"_ss);
    }

    {
        auto t    = parseOne<sem::Subtree>(R"(* Time [2020-04-20])");
        auto conv = immConv(t);
        auto i    = conv.node;
        EXPECT_EQ(t->getCleanTitle(), "Time [2020-04-20]"_ss);
        EXPECT_EQ(i.getCleanTitle(), "Time [2020-04-20]"_ss);
    }

    {
        auto t    = parseOne<sem::Subtree>(R"(* /Time/)");
        auto conv = immConv(t);
        auto i    = conv.node;
        EXPECT_EQ(t->getCleanTitle(), "Time"_ss);
        EXPECT_EQ(i.getCleanTitle(), "Time"_ss);
    }
}

TEST(OrgParseSem, TestMarkup) {
    Str text{R"(
test /Italic/

/Italic with space/

/*italic bold*/

*Bold*

*Bold with space*

*/bold italic/*

_Underline_

_Underline with space_

_*bold underline*_

~Monospace~

=Verbatim=

+strike+

+strike with space+

@mention

work_with_space

BIG_IDENT

other
)"};

    auto doc = parseOne<sem::Document>(text, getDebugFile("test_markup"));

    auto get = [&](CVec<int> path) {
        auto result = doc.asOrg();
        for (int i : path) { result = result.at(i); }
        return result;
    };

    EXPECT_EQ2(get({1})->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ2(get({1, 2})->getKind(), OrgSemKind::Italic);
    EXPECT_EQ2(get({3, 0})->getKind(), OrgSemKind::Italic);
    EXPECT_EQ2(get({5, 0})->getKind(), OrgSemKind::Italic);
    EXPECT_EQ2(get({5, 0, 0})->getKind(), OrgSemKind::Bold);
    EXPECT_EQ2(get({7, 0})->getKind(), OrgSemKind::Bold);
    EXPECT_EQ2(get({9, 0})->getKind(), OrgSemKind::Bold);
    EXPECT_EQ2(get({11, 0})->getKind(), OrgSemKind::Bold);
    EXPECT_EQ2(get({11, 0, 0})->getKind(), OrgSemKind::Italic);
    EXPECT_EQ2(get({13, 0})->getKind(), OrgSemKind::Underline);
    EXPECT_EQ2(get({15, 0})->getKind(), OrgSemKind::Underline);
    EXPECT_EQ2(get({17, 0})->getKind(), OrgSemKind::Underline);
    EXPECT_EQ2(get({17, 0, 0})->getKind(), OrgSemKind::Bold);
    EXPECT_EQ2(get({19, 0})->getKind(), OrgSemKind::Monospace);
    EXPECT_EQ2(get({19, 0, 0})->getKind(), OrgSemKind::RawText);
    EXPECT_EQ2(get({21, 0})->getKind(), OrgSemKind::Verbatim);
    EXPECT_EQ2(get({21, 0, 0})->getKind(), OrgSemKind::RawText);
    EXPECT_EQ2(get({23, 0})->getKind(), OrgSemKind::Strike);
    EXPECT_EQ2(get({25, 0})->getKind(), OrgSemKind::Strike);
    EXPECT_EQ2(get({27, 0})->getKind(), OrgSemKind::AtMention);
    EXPECT_EQ2(get({29, 0})->getKind(), OrgSemKind::Word);
    EXPECT_EQ2(get({29}).size(), 1);
    EXPECT_EQ2(get({31, 0})->getKind(), OrgSemKind::BigIdent);
    EXPECT_EQ2(get({31}).size(), 1);
}

TEST(OrgParseSem, IncludeCommand) {
    auto get = [&](std::string const& s,
                   Opt<std::string>   debug = std::nullopt) {
        return parseOne<sem::CmdInclude>(s, debug);
    };

    {
        auto i = get(R"(#+include: data.org)");
        EXPECT_EQ(i->path, "data.org"_ss);
    }
    {
        auto i = get(R"(#+include: "data.org")");
        EXPECT_EQ(i->path, "data.org"_ss);
    }
    {
        auto i = get(R"(#+include: "data.org::#custom-id")");
        EXPECT_EQ2(
            i->getIncludeKind(), sem::CmdInclude::Kind::OrgDocument);
        EXPECT_EQ(
            i->getOrgDocument().customIdTarget.value(), "custom-id"_ss);
    }
    {
        auto i = get(R"(#+include: "d.org::* path 1")");
        EXPECT_EQ2(
            i->getIncludeKind(), sem::CmdInclude::Kind::OrgDocument);
        EXPECT_EQ2(i->path, "d.org");
        EXPECT_TRUE(i->getOrgDocument().subtreePath.has_value());
        auto const& p = i->getOrgDocument().subtreePath.value().path;
        EXPECT_EQ(p.size(), 1);
        EXPECT_EQ2(p.at(0), "path 1"_ss);
    }
    {
        auto i = get(R"(#+include: "data.org::* path 1/path 2")");
        EXPECT_EQ2(
            i->getIncludeKind(), sem::CmdInclude::Kind::OrgDocument);
        EXPECT_EQ2(i->path, "data.org");
        EXPECT_TRUE(i->getOrgDocument().subtreePath.has_value());
        auto const& p = i->getOrgDocument().subtreePath.value().path;
        EXPECT_EQ(p.size(), 2);
        EXPECT_EQ2(p.at(0), "path 1"_ss);
        EXPECT_EQ2(p.at(1), "path 2"_ss);
    }

    {
        auto i = get(R"(#+INCLUDE: "~/.emacs" :lines "5-10")");
        EXPECT_EQ(i->firstLine.value(), 5);
        EXPECT_EQ(i->lastLine.value(), 10);
    }
    {
        auto i = get(R"(#+INCLUDE: "~/.emacs" :lines "-10")");
        EXPECT_FALSE(i->firstLine.has_value());
        EXPECT_EQ(i->lastLine.value(), 10);
    }
    {
        auto i = get(R"(#+INCLUDE: "~/.emacs" :lines "10-")");
        EXPECT_EQ(i->firstLine.value(), 10);
        EXPECT_FALSE(i->lastLine.has_value());
    }
    {
        auto i = get(
            R"(#+INCLUDE: "~/my-book/chapter2.org" :minlevel 1)",
            getDebugFile("include_command"));
        EXPECT_EQ(i->getOrgDocument().minLevel, 1);
    }
    {
        auto i = get(
            R"(#+INCLUDE: "./paper.org::#theory" :only-contents t)");
        EXPECT_EQ(i->getOrgDocument().onlyContent.value(), true);
    }
    {
        auto i = get(R"(#+INCLUDE: "~/.emacs" src emacs-lisp)");
        EXPECT_EQ(i->getIncludeKind(), sem::CmdInclude::Kind::Src);
        // EXPECT_EQ(i->getSrc())
    }

    {
        auto i = get(R"(#+INCLUDE: "~/.emacs" custom-name)");
        EXPECT_EQ(i->getIncludeKind(), sem::CmdInclude::Kind::Custom);
        EXPECT_EQ2(i->getCustom().blockName, "custom-name");
    }

    {
        auto i = get(R"(#+INCLUDE: "~/.emacs" ":custom-name")");
        EXPECT_EQ(i->getIncludeKind(), sem::CmdInclude::Kind::Custom);
        EXPECT_EQ2(i->getCustom().blockName, ":custom-name");
    }
}
