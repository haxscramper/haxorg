#include "tOrgFuzzUtils.hpp"
#include "tOrgFuzzDomains.hpp"

Domain<prt::AnyNode> GenerateAnyRawText(
    CR<GenerateNodeContext> ctx,
    Domain<std::string>     filler) {
    return GenerateAnyNodeWrapper( //
        Domain<prt::RawText>(
            InitLeaf<prt::RawText>(ctx).WithOptionalStringField(
                "text", AlwaysSet(filler))));
}

Domain<std::vector<prt::AnyNode>> SpacedSubDomain(
    CR<GenerateNodeContext> ctx) {
    return GenerateInterspersedNodes(
        ctx, ctx.generateDomain(), ctx.generateDomain(osk::Space));
}

template <>
Domain<prt::Caption> GenerateNode<prt::Caption>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug("Caption");
    return InitNode<prt::Caption>(ctx) //
        .WithOptionalProtobufField(
            "text",
            AlwaysSet(GenerateNode<prt::Paragraph>(
                ctx.withRelativeRecursionLimit(2).rec(osk::Caption))))
        .WithRepeatedFieldMaxSize("subnodes", 0);
}

template <>
Domain<prt::FileTarget> GenerateNode<prt::FileTarget>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug("FileTarget");
    return InitNode<prt::FileTarget>(ctx).WithRepeatedFieldMaxSize(
        "subnodes", 0);
}

template <>
Domain<prt::SubtreeLog> GenerateNode<prt::SubtreeLog>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug("SubtreeLog");
    return InitNode<prt::SubtreeLog>(ctx).WithRepeatedFieldMaxSize(
        "subnodes", 0);
}

template <>
Domain<prt::DocumentGroup> GenerateNode<prt::DocumentGroup>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug("DocumentGroup");
    return InitNode<prt::DocumentGroup>(ctx).WithRepeatedFieldMaxSize(
        "subnodes", 0);
}

template <>
Domain<prt::Tblfm> GenerateNode<prt::Tblfm>(CR<GenerateNodeContext> ctx) {
    ctx.debug("Tblfm");
    return InitNode<prt::Tblfm>(ctx).WithRepeatedFieldMaxSize(
        "subnodes", 0);
}

template <>
Domain<prt::Monospace> GenerateNode<prt::Monospace>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug("Monospace");
    return InitNode<prt::Monospace>(ctx) //
        .WithRepeatedProtobufField(
            "subnodes",
            VectorOf(GenerateAnyRawText(ctx, LowerIdent())).WithSize(1));
}

template <>
Domain<prt::Completion> GenerateNode<prt::Completion>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug("Completion");
    return InitNode<prt::Completion>(ctx) //
        .WithOptionalInt32Field("done", AlwaysSet(NonNegative<int>()))
        .WithOptionalInt32Field("full", AlwaysSet(NonNegative<int>()))
        .WithRepeatedFieldMaxSize("subnodes", 0);
}

template <>
Domain<prt::Code> GenerateNode<prt::Code>(CR<GenerateNodeContext> ctx) {
    ctx.debug("Code");
    return InitNode<prt::Code>(ctx).WithRepeatedFieldMaxSize(
        "subnodes", 0);
}

template <>
Domain<prt::StmtList> GenerateNode<prt::StmtList>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug("StmtList");
    return InitNode<prt::StmtList>(ctx).WithRepeatedFieldMaxSize(
        "subnodes", 0);
}

template <>
Domain<prt::Punctuation> GenerateNode<prt::Punctuation>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug("Punctuation");
    return InitLeaf<prt::Punctuation>(ctx) //
        .WithOptionalStringField(
            "text", AlwaysSet(ElementOf<std::string>({"?", "!", ","})));
}

template <>
Domain<prt::Export> GenerateNode<prt::Export>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug("Export");
    return InitNode<prt::Export>(ctx).WithRepeatedFieldMaxSize(
        "subnodes", 0);
}

template <>
Domain<prt::Table> GenerateNode<prt::Table>(CR<GenerateNodeContext> ctx) {
    ctx.debug("Table");
    return InitNode<prt::Table>(ctx).WithRepeatedFieldMaxSize(
        "subnodes", 0);
}

template <>
Domain<prt::CmdArgument> GenerateNode<prt::CmdArgument>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug("CmdArgument");
    return InitNode<prt::CmdArgument>(ctx).WithRepeatedFieldMaxSize(
        "subnodes", 0);
}

template <>
Domain<prt::Footnote> GenerateNode<prt::Footnote>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug("Footnote");
    return InitNode<prt::Footnote>(ctx) //
        .WithOptionalStringField("tag", AlwaysSet(LowerIdent()))
        .WithProtobufField(
            "definition",
            GenerateAnyNodeWrapper(GenerateNode<prt::Paragraph>(
                ctx.withRelativeRecursionLimit(1).rec(osk::Footnote))))
        .WithRepeatedFieldMaxSize("subnodes", 0);
}

template <>
Domain<prt::Row> GenerateNode<prt::Row>(CR<GenerateNodeContext> ctx) {
    ctx.debug("Row");
    return InitNode<prt::Row>(ctx).WithRepeatedFieldMaxSize("subnodes", 0);
}

template <>
Domain<prt::InlineMath> GenerateNode<prt::InlineMath>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug("InlineMath");
    return InitNode<prt::InlineMath>(ctx) //
        .WithRepeatedProtobufField(
            "subnodes",
            VectorOf(GenerateAnyRawText(ctx, LowerIdent())).WithSize(1));
}

template <>
Domain<prt::Escaped> GenerateNode<prt::Escaped>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug("Escaped");
    return InitLeaf<prt::Escaped>(ctx).WithOptionalStringField(
        "text", AlwaysSet(InRegexp(R"([a-zA-Z0-9\\//.,()])")));
}

template <>
Domain<prt::AdmonitionBlock> GenerateNode<prt::AdmonitionBlock>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug("AdmonitionBlock");
    return InitNode<prt::AdmonitionBlock>(ctx).WithRepeatedFieldMaxSize(
        "subnodes", 0);
}

template <>
Domain<prt::Include> GenerateNode<prt::Include>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug("Include");
    return InitNode<prt::Include>(ctx).WithRepeatedFieldMaxSize(
        "subnodes", 0);
}

template <>
Domain<prt::Empty> GenerateNode<prt::Empty>(CR<GenerateNodeContext> ctx) {
    ctx.debug("Empty");
    return InitNode<prt::Empty>(ctx).WithRepeatedFieldMaxSize(
        "subnodes", 0);
}

template <>
Domain<prt::AtMention> GenerateNode<prt::AtMention>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug("AtMention");
    return InitLeaf<prt::AtMention>(ctx) //
        .WithOptionalStringField("text", AlwaysSet(LowerIdent()));
}

template <>
Domain<prt::List> GenerateNode<prt::List>(CR<GenerateNodeContext> ctx) {
    ctx.debug("List");
    return InitNode<prt::List>(ctx) //
        .WithRepeatedProtobufField(
            "subnodes",
            VectorOf(GenerateAnyNodeWrapper(
                GenerateNode<prt::ListItem>(ctx.rec(osk::List)))));
}

template <>
Domain<prt::Placeholder> GenerateNode<prt::Placeholder>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug("Placeholder");
    return InitNode<prt::Placeholder>(ctx) //
        .WithRepeatedProtobufField(
            "subnodes",
            VectorOf(GenerateAnyRawText(ctx, LowerIdent())).WithSize(1));
}

template <>
Domain<prt::HashTag> GenerateNode<prt::HashTag>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug("HashTag");
    bool isMaxDepth = 2 < ctx.count(osk::HashTag);
    return InitNode<prt::HashTag>(ctx)
        .WithOptionalStringField("head", AlwaysSet(LowerIdent()))
        .WithRepeatedProtobufField(
            "subtags",
            VectorOf(
                isMaxDepth
                    ? Arbitrary<prt::HashTag>() //
                          .WithRepeatedFieldMaxSize("subnodes", 0)
                          .WithOptionalStringField(
                              "head", AlwaysSet(LowerIdent()))
                    : GenerateNode<prt::HashTag>(ctx.rec(osk::HashTag)))
                .WithMaxSize(isMaxDepth ? 2 : 0))
        .WithRepeatedFieldMaxSize("subnodes", 0);
}

template <>
Domain<prt::TextSeparator> GenerateNode<prt::TextSeparator>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug("TextSeparator");
    return InitNode<prt::TextSeparator>(ctx) //
        .WithRepeatedFieldMaxSize("subnodes", 0);
}

template <>
Domain<prt::Example> GenerateNode<prt::Example>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug("Example");
    return InitNode<prt::Example>(ctx) //
        .WithRepeatedProtobufField(
            "subnodes",
            VectorOf(GenerateAnyNodeWrapper(Domain<prt::RawText>(
                InitLeaf<prt::RawText>(ctx).WithStringField(
                    "text", StringOf(PrintableAsciiChar()))))));
}

template <>
Domain<prt::ParseError> GenerateNode<prt::ParseError>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug("ParseError");
    return InitNode<prt::ParseError>(ctx) //
        .WithRepeatedFieldMaxSize("subnodes", 0);
}

template <>
Domain<prt::ListItem> GenerateNode<prt::ListItem>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug("ListItem");
    return InitNode<prt::ListItem>(ctx) //
        .WithRepeatedProtobufField(
            "subnodes",
            VectorOf(
                GenerateAnyNode(ctx.getDomain(), ctx.rec(osk::ListItem))));
}

template <>
Domain<prt::MarkQuote> GenerateNode<prt::MarkQuote>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug("MarkQuote");
    return InitNode<prt::MarkQuote>(ctx).WithRepeatedFieldMaxSize(
        "subnodes", 0);
}

template <>
Domain<prt::Par> GenerateNode<prt::Par>(CR<GenerateNodeContext> ctx) {
    ctx.debug("Par");
    return InitNode<prt::Par>(ctx).WithRepeatedFieldMaxSize("subnodes", 0);
}

template <>
Domain<prt::CmdArguments> GenerateNode<prt::CmdArguments>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug("CmdArguments");
    return InitNode<prt::CmdArguments>(ctx).WithRepeatedFieldMaxSize(
        "subnodes", 0);
}

template <>
Domain<prt::Link> GenerateNode<prt::Link>(CR<GenerateNodeContext> ctx) {
    ctx.debug("Link");


    auto DataDomain =                //
        Arbitrary<prt::Link::Data>() //
            .WithProtobufField(
                "raw",
                Arbitrary<prt::Link::Raw>() //
                    .WithOptionalStringField(
                        "text", AlwaysSet(InRegexp(R"(https://\w+)"))))
            .WithProtobufField(
                "id",
                Arbitrary<prt::Link::Id>() //
                    .WithOptionalStringField(
                        "text", AlwaysSet(InRegexp(R"(\w+)"))))
            .WithProtobufField(
                "person",
                Arbitrary<prt::Link::Person>() //
                    .WithOptionalStringField(
                        "name", AlwaysSet(InRegexp(R"(\w+)"))))
            .WithProtobufField(
                "footnote",
                Arbitrary<prt::Link::Footnote>() //
                    .WithOptionalStringField(
                        "target", AlwaysSet(InRegexp(R"(\w+)"))))
            .WithProtobufField(
                "file",
                Arbitrary<prt::Link::File>() //
                    .WithOptionalStringField(
                        "file", AlwaysSet(InRegexp(R"(\w+)"))))
        //
        ;

    return InitNode<prt::Link>(ctx) //
        .WithOptionalProtobufField(
            "data", AlwaysSet(std::move(DataDomain)))
        .WithProtobufField(
            "description",
            GenerateNode<prt::Paragraph>(
                ctx.withRelativeRecursionLimit(1).rec(osk::Link)))
        .WithRepeatedFieldMaxSize("subnodes", 0);
}

template <>
Domain<prt::CommandGroup> GenerateNode<prt::CommandGroup>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug("CommandGroup");
    return InitNode<prt::CommandGroup>(ctx).WithRepeatedFieldMaxSize(
        "subnodes", 0);
}

template <>
Domain<prt::Time> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug("Time");
    auto StaticDomain =                //
        Arbitrary<prt::Time::Static>() //
            .WithProtobufField(
                "repeat",
                Arbitrary<prt::Time::Repeat>()
                    .WithInt32Field("count", InRange(0, 1200))
                    .WithOptionalEnumField(
                        "period",
                        AlwaysSet(          //
                            StaticCastEnum( //
                                GenerateEnumSet(
                                    sliceT<sem::Time::Repeat::Period>()))))
                    .WithOptionalEnumField(
                        "mode",
                        AlwaysSet(          //
                            StaticCastEnum( //
                                GenerateEnumSet(
                                    sliceT<sem::Time::Repeat::Mode>())))))
            .WithProtobufField("time", GenerateUserTime());


    auto TimeVariantDomain =                //
        Arbitrary<prt::Time::TimeVariant>() //
            .WithProtobufField("static", std::move(StaticDomain));

    return InitNode<prt::Time>(ctx.withoutSubnodes()) //
        .WithBoolFieldAlwaysSet("isActive")
        .WithRepeatedFieldMaxSize("subnodes", 0)
        .WithProtobufFieldAlwaysSet("time", std::move(TimeVariantDomain));
}


template <>
Domain<prt::Newline> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug("Newline");
    return InitLeaf<prt::Newline>(ctx) //
        .WithOptionalStringField(
            "text", AlwaysSet(StringOf(Just('\n')).WithSize(1)));
}

template <>
Domain<prt::RawText> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug("RawText");
    return InitLeaf<prt::RawText>(ctx) //
        .WithStringField("text", InRegexp(R"([a-zA-Z0-9_]+)"));
}

template <>
Domain<prt::Symbol> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug("Symbol");
    return InitNode<prt::Symbol>(ctx) //
        .WithOptionalStringField("name", AlwaysSet(LowerIdent()))
        .WithRepeatedProtobufField(
            "positional",
            VectorOf( //
                GenerateAnyNodeWrapper(GenerateNode<prt::Paragraph>(
                    ctx.withRelativeRecursionLimit(2)
                        .withMaxSubnodes(1)
                        .rec(osk::Symbol))))
                // Symbol can contain nested paragraphs with unlimited
                // nesting, but to avoid infinite recusion during domain
                // construction there is a hard limit here. Otherwise,
                // `\bold{\italic{\whatever{\else{\user{\wants{}}}}}}` is
                // an ok syntax.
                .WithMaxSize(ctx.count(osk::Symbol) < 2 ? 3 : 0))
        .WithRepeatedProtobufField(
            "parameters",
            VectorOf( //
                Arbitrary<orgproto::Symbol::Param>()
                    .WithStringField("key", LowerIdent())
                    .WithOptionalStringField(
                        "value", AlwaysSet(LowerIdent())))
                .WithMaxSize(4))
        .WithRepeatedFieldMaxSize("subnodes", 0);
}

template <>
Domain<prt::Subtree> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug("Subtree");
    auto subrec = ctx.rec(osk::Subtree);
    return InitNode<prt::Subtree>(ctx) //
        .WithStringField("treeId", StringOf(LowerChar()).WithMinSize(12))
        .WithStringField("todo", StringOf(UpperChar()).WithMinSize(3))
        .WithProtobufField(
            "completion", GenerateNode<prt::Completion>(subrec))
        .WithProtobufField(
            "description", GenerateNode<prt::Paragraph>(subrec))
        .WithProtobufField("closed", GenerateNode<prt::Time>(subrec))
        .WithProtobufField("scheduled", GenerateNode<prt::Time>(subrec))
        .WithProtobufField("deadline", GenerateNode<prt::Time>(subrec))
        .WithRepeatedProtobufField(
            "subnodes",
            VectorOf(GenerateAnyNode(subrec.getDomain(), subrec)))
        //
        ;
}

template <>
Domain<prt::Macro> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug("Macro");
    return InitNode<prt::Macro>(ctx.withoutSubnodes()) //
        .WithRepeatedFieldMaxSize("subnodes", 0)       //
        ;
}


template <>
Domain<prt::Word> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug("Word");
    return InitLeaf<prt::Word>(ctx) //
        .WithOptionalStringField("text", AlwaysSet(InRegexp(R"(\w+)")));
}

template <>
Domain<prt::BigIdent> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug("BigIdent");
    return InitLeaf<prt::BigIdent>(ctx) //
        .WithOptionalStringField(
            "text", AlwaysSet(InRegexp(R"([A-Z][_A-Z]+[A-Z])")));
}

template <>
Domain<prt::Space> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug("Space");
    return InitLeaf<prt::Space>(ctx) //
        .WithOptionalStringField(
            "text", AlwaysSet(StringOf(ElementOf({' '})).WithMinSize(1)));
}

template <>
Domain<prt::Center> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug("Center");
    return InitNode<prt::Center>(ctx).WithRepeatedProtobufField(
        "subnodes",
        VectorOf(GenerateAnyNodeWrapper(
                     GenerateNode<prt::Paragraph>(ctx.rec(osk::Center))))
            .WithMinSize(1));
}

template <>
Domain<prt::Verse> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug("Verse");
    return InitNode<prt::Verse>(ctx).WithRepeatedProtobufField(
        "subnodes",
        VectorOf(GenerateAnyNodeWrapper(
                     GenerateNode<prt::Paragraph>(ctx.rec(osk::Center))))
            .WithMinSize(1));
}

template <>
Domain<prt::Quote> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug("Quote");
    return InitNode<prt::Quote>(ctx).WithRepeatedProtobufField(
        "subnodes",
        VectorOf(GenerateAnyNodeWrapper(
                     GenerateNode<prt::Paragraph>(ctx.rec(osk::Quote))))
            .WithMinSize(1));
}

template <>
Domain<prt::TimeRange> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug("TimeRange");
    return InitNode<prt::TimeRange>(ctx)
        .WithRepeatedFieldMaxSize("subnodes", 0)
        .WithOptionalProtobufField(
            "from",
            AlwaysSet(GenerateNode<prt::Time>(ctx.rec(osk::TimeRange))))
        .WithOptionalProtobufField(
            "to",
            AlwaysSet(GenerateNode<prt::Time>(ctx.rec(osk::TimeRange))));
}

template <>
Domain<prt::Bold> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug("Bold");
    return InitNode<prt::Bold>(ctx) //
        .WithRepeatedProtobufField(
            "subnodes",
            SpacedSubDomain(ctx.withRelativeRecursionLimit(2) //
                                .withMaxSubnodes(2)
                                .rec(osk::Bold)));
}

template <>
Domain<prt::Verbatim> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug("Verbatim");
    return InitNode<prt::Verbatim>(ctx) //
        .WithRepeatedProtobufField(
            "subnodes",
            SpacedSubDomain(ctx.withRelativeRecursionLimit(2) //
                                .withMaxSubnodes(2)
                                .rec(osk::Verbatim)));
}

template <>
Domain<prt::Italic> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug("Italic");
    return InitNode<prt::Italic>(ctx) //
        .WithRepeatedProtobufField(
            "subnodes",
            SpacedSubDomain(ctx.withRelativeRecursionLimit(2) //
                                .withMaxSubnodes(2)
                                .rec(osk::Italic)));
}

template <>
Domain<prt::Underline> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug("Underline");
    return InitNode<prt::Underline>(ctx) //
        .WithRepeatedProtobufField(
            "subnodes",
            SpacedSubDomain(ctx.withRelativeRecursionLimit(2) //
                                .withMaxSubnodes(2)
                                .rec(osk::Underline)));
}

template <>
Domain<prt::Strike> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug("Strike");
    return InitNode<prt::Strike>(ctx) //
        .WithRepeatedProtobufField(
            "subnodes",
            SpacedSubDomain(ctx.withRelativeRecursionLimit(2) //
                                .withMaxSubnodes(2)
                                .rec(osk::Strike)));
}

template <>
Domain<prt::Paragraph> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug("Paragraph");
    return InitNode<prt::Paragraph>(ctx) //
        .WithRepeatedProtobufField(
            "attached", ctx.getAttachedDomain(osk::Paragraph))
        .WithRepeatedProtobufField(
            "subnodes", SpacedSubDomain(ctx.rec(osk::Paragraph)));
}

template <>
Domain<prt::DocumentOptions> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug("DocumentOptions");
    return InitLeaf<prt::DocumentOptions>(ctx.rec(osk::DocumentOptions));
}

template <>
Domain<prt::Document> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug("Document");
    return InitNode<prt::Document>(ctx) //
        .WithRepeatedFieldMaxSize("idTable", 0)
        .WithRepeatedFieldMaxSize("nameTable", 0)
        .WithRepeatedFieldMaxSize("footnoteTable", 0)
        .WithRepeatedFieldMaxSize("anchorTable", 0)
        .WithProtobufField(
            "title",
            GenerateNode<prt::Paragraph>(
                ctx.withoutAttached().withMaxSubnodes(2).rec(
                    osk::Document)))
        .WithProtobufField(
            "author",
            GenerateNode<prt::Paragraph>(
                ctx.withoutAttached().withMaxSubnodes(2).rec(
                    osk::Document)))
        .WithProtobufField(
            "creator",
            GenerateNode<prt::Paragraph>(
                ctx.withoutAttached().withMaxSubnodes(2).rec(
                    osk::Document)))
        .WithProtobufField(
            "email",
            GenerateNode<prt::RawText>(
                ctx.withoutAttached().withMaxSubnodes(2).rec(
                    osk::Document)))
        .WithProtobufField(
            "options",
            GenerateNode<prt::DocumentOptions>(ctx.rec(osk::Document)))
        .WithStringField("language", StringOf(LowerChar()))
        .WithStringField("exportFileName", StringOf(PrintableAsciiChar()))
        .WithRepeatedProtobufField(
            "subnodes",
            GenerateInterspersedNodes(
                ctx.withRelativeRecursionLimit(4).rec(osk::Document),
                ctx.generateDomain(),
                ctx.generateDomain(osk::Newline)));
}
