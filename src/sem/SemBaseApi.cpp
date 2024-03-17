#include "SemBaseApi.hpp"
#include <parse/OrgTokenizer.hpp>
#include <parse/OrgParser.hpp>
#include <sem/SemConvert.hpp>
#include <exporters/ExporterJson.hpp>
#include <fstream>
#include <sem/perfetto_org.hpp>
#include <sem/SemOrgFormat.hpp>
#include <exporters/ExporterJson.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <exporters/exporteryaml.hpp>
#include <exporters/exportertree.hpp>
#include <exporters/ExporterUltraplain.hpp>
#include <sem/SemOrgSerdeDeclarations.hpp>
#include <SemOrgProto.pb.h>

using namespace sem;
using osk = OrgSemKind;


std::string sem::exportToJsonString(sem::SemId<sem::Org> const& node) {
    return to_string(ExporterJson{}.evalTop(node));
}

void sem::exportToJsonFile(
    sem::SemId<sem::Org> const& node,
    std::string                 path) {
    writeFile(fs::path{path}, exportToJsonString(node));
}

std::string sem::exportToYamlString(sem::SemId<sem::Org> const& node) {
    std::stringstream os;
    os << ExporterYaml{}.evalTop(node);
    return os.str();
}

void sem::exportToYamlFile(
    sem::SemId<sem::Org> const& node,
    std::string                 path) {
    writeFile(fs::path{path}, exportToYamlString(node));
}


std::string sem::exportToTreeString(
    sem::SemId<sem::Org> const&   node,
    sem::OrgTreeExportOpts const& opts) {
    ColStream    os{};
    ExporterTree tree{os};

    tree.conf.withLineCol     = opts.withLineCol;
    tree.conf.withOriginalId  = opts.withOriginalId;
    tree.conf.skipEmptyFields = opts.skipEmptyFields;
    tree.conf.startLevel      = opts.startLevel;
    tree.evalTop(node);

    std::string result = os.toString(opts.withColor);
    return result;
}

void sem::exportToTreeFile(
    sem::SemId<sem::Org> const&   node,
    std::string                   path,
    sem::OrgTreeExportOpts const& opts) {

    ColStream    os{};
    ExporterTree tree{os};

    tree.conf.withLineCol     = opts.withLineCol;
    tree.conf.withOriginalId  = opts.withOriginalId;
    tree.conf.skipEmptyFields = opts.skipEmptyFields;
    tree.conf.startLevel      = opts.startLevel;
    tree.evalTop(node);

    std::ofstream file{path};
    file << os.toString(opts.withColor);
}

sem::SemId<sem::Document> sem::parseFile(
    std::string               file,
    const OrgParseParameters& opts) {
    return parseStringOpts(readFile(fs::path{file}), opts);
}

sem::SemId<sem::Document> sem::parseString(std::string text) {
    return parseStringOpts(text, OrgParseParameters{});
}

sem::SemId<sem::Document> sem::parseStringOpts(
    const std::string         text,
    OrgParseParameters const& opts) {
    LexerParams         p;
    SPtr<std::ofstream> fileTrace;
    if (opts.baseTokenTracePath) {
        fileTrace = std::make_shared<std::ofstream>(
            *opts.baseTokenTracePath);
    }
    p.traceStream            = fileTrace.get();
    OrgTokenGroup baseTokens = ::tokenize(text.data(), text.size(), p);
    OrgTokenGroup tokens;
    OrgTokenizer  tokenizer{&tokens};

    if (opts.tokenTracePath) {
        tokenizer.setTraceFile(*opts.tokenTracePath);
    }

    tokenizer.convert(baseTokens);
    Lexer<OrgTokenKind, OrgFill> lex{&tokens};

    OrgNodeGroup nodes{&tokens};
    OrgParser    parser{&nodes};
    if (opts.parseTracePath) { parser.setTraceFile(*opts.parseTracePath); }

    (void)parser.parseFull(lex);

    sem::OrgConverter converter{};
    if (opts.semTracePath) { converter.setTraceFile(*opts.semTracePath); }

    return converter.toDocument(OrgAdapter(&nodes, OrgId(0)));
}

sem::SemId<sem::Document> sem::readProtobufFile(const std::string& file) {
    sem::SemId        read_node = sem::SemId<sem::Org>::Nil();
    std::ifstream     stream{file};
    orgproto::AnyNode result;
    result.ParseFromIstream(&stream);
    proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::read(
        result,
        proto_write_accessor<sem::SemId<sem::Org>>::for_ref(read_node));
    return read_node.as<sem::Document>();
}

void sem::exportToProtobufFile(
    sem::SemId<sem::Document> doc,
    const std::string&        file) {
    std::ofstream     stream{file};
    orgproto::AnyNode result;
    proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::write(
        &result, doc.asOrg());
    result.SerializeToOstream(&stream);
}


std::string sem::formatToString(sem::SemId<sem::Org> arg) {
    return sem::Formatter::format(arg);
}

namespace {
void eachSubnodeRecImpl(
    CR<sem::SubnodeVisitor> visitor,
    SemId<Org>              org,
    bool                    originalBase);

template <sem::NotOrg T>
void visitField(CR<sem::SubnodeVisitor>, CR<T>) {}


void visitField(CR<sem::SubnodeVisitor> visitor, SemId<Org> node) {
    if (!node.isNil()) { eachSubnodeRecImpl(visitor, node, true); }
}

template <typename T>
void visitField(CR<sem::SubnodeVisitor> visitor, CVec<T> value) {
    for (const auto& it : value) { visitField(visitor, it); }
}


template <typename T>
void visitField(CR<sem::SubnodeVisitor> visitor, CR<Opt<T>> value) {
    if (value) { visitField(visitor, *value); }
}

template <typename T>
void recVisitOrgNodesImpl(
    CR<sem::SubnodeVisitor> visitor,
    SemId<T>                tree,
    bool                    originalBase) {
    if (tree.isNil()) { return; }
    if (originalBase) { visitor(tree); }
    using Bd = describe_bases<T, mod_any_access>;
    using Md = describe_members<T, mod_any_access>;
    mp_for_each<Bd>([&](auto Base) {
        using BaseType = typename decltype(Base)::type;
        recVisitOrgNodesImpl<BaseType>(
            visitor, tree.template as<BaseType>(), false);
    });

    mp_for_each<Md>([&](auto const& field) {
        visitField(visitor, tree.get()->*field.pointer);
    });
}


void eachSubnodeRecImpl(
    CR<sem::SubnodeVisitor> visitor,
    SemId<Org>              org,
    bool                    originalBase) {
    std::visit(
        [&](const auto& node) {
            recVisitOrgNodesImpl(visitor, node, originalBase);
        },
        asVariant(org));
}
} // namespace


void sem::eachSubnodeRec(SemId<Org> id, SubnodeVisitor cb) {
    eachSubnodeRecImpl(cb, id, true);
}


namespace {
void eachSubnodeRecWithCtxImpl(
    CR<sem::SubnodeVisitorWithCtx>    visitor,
    SemId<Org>                        org,
    bool                              originalBase,
    Vec<SubnodeVisitorCtxPart> const& ctx);

template <sem::NotOrg T>
void visitFieldWithCtx(
    CR<sem::SubnodeVisitorWithCtx>,
    CR<T>,
    Vec<SubnodeVisitorCtxPart> const&) {}


void visitFieldWithCtx(
    CR<sem::SubnodeVisitorWithCtx>    visitor,
    SemId<Org>                        node,
    Vec<SubnodeVisitorCtxPart> const& ctx) {
    if (!node.isNil()) {
        eachSubnodeRecWithCtxImpl(visitor, node, true, ctx);
    }
}

template <typename T>
void visitFieldWithCtx(
    CR<sem::SubnodeVisitorWithCtx>    visitor,
    CVec<T>                           value,
    Vec<SubnodeVisitorCtxPart> const& ctx) {
    for (int i = 0; i < value.size(); ++i) {
        visitFieldWithCtx(
            visitor,
            value.at(i),
            ctx
                + SubnodeVisitorCtxPart{
                    .index = i,
                    .kind  = SubnodeVisitorCtxPart::Kind::Index,
                });
    }
}

template <typename T>
void visitFieldWithCtx(
    CR<sem::SubnodeVisitorWithCtx>    visitor,
    UnorderedMap<Str, T> const&       value,
    Vec<SubnodeVisitorCtxPart> const& ctx) {
    for (auto const& [key, mapped] : value) {
        visitFieldWithCtx(
            visitor,
            mapped,
            ctx
                + SubnodeVisitorCtxPart{
                    .field = key,
                    .kind  = SubnodeVisitorCtxPart::Kind::Key,
                });
    }
}


template <typename T>
void visitFieldWithCtx(
    CR<sem::SubnodeVisitorWithCtx>    visitor,
    CR<Opt<T>>                        value,
    Vec<SubnodeVisitorCtxPart> const& ctx) {
    if (value) { visitFieldWithCtx(visitor, *value, ctx); }
}

template <typename T>
void recVisitOrgNodesWithCtxImpl(
    CR<sem::SubnodeVisitorWithCtx>    visitor,
    SemId<T>                          tree,
    bool                              originalBase,
    Vec<SubnodeVisitorCtxPart> const& ctx) {
    if (tree.isNil()) { return; }
    if (originalBase) { visitor(tree, ctx); }
    using Bd = describe_bases<T, mod_any_access>;
    using Md = describe_members<T, mod_any_access>;
    mp_for_each<Bd>([&](auto Base) {
        using BaseType = typename decltype(Base)::type;
        recVisitOrgNodesWithCtxImpl<BaseType>(
            visitor, tree.template as<BaseType>(), false, ctx);
    });

    mp_for_each<Md>([&](auto const& field) {
        visitFieldWithCtx(
            visitor,
            tree.get()->*field.pointer,
            ctx
                + SubnodeVisitorCtxPart{
                    .node  = tree.asOrg(),
                    .field = field.name,
                    .kind  = SubnodeVisitorCtxPart::Kind::Field,
                });
    });
}


void eachSubnodeRecWithCtxImpl(
    CR<sem::SubnodeVisitorWithCtx>    visitor,
    SemId<Org>                        org,
    bool                              originalBase,
    Vec<SubnodeVisitorCtxPart> const& ctx) {
    std::visit(
        [&](const auto& node) {
            recVisitOrgNodesWithCtxImpl(visitor, node, originalBase, ctx);
        },
        asVariant(org));
}
} // namespace

void sem::eachSubnodeRecWithContext(
    SemId<Org>            id,
    SubnodeVisitorWithCtx cb) {
    eachSubnodeRecWithCtxImpl(cb, id, true, {});
}

void OrgDocumentContext::addNodes(const sem::SemId<sem::Org>& node) {
    if (node.isNil()) { return; }
    eachSubnodeRec(node, [&](OrgArg arg) {
        if (arg->is(osk::Subtree)) {
            SemId<Subtree> tree = arg.as<Subtree>();
            if (tree->treeId) {
                this->subtreeIds[tree->treeId.value()].push_back(tree);
            }
        } else if (arg->is(osk::AnnotatedParagraph)) {
            SemId<AnnotatedParagraph> par = arg.as<AnnotatedParagraph>();
            if (par->getAnnotationKind()
                == AnnotatedParagraph::AnnotationKind::Footnote) {
                this->footnoteTargets[par->getFootnote().name].push_back(
                    par);
            }
        }
    });
}


Vec<SemId<Subtree>> OrgDocumentContext::getSubtreeById(
    const Str& id) const {
    if (subtreeIds.contains(id)) {
        return subtreeIds.at(id);
    } else {
        return {};
    }
}


Vec<SemId<Org>> OrgDocumentContext::getRadioTarget(Str const& name) const {
    return {};
}

Vec<SemId<Org>> OrgDocumentContext::getLinkTarget(
    const sem::SemId<sem::Link>& link) const {
    Vec<SemId<Org>> result;
    switch (link->getLinkKind()) {
        case Link::Kind::Footnote: {
            CR<Str> target = link->getFootnote().target;
            if (footnoteTargets.contains(target)) {
                for (auto const& it : footnoteTargets.at(target)) {
                    result.push_back(it.asOrg());
                }
            }
        }

        case Link::Kind::Id: {
            CR<Str> target = link->getId().text;
            if (subtreeIds.contains(target)) {
                for (auto const& it : subtreeIds.at(target)) {
                    result.push_back(it.asOrg());
                }
            }
        }

        default: {
        }
    }

    return result;
}

Opt<UserTime> getCreationTime(const SemId<Org>& node) {
    if (node->is(osk::AnnotatedParagraph)) {
        auto const& par = node.as<AnnotatedParagraph>();
        if (par->getAnnotationKind()
            == AnnotatedParagraph::AnnotationKind::Timestamp) {
            return par->getTimestamp().time->getStatic().time;
        }
    } else if (node->is(osk::Subtree)) {
        auto const& tree = node.as<Subtree>();
        for (auto const& period :
             tree->getTimePeriods({Subtree::Period::Kind::Created})) {
            return period.from->getStatic().time;
        }

        for (auto const& period :
             tree->getTimePeriods({Subtree::Period::Kind::Titled})) {
            return period.from->getStatic().time;
        }
    }

    return std::nullopt;
}


bool OrgDocumentSelector::isMatching(
    const SemId<Org>&                 node,
    const Vec<SubnodeVisitorCtxPart>& ctx) const {

    for (int i = 0; i < path.size(); ++i) {
        if (i < path.high() && !path.at(i).link.has_value()) {
            throw std::logic_error(
                fmt("Element at index {} is not a final element in the "
                    "selector path, but it is missing a link.",
                    i));
        }
    }

    using PathIter = Vec<OrgSelectorCondition>::const_iterator;

    auto dbg =
        [&](Str const& msg, int depth, int line = __builtin_LINE()) {
            if (debug) {
                LOG(INFO) << fmt(
                    "{}[{}] {}", Str("  ").repeated(depth), line, msg);
            }
        };

    auto getParentSpan = [](int levels, Span<SubnodeVisitorCtxPart> span)
        -> Opt<Span<SubnodeVisitorCtxPart>> {
        auto end           = span.rbegin();
        auto begin         = span.rend();
        int  skippedLevels = 0;
        while (skippedLevels < levels && end != begin) {
            if (end->node) { ++skippedLevels; }
            ++end;
        }

        if (skippedLevels == levels) {
            return IteratorSpan(begin.base(), end.base());
        } else {
            return std::nullopt;
        }
    };

    auto getParentNode =
        [](int                         levels,
           Span<SubnodeVisitorCtxPart> span) -> Opt<SemId<Org>> {
        int skippedLevels = 0;
        for (auto it = span.rbegin(); it != span.rend(); ++it) {
            if (it->node) {
                ++skippedLevels;
                if (skippedLevels == levels) { return it->node.value(); }
            }
        }

        return std::nullopt;
    };


    Func<bool(
        PathIter                    condition,
        SemId<Org>                  node,
        Span<SubnodeVisitorCtxPart> ctx,
        int                         depth)>
        aux;

    aux = [&](PathIter                    condition,
              SemId<Org>                  node,
              Span<SubnodeVisitorCtxPart> ctx,
              int                         depth) {
        if (debug) {
            Vec<Str> context;
            for (auto const& it : ctx) {
                if (it.node) {
                    context.push_back(
                        fmt("{}", it.node.value()->getKind()));
                } else {
                    context.push_back(fmt("idx={}", it.index));
                }
            }

            dbg(fmt("condition={} (@{}/{}) node={} ctx={}",
                    condition->debug,
                    std::distance(path.begin(), condition),
                    path.high(),
                    node->getKind(),
                    context),
                depth);
        }

        if (condition->check(node, ctx)) {
            dbg(fmt("passed check {}", condition->debug), depth);
            if (condition->link) {
                auto const& link = condition->link.value();
                dbg(fmt("link={}", link.kind), depth);
                switch (link.kind) {
                    case OrgSelectorLink::Kind::DirectSubnode: {
                        auto node = getParentNode(1, ctx);
                        if (node) {
                            bool result = aux(
                                condition + 1,
                                node.value(),
                                getParentSpan(1, ctx).value(),
                                depth + 1);
                            return result;
                        } else {
                            return false;
                        }
                    }

                    case OrgSelectorLink::Kind::IndirectSubnode: {
                        int offset = 1;
                        while (
                            auto parentSpan = getParentSpan(offset, ctx)) {
                            auto parent = getParentNode(offset, ctx);
                            if (parent
                                && aux(
                                    condition + 1,
                                    parent.value(),
                                    parentSpan.value(),
                                    depth + 1)) {
                                return true;
                            }
                            ++offset;
                        }

                        return false;
                    }
                }
            } else {
                dbg(fmt("no link"), depth);
                return true;
            }
        } else {
            return false;
        }
    };

    return aux(
        path.begin(), node, IteratorSpan(ctx.begin(), ctx.end()), 0);
}

void OrgDocumentSelector::assertLinkPresence() const {
    if (!path.empty()) {
        if (!path.back().link) {
            throw std::logic_error(
                "Adding extra search path with previous path element "
                "missing link value. Previous searchXXX should have been "
                "called with link= set to a non-null value. This is a "
                "logic error in the search query construction code.");
        }
    }
}

Vec<SemId<Org>> OrgDocumentSelector::getMatches(
    const SemId<Org>& node) const {
    Vec<SemId<Org>> result;
    eachSubnodeRecWithContext(
        node,
        [&](SemId<Org> const&                 node,
            Vec<SubnodeVisitorCtxPart> const& path) {
            if (isMatching(node, path)) { result.push_back(node); }
        });

    return result;
}

void OrgDocumentSelector::searchSubtreePlaintextTitle(
    const Str&           title,
    Opt<OrgSelectorLink> link) {
    assertLinkPresence();
    if (debug) { LOG(INFO) << title; }
    path.push_back({
        .check = [title](
                     SemId<Org> const& node,
                     Span<SubnodeVisitorCtxPart> const&) -> bool {
            return node->is(osk::Subtree)
                && ExporterUltraplain::toStr(node.as<Subtree>()->title)
                       == title;
        },
        .debug = fmt("HasSubtreePlaintextTitle:{}", title),
        .link  = link,
    });
}

void OrgDocumentSelector::searchSubtreeId(
    const Str&           id,
    Opt<OrgSelectorLink> link) {
    assertLinkPresence();
    path.push_back({
        .check = [id](
                     SemId<Org> const& node,
                     Span<SubnodeVisitorCtxPart> const&) -> bool {
            return node->is(osk::Subtree)
                && node.as<Subtree>()->treeId == id;
        },
        .debug = fmt("HasSubtreeId:{}", id),
        .link  = link,
    });
}

void OrgDocumentSelector::searchAnyKind(
    IntSet<OrgSemKind> const& kinds,
    Opt<OrgSelectorLink>      link) {
    assertLinkPresence();
    path.push_back({
        .check = [kinds](
                     SemId<Org> const& node,
                     Span<SubnodeVisitorCtxPart> const&) -> bool {
            return kinds.contains(node->getKind());
        },
        .debug = fmt("HasKind:{}", kinds),
        .link  = link,
    });
}
