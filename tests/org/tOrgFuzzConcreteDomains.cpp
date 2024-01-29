#include "tOrgFuzzUtils.hpp"
#include "tOrgFuzzDomains.hpp"

template <>
Domain<prt::Caption> GenerateNode<prt::Caption>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::Caption>(ctx);
}

template <>
Domain<prt::FileTarget> GenerateNode<prt::FileTarget>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::FileTarget>(ctx);
}

template <>
Domain<prt::SubtreeLog> GenerateNode<prt::SubtreeLog>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::SubtreeLog>(ctx);
}

template <>
Domain<prt::DocumentGroup> GenerateNode<prt::DocumentGroup>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::DocumentGroup>(ctx);
}

template <>
Domain<prt::Monospace> GenerateNode<prt::Monospace>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::Monospace>(ctx);
}

template <>
Domain<prt::Completion> GenerateNode<prt::Completion>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::Completion>(ctx);
}

template <>
Domain<prt::Code> GenerateNode<prt::Code>(CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::Code>(ctx);
}

template <>
Domain<prt::StmtList> GenerateNode<prt::StmtList>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::StmtList>(ctx);
}

template <>
Domain<prt::Punctuation> GenerateNode<prt::Punctuation>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::Punctuation>(ctx);
}

template <>
Domain<prt::Export> GenerateNode<prt::Export>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::Export>(ctx);
}

template <>
Domain<prt::Table> GenerateNode<prt::Table>(CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::Table>(ctx);
}

template <>
Domain<prt::CmdArgument> GenerateNode<prt::CmdArgument>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::CmdArgument>(ctx);
}

template <>
Domain<prt::Footnote> GenerateNode<prt::Footnote>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::Footnote>(ctx);
}

template <>
Domain<prt::Row> GenerateNode<prt::Row>(CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::Row>(ctx);
}

template <>
Domain<prt::InlineMath> GenerateNode<prt::InlineMath>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::InlineMath>(ctx);
}

template <>
Domain<prt::Escaped> GenerateNode<prt::Escaped>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::Escaped>(ctx);
}

template <>
Domain<prt::AdmonitionBlock> GenerateNode<prt::AdmonitionBlock>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::AdmonitionBlock>(ctx);
}

template <>
Domain<prt::Include> GenerateNode<prt::Include>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::Include>(ctx);
}

template <>
Domain<prt::Empty> GenerateNode<prt::Empty>(CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::Empty>(ctx);
}

template <>
Domain<prt::AtMention> GenerateNode<prt::AtMention>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::AtMention>(ctx);
}

template <>
Domain<prt::List> GenerateNode<prt::List>(CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::List>(ctx);
}

template <>
Domain<prt::Placeholder> GenerateNode<prt::Placeholder>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::Placeholder>(ctx);
}

template <>
Domain<prt::HashTag> GenerateNode<prt::HashTag>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::HashTag>(ctx);
}

template <>
Domain<prt::TextSeparator> GenerateNode<prt::TextSeparator>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::TextSeparator>(ctx);
}

template <>
Domain<prt::Example> GenerateNode<prt::Example>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::Example>(ctx);
}

template <>
Domain<prt::ParseError> GenerateNode<prt::ParseError>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::ParseError>(ctx);
}

template <>
Domain<prt::ListItem> GenerateNode<prt::ListItem>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::ListItem>(ctx);
}

template <>
Domain<prt::MarkQuote> GenerateNode<prt::MarkQuote>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::MarkQuote>(ctx);
}

template <>
Domain<prt::Par> GenerateNode<prt::Par>(CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::Par>(ctx);
}

template <>
Domain<prt::CmdArguments> GenerateNode<prt::CmdArguments>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::CmdArguments>(ctx);
}

template <>
Domain<prt::Link> GenerateNode<prt::Link>(CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::Link>(ctx);
}

template <>
Domain<prt::CommandGroup> GenerateNode<prt::CommandGroup>(
    CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::CommandGroup>(ctx);
}

template <>
Domain<prt::Time> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
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
        .WithProtobufFieldAlwaysSet("time", std::move(TimeVariantDomain));
}


template <>
Domain<prt::Newline> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitLeaf<prt::Newline>(ctx) //
        .WithOptionalStringField(
            "text", AlwaysSet(StringOf(Just('\n')).WithSize(1)));
}

template <>
Domain<prt::RawText> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitLeaf<prt::RawText>(ctx) //
        .WithStringField("text", InRegexp(R"([a-zA-Z0-9_]+)"));
}

template <>
Domain<prt::Symbol> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::Symbol>(ctx) //
        .WithOptionalStringField("name", AlwaysSet(LowerIdent()))
        .WithRepeatedProtobufField(
            "positional",
            VectorOf( //
                GenerateAnyNodeWrapper(
                    GenerateNode<prt::Paragraph>(ctx.rec(osk::Symbol))))
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
    ctx.debug(__PRETTY_FUNCTION__);
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
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::Macro>(ctx.withoutSubnodes()) //
        ;
}


template <>
Domain<prt::Word> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitLeaf<prt::Word>(ctx) //
        .WithOptionalStringField("text", AlwaysSet(InRegexp(R"(\w+)")));
}

template <>
Domain<prt::BigIdent> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitLeaf<prt::BigIdent>(ctx) //
        .WithOptionalStringField(
            "text", AlwaysSet(InRegexp(R"([A-Z][_A-Z]+[A-Z])")));
}

template <>
Domain<prt::Space> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitLeaf<prt::Space>(ctx) //
        .WithOptionalStringField(
            "text", AlwaysSet(StringOf(ElementOf({' '})).WithMinSize(1)));
}

template <>
Domain<prt::Center> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::Center>(ctx).WithRepeatedProtobufField(
        "subnodes",
        VectorOf(GenerateAnyNodeWrapper(
                     GenerateNode<prt::Paragraph>(ctx.rec(osk::Center))))
            .WithMinSize(1));
}

template <>
Domain<prt::Quote> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::Quote>(ctx).WithRepeatedProtobufField(
        "subnodes",
        VectorOf(GenerateAnyNodeWrapper(
                     GenerateNode<prt::Paragraph>(ctx.rec(osk::Quote))))
            .WithMinSize(1));
}

template <>
Domain<prt::TimeRange> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::TimeRange>(ctx.withoutSubnodes())
        .WithOptionalProtobufField(
            "from",
            AlwaysSet(GenerateNode<prt::Time>(ctx.rec(osk::TimeRange))))
        .WithOptionalProtobufField(
            "to",
            AlwaysSet(GenerateNode<prt::Time>(ctx.rec(osk::TimeRange))));
}

template <>
Domain<prt::Bold> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::Bold>(ctx) //
        .WithRepeatedProtobufField(
            "subnodes", GenerateSpaceSeparatedNodes(ctx.rec(osk::Bold)));
}

template <>
Domain<prt::Verbatim> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::Verbatim>(ctx) //
        .WithRepeatedProtobufField(
            "subnodes",
            GenerateSpaceSeparatedNodes(ctx.rec(osk::Verbatim)));
}

template <>
Domain<prt::Italic> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::Italic>(ctx) //
        .WithRepeatedProtobufField(
            "subnodes", GenerateSpaceSeparatedNodes(ctx.rec(osk::Italic)));
}

template <>
Domain<prt::Underline> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::Underline>(ctx) //
        .WithRepeatedProtobufField(
            "subnodes",
            GenerateSpaceSeparatedNodes(ctx.rec(osk::Underline)));
}

template <>
Domain<prt::Strike> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::Strike>(ctx) //
        .WithRepeatedProtobufField(
            "subnodes", GenerateSpaceSeparatedNodes(ctx.rec(osk::Strike)));
}

template <>
Domain<prt::Paragraph> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::Paragraph>(ctx) //
        .WithRepeatedProtobufField(
            "subnodes",
            GenerateSpaceSeparatedNodes(ctx.rec(osk::Paragraph)));
}

template <>
Domain<prt::DocumentOptions> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitLeaf<prt::DocumentOptions>(ctx.rec(osk::DocumentOptions));
}

template <>
Domain<prt::Document> GenerateNode(CR<GenerateNodeContext> ctx) {
    ctx.debug(__PRETTY_FUNCTION__);
    return InitNode<prt::Document>(ctx) //
        .WithRepeatedFieldMaxSize("idTable", 0)
        .WithRepeatedFieldMaxSize("nameTable", 0)
        .WithRepeatedFieldMaxSize("footnoteTable", 0)
        .WithRepeatedFieldMaxSize("anchorTable", 0)
        .WithProtobufField(
            "title", GenerateNode<prt::Paragraph>(ctx.rec(osk::Document)))
        .WithProtobufField(
            "author", GenerateNode<prt::Paragraph>(ctx.rec(osk::Document)))
        .WithProtobufField(
            "creator",
            GenerateNode<prt::Paragraph>(ctx.rec(osk::Document)))
        .WithProtobufField(
            "email", GenerateNode<prt::RawText>(ctx.rec(osk::Document)))
        .WithProtobufField(
            "options",
            GenerateNode<prt::DocumentOptions>(ctx.rec(osk::Document)))
        .WithStringField("language", StringOf(LowerChar()))
        .WithStringField("exportFileName", StringOf(PrintableAsciiChar()))
        .WithRepeatedProtobufField(
            "subnodes",
            GenerateNodesKind(
                GenerateKind({
                    osk::Paragraph,
                }),
                ctx.rec(osk::Document)));
}
