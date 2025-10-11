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
)",
        getDebugFile("LinkAttachedGet1"));

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
    org::test::MockFull p{"<test>", true, true};
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


    org::parse::LexerParams params;
    fs::path lex_trace{"/tmp/TraceOperations1_lex_trace.txt"};
    params.setTraceFile(lex_trace);
    params.traceStructured = true;
    p.tokenizeBase(text, params);
    p.tokenizeConvert();
    p.parse();

    auto document = converter
                        .convertDocument(org::parse::OrgAdapter(
                            &p.nodes, org::parse::OrgId(0)))
                        .value();

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
        auto par = parseOne<sem::Paragraph>(
            "[fn:footnote] content",
            getDebugFile("paragraph_body_footnote"));
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
    using NP = sem::NamedProperty;
    {
        auto t = parseOne<sem::Subtree>(
            R"(* Parent capturing statistics
  :PROPERTIES:
  :COOKIE_DATA: todo recursive
  :END:)",
            getDebugFile("cookie_data"));

        auto p = org::getSubtreeProperties<NP::CookieData>(t);
        EXPECT_EQ(p.size(), 1);
        EXPECT_EQ(p.at(0).isRecursive, true);
        EXPECT_EQ(p.at(0).source, SubtreeTodoSource::Todo);
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
            auto olpath = org::getSubtreeProperties<NP::ArchiveOlpath>(
                tree);
            EXPECT_EQ(olpath.size(), 1);
            auto const& p = olpath.at(0).path.path;
            EXPECT_EQ(p.at(0), "Haxorg");
            EXPECT_EQ(p.at(1), "Infrastructure");
            EXPECT_EQ(p.at(2), "Code coverage");
        }

        {
            auto p = org::getSubtreeProperties<NP::ArchiveFile>(tree);
            EXPECT_EQ(p.size(), 1);
            EXPECT_EQ(p.at(0).file, "~/projects.org");
        }


        {
            auto p = org::getSubtreeProperties<NP::ArchiveCategory>(tree);
            EXPECT_EQ(p.size(), 1);
            EXPECT_EQ(p.at(0).category, "projects");
        }
        {
            auto p = org::getSubtreeProperties<NP::ArchiveTodo>(tree);
            EXPECT_EQ(p.size(), 1);
            EXPECT_EQ(p.at(0).todo, "COMPLETED");
        }

        {
            auto p = org::getSubtreeProperties<NP::ArchiveTarget>(tree);
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
            auto p = org::getSubtreeProperties<NP::CustomSubtreeJson>(
                tree);
            EXPECT_EQ(p.size(), 1);
            EXPECT_EQ(p.at(0).name, "name"_ss);
            EXPECT_EQ(p.at(0).value.getField("key").getString(), "value");
        }
        {
            auto p = org::getSubtreeProperties<NP::CustomSubtreeFlags>(
                tree);
            EXPECT_EQ(p.size(), 1);
            EXPECT_EQ(p.at(0).value.getNamedSize(), 1);
            EXPECT_EQ(p.at(0).name, "name"_ss);
            EXPECT_EQ(
                p.at(0).value.getFirstNamed("key")->getString(), "value");
        }
    }

    {
        auto t = parseOne<sem::Subtree>(R"(* tree
:properties:
:prop_json:name_one: [2, 3, 4]
:prop_args:name_other: :key value
:end:
)");
        {
            auto p = t->getProperty("prop_json");
            EXPECT_TRUE(p.has_value());
            EXPECT_EQ2(p->getKind(), NP::Kind::CustomSubtreeJson);
            EXPECT_EQ2(p->getCustomSubtreeJson().name, "nameone");
            EXPECT_EQ2(
                p->getCustomSubtreeJson().value.getRef().dump(),
                "[2,3,4]"_ss);
        }

        {
            auto p = t->getProperty("customsubtreejson");
            EXPECT_TRUE(p.has_value());
            EXPECT_EQ2(p->getKind(), NP::Kind::CustomSubtreeJson);
            EXPECT_EQ2(p->getCustomSubtreeJson().name, "nameone");
            EXPECT_EQ2(
                p->getCustomSubtreeJson().value.getRef().dump(),
                "[2,3,4]"_ss);
        }
        {
            auto p = t->getProperty("prop_args");
            EXPECT_TRUE(p.has_value());
        }
        {
            auto p = t->getProperty("propargs");
            EXPECT_TRUE(p.has_value());
        }
        {
            auto p = t->getProperty("PROP_ARGS");
            EXPECT_TRUE(p.has_value());
        }
    }

    {
        auto t = parseOne<sem::Subtree>(R"(* tree
:properties:
:prop_args:name_other:
:end:
)");
        for (auto const& kind : hstd::Vec<hstd::Str>{
                 "prop_args", "propargs", "PROP_ARGS", "PROPARGS"}) {
            auto p = t->getProperty(kind);
            EXPECT_TRUE(p.has_value());

            for (auto const& subkind : hstd::Vec<hstd::Str>{
                     "nameother",
                     "NAME_OTHER",
                     "NAMEOTHER",
                     "name_other"}) {
                auto p = t->getProperty(kind, subkind);
                EXPECT_TRUE(p.has_value());
            }
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
        auto h = parseOne<sem::HashTag>(
            "#one##[two##[three,four,five]]",
            getDebugFile("hashtag_parse_nested"));
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

TEST(OrgParseSem, TimeParsing) {
    {
        auto t = parseOne<sem::Time>("[2025-12-02]");
        EXPECT_EQ(t->getYear(), 2025);
        EXPECT_EQ(t->getMonth(), 12);
        EXPECT_EQ(t->getDay(), 2);
        EXPECT_TRUE(t->isStatic());
        EXPECT_FALSE(t->isDynamic());
        EXPECT_FALSE(t->isActive);
        EXPECT_EQ(t->getTimeKind(), sem::Time::TimeKind::Static);
    }

    {
        auto t = parseOne<sem::Time>("<2025-12-02>");
        EXPECT_TRUE(t->isActive);
        EXPECT_TRUE(t->isStatic());
    }

    {
        auto t = parseOne<sem::Time>("[2025-12-02 Mon 14:30]");
        EXPECT_EQ(t->getHour(), 14);
        EXPECT_EQ(t->getMinute(), 30);
        EXPECT_EQ(t->getSecond(), std::nullopt);
        auto breakdown = t->getStatic().time.getBreakdown();
        EXPECT_EQ(breakdown.year, 2025);
        EXPECT_EQ(breakdown.month, 12);
        EXPECT_EQ(breakdown.day, 2);
        EXPECT_EQ(breakdown.hour, 14);
        EXPECT_EQ(breakdown.minute, 30);
    }

    {
        auto t = parseOne<sem::Time>("[2025-12-02 +1w]");
        EXPECT_TRUE(t->isStatic());
        auto& static_time = t->getStatic();
        EXPECT_EQ(static_time.repeat.size(), 1);
        EXPECT_EQ(
            static_time.repeat[0].mode, sem::Time::Repeat::Mode::Exact);
        EXPECT_EQ(
            static_time.repeat[0].period, sem::Time::Repeat::Period::Week);
        EXPECT_EQ(static_time.repeat[0].count, 1);
    }

    {
        auto  t           = parseOne<sem::Time>("[2025-12-02 ++1d]");
        auto& static_time = t->getStatic();
        EXPECT_EQ(
            static_time.repeat[0].mode,
            sem::Time::Repeat::Mode::FirstMatch);
        EXPECT_EQ(
            static_time.repeat[0].period, sem::Time::Repeat::Period::Day);
    }

    {
        auto  t           = parseOne<sem::Time>("[2025-12-02 .+1m]");
        auto& static_time = t->getStatic();
        EXPECT_EQ(
            static_time.repeat[0].mode, sem::Time::Repeat::Mode::SameDay);
        EXPECT_EQ(
            static_time.repeat[0].period,
            sem::Time::Repeat::Period::Month);
    }

    {
        auto  t           = parseOne<sem::Time>("[2025-12-02 +1y -3d]");
        auto& static_time = t->getStatic();
        EXPECT_EQ(static_time.repeat.size(), 1);
        EXPECT_TRUE(static_time.warn.has_value());
        EXPECT_EQ(
            static_time.warn->period, sem::Time::Repeat::Period::Day);
        EXPECT_EQ(static_time.warn->count, -3);
    }

    {
        auto t = parseOne<sem::Time>(
            "<%%(diary-anniversary 12 25 1990)>",
            getDebugFile("diary_anniversary"));
        EXPECT_TRUE(t->isDynamic());
        EXPECT_FALSE(t->isStatic());
        EXPECT_EQ(t->getTimeKind(), sem::Time::TimeKind::Dynamic);
        EXPECT_TRUE(t->isActive);
        auto& dynamic_time = t->getDynamic();
        EXPECT_EQ(dynamic_time.expr.getCall().name, "diary-anniversary");
        EXPECT_EQ(
            dynamic_time.expr.getCall().args.at(0).getNumber().value, 12);
        EXPECT_EQ(
            dynamic_time.expr.getCall().args.at(1).getNumber().value, 25);
        EXPECT_EQ(
            dynamic_time.expr.getCall().args.at(2).getNumber().value,
            1990);
    }

    {
        auto t = parseOne<sem::Time>("[%%(diary-anniversary 12 25 1990)]");
        EXPECT_TRUE(t->isDynamic());
        EXPECT_FALSE(t->isStatic());
        EXPECT_EQ(t->getTimeKind(), sem::Time::TimeKind::Dynamic);
        EXPECT_FALSE(t->isActive);
        auto& dynamic_time = t->getDynamic();
        EXPECT_EQ(dynamic_time.expr.getCall().name, "diary-anniversary");
        EXPECT_EQ(
            dynamic_time.expr.getCall().args.at(0).getNumber().value, 12);
        EXPECT_EQ(
            dynamic_time.expr.getCall().args.at(1).getNumber().value, 25);
        EXPECT_EQ(
            dynamic_time.expr.getCall().args.at(2).getNumber().value,
            1990);
    }

    {
        auto tr = parseOne<sem::TimeRange>("[2025-12-02]--[2025-12-03]");
        EXPECT_EQ(tr->getClockedTimeSeconds().value(), 24 * 60 * 60);
        EXPECT_TRUE(tr->from->isStatic());
        EXPECT_TRUE(tr->to->isStatic());
        EXPECT_EQ(tr->from->getDay(), 2);
        EXPECT_EQ(tr->to->getDay(), 3);
    }

    {
        auto tr = parseOne<sem::TimeRange>(
            "[2025-12-02 10:00]--[2025-12-02 15:30]");
        EXPECT_EQ(tr->getClockedTimeSeconds().value(), 5.5 * 60 * 60);
    }

    {
        auto tr = parseOne<sem::TimeRange>(
            "<2025-12-02>--<%%(diary-anniversary 12 25 1990)>");
        EXPECT_TRUE(tr->from->isStatic());
        EXPECT_TRUE(tr->to->isDynamic());
        EXPECT_TRUE(tr->from->isActive);
        EXPECT_TRUE(tr->to->isActive);
        EXPECT_FALSE(tr->getClockedTimeSeconds().has_value());
    }

    {
        auto  t = parseOne<sem::Time>("[2025-12-02 +2w +1m -1d]");
        auto& static_time = t->getStatic();
        EXPECT_EQ(static_time.repeat.size(), 2);
        EXPECT_EQ(
            static_time.repeat[0].period, sem::Time::Repeat::Period::Week);
        EXPECT_EQ(static_time.repeat[0].count, 2);
        EXPECT_EQ(
            static_time.repeat[1].period,
            sem::Time::Repeat::Period::Month);
        EXPECT_EQ(static_time.repeat[1].count, 1);
        EXPECT_TRUE(static_time.warn.has_value());
        EXPECT_EQ(static_time.warn->count, -1);
    }

    {
        auto t = parseOne<sem::Time>("[2025-12-02 14:30:45]");
        EXPECT_EQ(t->getSecond(), 45);
        auto user_time = t->getStaticTime();
        EXPECT_EQ(user_time.align, UserTime::Alignment::Second);
    }

    {
        auto t         = parseOne<sem::Time>("[2025-12-02]");
        auto user_time = t->getStaticTime();
        EXPECT_EQ(user_time.align, UserTime::Alignment::Day);
        EXPECT_FALSE(user_time.zone.has_value());
    }
}

TEST(OrgParseSem, SubtreeLogParsing) {
    {
        auto s = parseOne<sem::Subtree>(
            R"(**** COMPLETED Subtree
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
)",
            getDebugFile("prolog"));
        EXPECT_TRUE(t->deadline.has_value());
        auto d = t->deadline.value()->getStaticTime().getBreakdown();
        EXPECT_EQ(d.day, 15);
        EXPECT_EQ(d.year, 2019);
        EXPECT_EQ(d.month, 12);

        EXPECT_TRUE(t->closed.has_value());
        auto c = t->closed.value()->getStaticTime().getBreakdown();
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
            t->closed.value()->getStaticTime().getBreakdown(),
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
            t->closed.value()->getStaticTime().getBreakdown(),
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
            t->closed.value()->getStaticTime().getBreakdown(),
            (UserTimeBreakdown{
                .year   = 2019,
                .month  = 11,
                .day    = 8,
                .hour   = 19,
                .minute = 35,
            }));

        EXPECT_EQ(
            t->deadline.value()->getStaticTime().getBreakdown(),
            (UserTimeBreakdown{
                .year   = 2019,
                .month  = 11,
                .day    = 7,
                .hour   = 19,
                .minute = 35,
            }));

        EXPECT_EQ(
            t->scheduled.value()->getStaticTime().getBreakdown(),
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
            t->closed.value()->getStaticTime().getBreakdown(),
            (UserTimeBreakdown{
                .year   = 2019,
                .month  = 11,
                .day    = 12,
                .hour   = 19,
                .minute = 35,
            }));

        EXPECT_EQ(
            t->deadline.value()->getStaticTime().getBreakdown(),
            (UserTimeBreakdown{
                .year   = 2019,
                .month  = 11,
                .day    = 13,
                .hour   = 19,
                .minute = 35,
            }));

        EXPECT_EQ(
            t->scheduled.value()->getStaticTime().getBreakdown(),
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

    {
        auto t = parseOne<sem::Subtree>(R"(* TODO Task name)");
        EXPECT_EQ(t->getTodoKeyword().value(), "TODO");
        EXPECT_FALSE(t->isComment);
        EXPECT_FALSE(t->isArchived);
        EXPECT_EQ(t->getCleanTitle(), "TODO Task name"_ss);
    }

    {
        auto t = parseOne<sem::Subtree>(R"(* DONE Completed task)");
        EXPECT_EQ(t->getTodoKeyword().value(), "DONE");
        EXPECT_EQ(t->getCleanTitle(), "DONE Completed task"_ss);
    }

    {
        auto t = parseOne<sem::Subtree>(R"(* IEEE Completed task)");
        EXPECT_EQ(t->getTodoKeyword().value(), "IEEE"_ss);
        EXPECT_EQ(t->getCleanTitle(), "IEEE Completed task"_ss);
    }

    {
        auto t = parseOne<sem::Subtree>(R"(* COMMENT This is a comment)");
        EXPECT_TRUE(t->isComment);
        EXPECT_FALSE(t->getTodoKeyword().has_value());
        EXPECT_EQ(t->getCleanTitle(), "This is a comment");
    }

    {
        auto t = parseOne<sem::Subtree>(R"(* [#A] High priority task)");
        EXPECT_EQ(t->priority.value(), "A");
        EXPECT_EQ(t->getCleanTitle(), "High priority task");
    }

    {
        auto t = parseOne<sem::Subtree>(R"(* [#B] Medium priority task)");
        EXPECT_EQ(t->priority.value(), "B");
    }

    {
        auto t = parseOne<sem::Subtree>(R"(* [#C] Low priority task)");
        EXPECT_EQ(t->priority.value(), "C");
    }

    {
        auto t = parseOne<sem::Subtree>(
            R"(* TODO [#A] Important task [2/5])");
        EXPECT_EQ(t->getTodoKeyword().value(), "TODO");
        EXPECT_EQ(t->priority.value(), "A");
        auto c = t->completion.value();
        EXPECT_EQ(c.done, 2);
        EXPECT_EQ(c.full, 5);
        EXPECT_FALSE(c.isPercent);
        EXPECT_EQ(t->getCleanTitle(), "Important task");
    }

    {
        auto t = parseOne<sem::Subtree>(
            R"(* DONE [#B] Finished work [100%])");
        EXPECT_EQ(t->getTodoKeyword().value(), "DONE");
        EXPECT_EQ(t->priority.value(), "B");
        auto c = t->completion.value();
        EXPECT_EQ(c.done, 100);
        EXPECT_EQ(c.full, 100);
        EXPECT_TRUE(c.isPercent);
    }

    {
        auto t = parseOne<sem::Subtree>(
            R"(* Task with *bold* and /italic/ text)");
        EXPECT_EQ(t->getCleanTitle(), "Task with bold and italic text");
        EXPECT_FALSE(t->getTodoKeyword().has_value());
        EXPECT_FALSE(t->priority.has_value());
        EXPECT_FALSE(t->completion.has_value());
    }

    {
        auto t = parseOne<sem::Subtree>(R"(* Simple title)");
        EXPECT_EQ(t->getCleanTitle(), "Simple title");
        EXPECT_FALSE(t->getTodoKeyword().has_value());
        EXPECT_FALSE(t->priority.has_value());
        EXPECT_FALSE(t->completion.has_value());
        EXPECT_FALSE(t->isComment);
        EXPECT_FALSE(t->isArchived);
    }

    {
        auto t = parseOne<sem::Subtree>(R"(* Title [0/0])");
        auto c = t->completion.value();
        EXPECT_EQ(c.done, 0);
        EXPECT_EQ(c.full, 0);
        EXPECT_FALSE(c.isPercent);
    }

    {
        auto t = parseOne<sem::Subtree>(R"(* Title [0%])");
        auto c = t->completion.value();
        EXPECT_EQ(c.done, 0);
        EXPECT_EQ(c.full, 100);
        EXPECT_TRUE(c.isPercent);
    }

    {
        auto t = parseOne<sem::Subtree>(R"(* Title [100%])");
        auto c = t->completion.value();
        EXPECT_EQ(c.done, 100);
        EXPECT_EQ(c.full, 100);
        EXPECT_TRUE(c.isPercent);
    }

    {
        auto t = parseOne<sem::Subtree>(R"(* Title [10/10])");
        auto c = t->completion.value();
        EXPECT_EQ(c.done, 10);
        EXPECT_EQ(c.full, 10);
        EXPECT_FALSE(c.isPercent);
    }

    {
        auto t = parseOne<sem::Subtree>(
            R"(* COMMENT TODO This should be comment)");
        EXPECT_TRUE(t->isComment);
        EXPECT_TRUE(t->getTodoKeyword().has_value());
        EXPECT_EQ(t->getTodoKeyword().value(), "TODO");
        EXPECT_EQ(t->getCleanTitle(), "TODO This should be comment");
    }

    {
        auto t = parseOne<sem::Subtree>(R"(* Title :tag1:tag2:)");
        EXPECT_EQ(t->tags.size(), 2);
        EXPECT_EQ(t->tags.at(0)->text.head, "tag1"_ss);
        EXPECT_EQ(t->tags.at(1)->text.head, "tag2"_ss);
        EXPECT_EQ(t->getCleanTitle(), "Title"_ss);
    }

    {
        auto t = parseOne<sem::Subtree>(R"(* Title :ARCHIVE:)");
        EXPECT_TRUE(t->isArchived);
        EXPECT_EQ(t->tags.size(), 0);
    }

    {
        auto t = parseOne<sem::Subtree>(
            R"(* Title :work:urgent:ARCHIVE:)");
        EXPECT_TRUE(t->isArchived);
        EXPECT_EQ(t->tags.size(), 2);
        EXPECT_EQ(t->tags.at(0)->text.head, "work"_ss);
        EXPECT_EQ(t->tags.at(1)->text.head, "urgent"_ss);
    }

    {
        auto t = parseOne<sem::Subtree>(
            R"(* TODO [#A] Important task [2/5] :work:urgent:)",
            getDebugFile("subtree/a"));
        EXPECT_EQ(t->todo.value(), "TODO");
        EXPECT_EQ(t->priority.value(), "A");
        auto c = t->completion.value();
        EXPECT_EQ(c.done, 2);
        EXPECT_EQ(c.full, 5);
        EXPECT_EQ(t->tags.size(), 2);
        EXPECT_EQ(t->tags.at(0)->text.head, "work"_ss);
        EXPECT_EQ(t->tags.at(1)->text.head, "urgent"_ss);
        EXPECT_EQ(t->getCleanTitle(), "Important task");
    }

    {
        auto t = parseOne<sem::Subtree>(
            R"(* COMMENT Task with tags :comment:test:)");
        EXPECT_TRUE(t->isComment);
        EXPECT_EQ(t->tags.size(), 2);
        EXPECT_EQ(t->tags.at(0)->text.head, "comment"_ss);
        EXPECT_EQ(t->tags.at(1)->text.head, "test"_ss);
        EXPECT_EQ(t->getCleanTitle(), "Task with tags");
    }

    {
        auto t = parseOne<sem::Subtree>(
            R"(* DONE [#B] Finished work [100%] :project:ARCHIVE:)");
        EXPECT_EQ(t->todo.value(), "DONE"_ss);
        EXPECT_EQ(t->priority.value(), "B"_ss);
        EXPECT_TRUE(t->isArchived);
        auto c = t->completion.value();
        EXPECT_EQ(c.done, 100);
        EXPECT_TRUE(c.isPercent);
        EXPECT_EQ(t->tags.size(), 1);
        EXPECT_EQ(t->tags.at(0)->text.head, "project"_ss);
    }

    {
        auto t = parseOne<sem::Subtree>(R"(* Title :single:)");
        EXPECT_EQ(t->tags.size(), 1);
        EXPECT_EQ(t->tags.at(0)->text.head, "single"_ss);
    }

    {
        auto t = parseOne<sem::Subtree>(
            R"(* Title with *markup* :tag1:tag2:tag3:)");
        EXPECT_EQ(t->getCleanTitle(), "Title with markup");
        EXPECT_EQ(t->tags.size(), 3);
        EXPECT_EQ(t->tags.at(0)->text.head, "tag1"_ss);
        EXPECT_EQ(t->tags.at(1)->text.head, "tag2"_ss);
        EXPECT_EQ(t->tags.at(2)->text.head, "tag3"_ss);
    }

    {
        auto t = parseOne<sem::Subtree>(
            R"(* Title with *markup* :tag1:nested##tag:tag3##complex##nested:)");
        EXPECT_EQ(t->getCleanTitle(), "Title with markup"_ss);
        EXPECT_EQ(t->tags.size(), 3);
        EXPECT_EQ(t->tags.at(0)->text.head, "tag1"_ss);
        EXPECT_EQ(t->tags.at(1)->text.head, "nested"_ss);
        EXPECT_EQ(t->tags.at(1)->text.subtags.at(0).head, "tag"_ss);

        EXPECT_EQ(t->tags.at(2)->text.head, "tag3"_ss);
        EXPECT_EQ(t->tags.at(2)->text.subtags.at(0).head, "complex"_ss);
        EXPECT_EQ(
            t->tags.at(2)->text.subtags.at(0).subtags.at(0).head,
            "nested"_ss);
    }
    {
        auto t = parseOne<sem::Subtree>(
            R"(* Title with *:tag_feint:* :tag1:nested##tag:tag3##complex##nested:)");
        EXPECT_EQ(t->getCleanTitle(), "Title with :tag_feint:");
        EXPECT_EQ(t->tags.size(), 3);
        EXPECT_EQ(t->tags.at(0)->text.head, "tag1"_ss);
        EXPECT_EQ(t->tags.at(1)->text.head, "nested"_ss);
        EXPECT_EQ(t->tags.at(1)->text.subtags.at(0).head, "tag"_ss);

        EXPECT_EQ(t->tags.at(2)->text.head, "tag3"_ss);
        EXPECT_EQ(t->tags.at(2)->text.subtags.at(0).head, "complex"_ss);
        EXPECT_EQ(
            t->tags.at(2)->text.subtags.at(0).subtags.at(0).head,
            "nested"_ss);
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
        EXPECT_EQ(par.size(), 5);
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
        auto        l = parseOne<sem::Link>(R"([[* Title]])");
        auto const& t = l->target;
        EXPECT_EQ(t.getKind(), sem::LinkTarget::Kind::SubtreeTitle);
        EXPECT_EQ(t.getSubtreeTitle().level, 1);
        EXPECT_EQ(t.getSubtreeTitle().title.path.size(), 1);
        EXPECT_EQ(t.getSubtreeTitle().title.path.at(0), "Title");
    }
    {
        auto        l = parseOne<sem::Link>(R"([[** Title/Sub]])");
        auto const& t = l->target;
        EXPECT_EQ(t.getKind(), sem::LinkTarget::Kind::SubtreeTitle);
        EXPECT_EQ(t.getSubtreeTitle().level, 2);
        EXPECT_EQ(t.getSubtreeTitle().title.path.size(), 2);
        EXPECT_EQ(t.getSubtreeTitle().title.path.at(0), "Title");
        EXPECT_EQ(t.getSubtreeTitle().title.path.at(1), "Sub");
    }
    {
        auto        l = parseOne<sem::Link>(R"([[#custom-id]])");
        auto const& t = l->target;
        EXPECT_EQ(t.getKind(), sem::LinkTarget::Kind::CustomId);
        EXPECT_EQ(t.getCustomId().text, "custom-id");
    }
    {
        auto l = parseOne<sem::Link>(
            R"([[file:random-path.pdf]])", getDebugFile("file_link"));
        auto const& t = l->target;
        EXPECT_EQ2(t.getKind(), sem::LinkTarget::Kind::File);
        EXPECT_EQ(t.getFile().file, "random-path.pdf");
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
        EXPECT_EQ(attrs1.getAttrs("cache").at(0).getString(), "yes");
        EXPECT_EQ(attrs1.getAttrs("cache").at(0).getBool(), true);

        auto h2     = t2->getProperty("header-args");
        auto attrs2 = h2.value().getCustomArgs().attrs;
        EXPECT_TRUE(h2.has_value());
        EXPECT_EQ(attrs2.getAttrs("results").size(), 1);
        EXPECT_EQ(
            attrs2.getAttrs("results").at(0).name.value(), "results");
        EXPECT_EQ(attrs2.getAttrs("results").at(0).getString(), "silent");

        auto stacked = org::getFinalProperty({t1, t2}, "header-args");
        EXPECT_TRUE(stacked.has_value());
        auto s = stacked.value();
        EXPECT_EQ(
            s.getCustomArgs().attrs.getAttrs("results").at(0).getString(),
            "silent");

        EXPECT_EQ(
            s.getCustomArgs().attrs.getAttrs("cache").at(0).getString(),
            "yes");
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
        auto m = parseOne<sem::Macro>(
            R"({{{dashed-name}}})", getDebugFile("macro_dashed_name"));
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
        auto m = parseOne<sem::Macro>(
            R"({{{named(key=value)}}})", getDebugFile("dash_name"));
        EXPECT_EQ(m->name, "named"_ss);
        EXPECT_EQ(m->attrs.getPositionalSize(), 1);
        EXPECT_EQ(m->attrs.getNamedSize(), 0);
        EXPECT_EQ(m->attrs.getPositional(0)->getString(), "value"_ss);
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
        auto i = get(
            R"(#+include: data.org)",
            getDebugFile("include_command_item"));
        EXPECT_EQ2(i->path, "data.org"_ss);
    }
    {
        auto i = get(R"(#+include: "data.org")");
        EXPECT_EQ2(i->path, "data.org"_ss);
    }
    {
        auto i = get(R"(#+include: "data.org::#custom-id")");
        EXPECT_EQ2(
            i->getIncludeKind(), sem::CmdInclude::Kind::OrgDocument);
        EXPECT_EQ2(
            i->getOrgDocument().customIdTarget.value(), "custom-id"_ss);
    }
    {
        auto i = get(R"(#+include: "d.org::* path 1")");
        EXPECT_EQ2(
            i->getIncludeKind(), sem::CmdInclude::Kind::OrgDocument);
        EXPECT_EQ2(i->path, "d.org");
        EXPECT_TRUE(i->getOrgDocument().subtreePath.has_value());
        auto const& p = i->getOrgDocument().subtreePath.value().path;
        EXPECT_EQ2(p.size(), 1);
        EXPECT_EQ2(p.at(0), "path 1"_ss);
    }
    {
        auto i = get(R"(#+include: "data.org::* path 1/path 2")");
        EXPECT_EQ2(
            i->getIncludeKind(), sem::CmdInclude::Kind::OrgDocument);
        EXPECT_EQ2(i->path, "data.org");
        EXPECT_TRUE(i->getOrgDocument().subtreePath.has_value());
        auto const& p = i->getOrgDocument().subtreePath.value().path;
        EXPECT_EQ2(p.size(), 2);
        EXPECT_EQ2(p.at(0), "path 1"_ss);
        EXPECT_EQ2(p.at(1), "path 2"_ss);
    }

    {
        auto i = get(
            R"(#+INCLUDE: "~/.emacs" :lines "5-10")",
            getDebugFile("include_qith_quotes"));
        EXPECT_EQ2(i->firstLine.value(), 5);
        EXPECT_EQ2(i->lastLine.value(), 10);
    }
    {
        auto i = get(R"(#+INCLUDE: "~/.emacs" :lines "-10")");
        EXPECT_FALSE(i->firstLine.has_value());
        EXPECT_EQ2(i->lastLine.value(), 10);
    }
    {
        auto i = get(R"(#+INCLUDE: "~/.emacs" :lines "10-")");
        EXPECT_EQ2(i->firstLine.value(), 10);
        EXPECT_FALSE(i->lastLine.has_value());
    }
    {
        auto i = get(
            R"(#+INCLUDE: "~/my-book/chapter2.org" :minlevel 1)",
            getDebugFile("include_command"));
        EXPECT_EQ2(i->getOrgDocument().minLevel, 1);
    }
    {
        auto i = get(
            R"(#+INCLUDE: "./paper.org::#theory" :only-contents t)");
        EXPECT_EQ2(i->getOrgDocument().onlyContent.value(), true);
    }
    {
        auto i = get(R"(#+INCLUDE: "~/.emacs" src emacs-lisp)");
        EXPECT_EQ2(i->getIncludeKind(), sem::CmdInclude::Kind::Src);
        // EXPECT_EQ2(i->getSrc())
    }

    {
        auto i = get(R"(#+INCLUDE: "~/.emacs" custom-name)");
        EXPECT_EQ2(i->getIncludeKind(), sem::CmdInclude::Kind::Custom);
        EXPECT_EQ2(i->getCustom().blockName, "custom-name");
    }

    {
        auto i = get(
            R"(#+INCLUDE: "~/.emacs" ":custom-name")",
            getDebugFile("quoted_custom_name"));
        EXPECT_EQ2(i->getIncludeKind(), sem::CmdInclude::Kind::Custom);
        EXPECT_EQ2(i->getCustom().blockName, ":custom-name");
    }
}

TEST(OrgParseSem, CodeBlockVariables) {
    auto get = [&](std::string const& s,
                   Opt<std::string>   debug = std::nullopt) {
        return parseOne<sem::BlockCode>(s, debug);
    };
    {
        auto c = get(
            R"(#+BEGIN_SRC emacs-lisp :var table=example-table
  (length table)
#+END_SRC)",
            getDebugFile("example-table"));
        EXPECT_EQ2(c->getVariable("table")->getString(), "example-table");
    }
    {
        auto c = get(
            R"(#+BEGIN_SRC emacs-lisp :var data=example-table[0,-1]
  data
#+END_SRC)");
        EXPECT_EQ2(c->getVariable("data")->getString(), "example-table");
        auto span = c->getVariable("data")->span;
        EXPECT_EQ2(span.size(), 2);
        EXPECT_EQ2(span.at(0).first, 0);
        EXPECT_FALSE(span.at(0).last.has_value());
        EXPECT_EQ(span.at(1).first, -1);
        EXPECT_FALSE(span.at(1).last.has_value());
    }
    {
        auto c = get(R"(#+BEGIN_SRC emacs-lisp :var data=example-table[1:3]
  data
#+END_SRC)");
        auto span = c->getVariable("data")->span;
        EXPECT_EQ(span.at(0).first, 1);
        EXPECT_EQ(span.at(0).last.value(), 3);
    }
    {
        auto c = get(
            R"(#+BEGIN_SRC emacs-lisp :var data=3D[1,,1]
  data
#+END_SRC)",
            getDebugFile("empty_content_slice"));
        auto span = c->getVariable("data")->span;
        EXPECT_EQ(span.size(), 3);
        EXPECT_EQ(span.at(0).first, 1);
        EXPECT_FALSE(span.at(0).last.has_value());
        EXPECT_EQ(span.at(1).first, 0);
        EXPECT_EQ(span.at(1).last.value(), -1);
        EXPECT_EQ(span.at(2).first, 1);
        EXPECT_FALSE(span.at(2).last.has_value());
    }
    {
        auto c   = get(R"(#+BEGIN_SRC emacs-lisp :var NAME=FILE:REFERENCE
  data
#+END_SRC)");
        auto var = c->getVariable("NAME");
        EXPECT_TRUE(var->isFileReference());
        EXPECT_EQ(var->varname, "NAME");
        EXPECT_EQ(var->getFileReference().file, "FILE");
        EXPECT_EQ(var->getFileReference().reference, "REFERENCE");
    }
}

TEST(OrgParseSem, CodeBlockEval) {
    auto get = [](std::string const&         code,
                  hstd::Opt<fs::path> const& path = std::nullopt)
        -> sem::OrgCodeEvalInput {
        org::OrgCodeEvalParameters conf;
        Vec<sem::OrgCodeEvalInput> buf;
        auto doc = path ? testParseString(code, path->native())
                        : testParseString(code);

        conf.evalBlock = [&](sem::OrgCodeEvalInput const& in)
            -> Vec<sem::OrgCodeEvalOutput> {
            buf.push_back(in);
            return {sem::OrgCodeEvalOutput{.stdoutText = ""}};
        };
        if (path) { conf.debug->setTraceFile(path.value()); }
        auto ev = org::evaluateCodeBlocks(doc, conf);
        return buf.at(0);
    };
    {
        auto i = get(R"(#+begin_src python
content
#+end_src)");
        EXPECT_EQ(i.language, "python"_ss);
    }
    {
        auto i = get(R"(#+begin_src python :results table
content
#+end_src)");
        EXPECT_EQ2(
            i.resultType, org::sem::OrgCodeEvalInput::ResultType::Table);
    }

    {
        auto i = get(R"(#+begin_src python :results list
content
#+end_src)");
        EXPECT_EQ2(
            i.resultType, org::sem::OrgCodeEvalInput::ResultType::List);
    }

    {
        auto i = get(R"(#+begin_src python :results scalar
content
#+end_src)");
        EXPECT_EQ2(
            i.resultType, org::sem::OrgCodeEvalInput::ResultType::Scalar);
    }

    {
        auto i = get(R"(#+begin_src python :results file
content
#+end_src)");
        EXPECT_EQ2(
            i.resultType,
            org::sem::OrgCodeEvalInput::ResultType::SaveFile);
    }

    {
        auto i = get(R"(#+begin_src python :results raw
content
#+end_src)");
        EXPECT_EQ2(
            i.resultFormat, org::sem::OrgCodeEvalInput::ResultFormat::Raw);
    }

    {
        auto i = get(R"(#+begin_src python :results code
content
#+end_src)");
        EXPECT_EQ2(
            i.resultFormat,
            org::sem::OrgCodeEvalInput::ResultFormat::Code);
    }

    {
        auto i = get(R"(#+begin_src python :results drawer
content
#+end_src)");
        EXPECT_EQ2(
            i.resultFormat,
            org::sem::OrgCodeEvalInput::ResultFormat::Drawer);
    }

    {
        auto i = get(R"(#+begin_src python :results html
content
#+end_src)");
        EXPECT_EQ2(
            i.resultFormat,
            org::sem::OrgCodeEvalInput::ResultFormat::ExportType);
        EXPECT_EQ2(i.exportType.value(), "html");
    }

    {
        auto i = get(R"(#+begin_src python :results replace
content
#+end_src)");
        EXPECT_EQ2(
            i.resultHandling,
            org::sem::OrgCodeEvalInput::ResultHandling::Replace);
    }

    {
        auto i = get(R"(#+begin_src python :results silent
content
#+end_src)");
        EXPECT_EQ2(
            i.resultHandling,
            org::sem::OrgCodeEvalInput::ResultHandling::Silent);
    }

    {
        auto i = get(R"(#+begin_src python :results append
content
#+end_src)");
        EXPECT_EQ2(i.language, "python"_ss);
        EXPECT_EQ2(
            i.resultHandling,
            org::sem::OrgCodeEvalInput::ResultHandling::Append);
    }

    {
        auto i = get(R"(#+begin_src python :results prepend
content
#+end_src)");
        EXPECT_EQ2(
            i.resultHandling,
            org::sem::OrgCodeEvalInput::ResultHandling::Prepend);
    }

    {
        auto i = get(R"(#+begin_src python :var x=10 :var name="test"
content
#+end_src)");
        EXPECT_EQ2(i.argList.size(), 2);
        EXPECT_EQ2(i.getVariable("x").value().value.getString(), "10"_ss);
        EXPECT_EQ2(
            i.getVariable("name").value().value.getString(), "test"_ss);
    }

    {
        auto i = get(R"(#+begin_src python
print("hello")
x = 42
#+end_src)");
        EXPECT_EQ2(i.tangledCode, "print(\"hello\")\nx = 42");
    }

    {
        auto i = get(R"(#+begin_src
no language
#+end_src)");
        EXPECT_EQ2(i.language, "");
        EXPECT_EQ2(
            i.resultType, org::sem::OrgCodeEvalInput::ResultType::Scalar);
        EXPECT_EQ2(
            i.resultFormat,
            org::sem::OrgCodeEvalInput::ResultFormat::None);
        EXPECT_EQ2(
            i.resultHandling,
            org::sem::OrgCodeEvalInput::ResultHandling::Replace);
    }

    {
        auto i = get(R"(#+begin_src python :tangle file.py :noweb yes
content
#+end_src)");
        EXPECT_EQ(i.blockAttrs.positional.items.size(), 0);
    }
}

TEST(OrgParseSem, CodeBlockBody) {
    {
        auto c = parseOne<sem::BlockCode>(R"(#+BEGIN_SRC python
print("hello world")
#+END_SRC)");
        EXPECT_EQ2(c->lang.value(), "python");
        EXPECT_EQ2(c->lines.size(), 1);
        EXPECT_EQ2(c->lines[0].parts.size(), 1);
        EXPECT_TRUE(c->lines[0].parts[0].isRaw());
    }
    {
        auto c = parseOne<sem::BlockCode>(
            R"(#+BEGIN_SRC python :cache yes
print("test")
#+END_SRC)");
        EXPECT_TRUE(c->getFirstAttrBool("cache").value());
    }

    {
        auto c = parseOne<sem::BlockCode>(
            R"(#+BEGIN_SRC python :eval no
print("test")
#+END_SRC)");
        EXPECT_FALSE(c->getFirstAttrBool("eval").value());
    }

    {
        auto c = parseOne<sem::BlockCode>(R"(#+BEGIN_SRC python :noweb yes
print("test")
#+END_SRC)");
        EXPECT_TRUE(c->getFirstAttrBool("noweb"));
    }

    {
        auto c = parseOne<sem::BlockCode>(
            R"(#+BEGIN_SRC python :tangle file.py
print("test")
#+END_SRC)");
        EXPECT_EQ(c->getFirstAttrString("tangle"), "file.py"_ss);
    }

    {
        auto c = parseOne<sem::BlockCode>(R"(#+BEGIN_SRC
line1
line2
line3
#+END_SRC)");
        EXPECT_EQ2(c->lines.size(), 3);
        EXPECT_FALSE(c->lang.has_value());
    }

    {
        auto c = parseOne<sem::BlockCode>(
            R"(#+BEGIN_SRC python :var x=10 :var y=20
print(x + y)
#+END_SRC)");
        EXPECT_EQ2(c->getVariable("x")->getString(), "10");
        EXPECT_EQ2(c->getVariable("y")->getString(), "20");
        EXPECT_FALSE(c->getVariable("z").has_value());
    }

    {
        auto c = parseOne<sem::BlockCode>(R"(#+BEGIN_SRC
#+END_SRC)");
        EXPECT_EQ2(c->lines.size(), 0);
        EXPECT_EQ2(c->result.size(), 0);
    }
}

TEST(OrgParseSem, CodeBlockResults) {
    {
        auto c = parseOne<sem::BlockCode>(R"(#+BEGIN_SRC python
print("hello")
#+END_SRC

#+RESULTS:
: hello)");
        EXPECT_EQ2(c->result.size(), 1);
        auto result = c->result[0].get();
        EXPECT_EQ2(result->node->getKind(), OrgSemKind::ColonExample);
    }

    {
        auto c = parseOne<sem::BlockCode>(
            R"(#+BEGIN_SRC python
import matplotlib.pyplot as plt
plt.plot([1,2,3])
plt.savefig('plot.png')
#+END_SRC

#+RESULTS:
[[file:plot.png]])");
        EXPECT_EQ2(c->result.size(), 1);
        auto result = c->result[0].get();
        EXPECT_EQ2(result->node->getKind(), OrgSemKind::Link);
    }

    {
        auto c = parseOne<sem::BlockCode>(R"(#+BEGIN_SRC python
data = [[1, 2], [3, 4]]
print(data)
#+END_SRC

#+RESULTS:
| 1 | 2 |
| 3 | 4 |)");
        EXPECT_EQ2(c->result.size(), 1);
        auto result = c->result[0].get();
        EXPECT_EQ2(result->node->getKind(), OrgSemKind::Table);
    }

    {
        auto c = parseOne<sem::BlockCode>(R"(#+BEGIN_SRC python
print("line1")
print("line2")
#+END_SRC

#+RESULTS:
#+begin_example
line1
line2
#+end_example)");
        EXPECT_EQ2(c->result.size(), 1);
        auto result = c->result[0].get();
        EXPECT_EQ2(result->node->getKind(), OrgSemKind::BlockExample);
    }

    {
        auto c = parseOne<sem::BlockCode>(R"(#+BEGIN_SRC python
def hello():
    return "world"
#+END_SRC

#+RESULTS:
#+begin_src python
def hello():
    return "world"
#+end_src)");
        EXPECT_EQ2(c->result.size(), 1);
        auto result = c->result[0].get();
        EXPECT_EQ2(result->node->getKind(), OrgSemKind::BlockCode);
    }

    {
        auto c = parseOne<sem::BlockCode>(R"(#+BEGIN_SRC python
print("no results")
#+END_SRC)");
        EXPECT_EQ2(c->result.size(), 0);
    }

    {
        auto doc = parseOne<sem::Document>(
            R"(#+BEGIN_SRC python
print("first")
#+END_SRC

#+RESULTS:
: first

#+BEGIN_SRC python
print("second")
#+END_SRC

#+RESULTS:
: second)");
        auto c0 = doc.at(0).as<sem::BlockCode>();
        auto c1 = doc.at(2).as<sem::BlockCode>();
        EXPECT_EQ(c0->result.size(), 1);
        EXPECT_EQ(c1->result.size(), 1);
    }
}

TEST(OrgParseSem, CmdCallNode) {
    auto get = [&](std::string const& s,
                   Opt<std::string>   debug = std::nullopt) {
        return parseOne<sem::CmdCall>(s, debug);
    };
    {
        auto c = get(
            R"(#+call: docker-swarm-systemd-configure[:dir (docker:infra-ssh "docker-swarm-0")](nodes=process42-node-table[2:-1],graph=process42-graph[2:-1],arg=(elisp-eval (something))) :results silent)",
            getDebugFile("CmdCallNode"));

        auto ea = c->endHeaderAttrs;
        auto ha = c->insideHeaderAttrs;
        auto ca = c->callAttrs;
        EXPECT_EQ(ea.getNamedSize(), 1);
        EXPECT_EQ(ea.getFirstNamed("results")->getString(), "silent");

        EXPECT_EQ(ha.getNamedSize(), 1);
        EXPECT_TRUE(ha.getFirstNamed("dir")->isLispValue());
        auto dir = ha.getFirstNamed("dir").value().getLispValue().code;
        EXPECT_TRUE(dir.isCall());
        EXPECT_EQ2(dir.getCall().name, "docker:infra-ssh");
        EXPECT_EQ2(
            dir.getCall().args.at(0).getText().value, "docker-swarm-0");

        EXPECT_EQ(ca.getPositionalSize(), 3);
        auto ca1 = ca.getPositional(0);
        auto ca2 = ca.getPositional(1);
        auto ca3 = ca.getPositional(2);

        EXPECT_EQ2(ca1->varname.value(), "nodes");
        EXPECT_EQ2(ca2->varname.value(), "graph");
        EXPECT_EQ2(ca3->varname.value(), "arg");
        EXPECT_FALSE(ca1->name.has_value());
        EXPECT_FALSE(ca2->name.has_value());
        EXPECT_FALSE(ca3->name.has_value());
        EXPECT_EQ2(ca1.value().getString(), "process42-node-table"_ss);
        EXPECT_EQ2(ca1->span.at(0).first, 2);
        EXPECT_EQ2(ca1->span.at(0).last.value(), -1);
        EXPECT_EQ2(ca2.value().getString(), "process42-graph"_ss);
        EXPECT_EQ2(ca2->span.at(0).first, 2);
        EXPECT_EQ2(ca2->span.at(0).last.value(), -1);

        auto el = ca3->getLispValue().code;
        EXPECT_TRUE(el.isCall());
        EXPECT_EQ2(el.getCall().name, "elisp-eval"_ss);
        EXPECT_TRUE(el.getCall().args.at(0).isCall());
        EXPECT_EQ2(el.getCall().args.at(0).getCall().name, "something"_ss);
    }
}

TEST(OrgParseSem, DocumentFragments) {
    auto opts = OrgParseParameters::shared();
    opts->getFragments =
        [](std::string const& text) -> Vec<OrgParseFragment> {
        return org::extractCommentBlocks(text, {"//#"});
    };

    opts->semTracePath       = getDebugFile("sem_trace.log");
    opts->parseTracePath     = getDebugFile("parse_trace.log");
    opts->tokenTracePath     = getDebugFile("token_trace.log");
    opts->baseTokenTracePath = getDebugFile("base_token_trace.log");

    auto node = org::parseStringOpts(
        R"(
struct [[refl]] OrgParseFragment {
    //# Documenting with org-mode comments
    //# Multiline string will be joined into a single fragment
    [[refl]] int         baseLine;
    //# #+name: named-paragraph-reference-base-col-field
    //# Document fragment can have a named paragraph
    [[refl]] int         baseCol;
    [[refl]] std::string text;
    //# Referencing [[named-paragraph-reference-base-col-field]]
    DESC_FIELDS(OrgParseFragment, (baseLine, baseCol, text));
};
)",
        opts);

    writeTreeRepr(node, getDebugFile("parsed.yaml"));
}


TEST(OrgParseSem, CriticMarkup) {
    auto get = [&](std::string const& s,
                   Opt<std::string>   debug = std::nullopt) {
        return parseOne<sem::CriticMarkup>(s, debug);
    };
    { auto n = get(R"({--is --})", getDebugFile("delete")); }
    { auto n = get(R"({++is ++})"); }
    { auto n = get(R"({~~a~>b~~})"); }
    { auto n = get(R"({==is==})"); }
    { auto n = get(R"({>>is<<})"); }
}
