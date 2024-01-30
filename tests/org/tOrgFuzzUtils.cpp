#include "tOrgFuzzUtils.hpp"
#include "tOrgFuzzDomains.hpp"

void PrintMessageWithTypeName(
    const google::protobuf::Message& message,
    std::ostringstream&              oss,
    int                              depth) {
    const gpb::Descriptor* descriptor = message.GetDescriptor();
    const gpb::Reflection* reflection = message.GetReflection();
    std::string indent(depth * 2, ' '); // Indentation for pretty printing

    oss << indent << descriptor->name() << " {\n";

    for (int i = 0; i < descriptor->field_count(); ++i) {
        const gpb::FieldDescriptor* field = descriptor->field(i);

        if ((!field->is_repeated()
             && !reflection->HasField(message, field))
            || (field->is_repeated()
                && reflection->FieldSize(message, field) == 0)) {
            continue; // Skip non-set fields
        }


        if (field->cpp_type()
            == google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE) {
            if (field->is_repeated()) {
                int count = reflection->FieldSize(message, field);
                oss << indent << "  " << field->name() << ": [\n";
                for (int j = 0; j < count; ++j) {
                    const gpb::Message& subMessage = //
                        reflection->GetRepeatedMessage(message, field, j);
                    PrintMessageWithTypeName(subMessage, oss, depth + 2);
                }
                oss << indent << "  "
                    << "]\n";
            } else {
                oss << indent << "  " << field->name() << ":\n";
                const gpb::Message& subMessage = //
                    reflection->GetMessage(message, field);
                PrintMessageWithTypeName(subMessage, oss, depth + 2);
            }
        } else {
            oss << indent << "  " << field->name() << ": ";
            std::string fieldText;
            if (field->is_repeated()) {
                oss << "[ ";
                int count = reflection->FieldSize(message, field);
                for (int j = 0; j < count; ++j) {
                    google::protobuf::TextFormat::PrintFieldValueToString(
                        message, field, j, &fieldText);
                    oss << fieldText << (j < count - 1 ? " " : "");
                }
                oss << " ]\n";
            } else if (field->name() == "debug") {
                oss << reflection->GetString(message, field) << "\n";
            } else {
                google::protobuf::TextFormat::PrintFieldValueToString(
                    message, field, -1, &fieldText);
                oss << fieldText << "\n";
            }
        }
    }

    oss << indent << "}\n";
}

std::string PrintWithTypeName(const google::protobuf::Message& message) {
    std::ostringstream oss;
    PrintMessageWithTypeName(message, oss, 0);
    return oss.str();
}

std::string GenerateNodeContext::format() const {
    return std::format(
        "min={} max={} [{}] ... {}",
        getMinSubnodeCount(),
        getMaxSubnodeCount(),
        steps
            | rv::transform([](GenerateNodePath const& p) -> std::string {
                  return fmt("{}:{}", p.kind, p.line);
              })
            | rv::intersperse("->") //
            | rv::join              //
            | rs::to<std::string>(),
        getSubnodeSet());
}

std::string GenerateNodeContext::indent() const {
    return std::string(steps.size() * 2, ' ');
}

void GenerateNodeContext::debug(
    const char* function,
    std::string msg,
    int         line) const {
    if (opts.get().enableTrace) {
        std::cerr << indent() << msg << "'" << function << "' " << format()
                  << "\n";
    }
}

int GenerateNodeContext::count(OrgSemKind contexts) const {
    return rs::count_if(steps, [&](GenerateNodePath const& p) {
        return p.kind == contexts;
    });
}

Domain<std::vector<orgproto::AnyNode>> GenerateNodeContext::
    getAttachedDomain(OrgSemKind node) const {
    return VectorOf(GenerateAnyNode(
                        GenerateEnumSet(getAttachedSet(node)), *this))
        .WithMinSize(opts->minAttachedCount)
        .WithMaxSize(opts->maxAttachedCount);
}

Domain<std::vector<prt::AnyNode>> GenerateNodeContext::getSubnodeDomain(
    Domain<prt::AnyNode> filler) const {
    if (opts->maxSubnodeCount) {
        return VectorOf(filler)
            .WithMinSize(opts->minSubnodeCount)
            .WithMaxSize(*opts->maxSubnodeCount);
    } else {
        return VectorOf(filler).WithMinSize(opts->minSubnodeCount);
    }
}


Domain<std::vector<prt::AnyNode>> GenerateNodeContext::getSubnodeDomain(
    OrgSemKind kind) const {
    auto tmp = VectorOf(GenerateAnyNode(getDomain(), rec(kind)))
                   .WithMinSize(getMinSubnodeCount());
    if (auto max = getMaxSubnodeCount(); max) {
        tmp = std::move(tmp).WithMaxSize(*max);
    }
    return std::move(tmp);
}


SemSet GenerateNodeContext::getSubnodeSet() const {
    SemSet result{sliceT<OrgSemKind>()};
    SemSet visited;
    int    markupLayersCount = 0;
    SemSet markupKinds{
        osk::Bold,
        osk::Italic,
        osk::Verbatim,
        osk::Monospace,
        osk::Underline,
        osk::Strike,
    };

    result.excl(SemSet{
        osk::FileTarget,
        osk::CmdArgument,
        osk::CmdArguments,
        osk::ParseError,
        osk::DocumentOptions,
        osk::Empty,
        osk::SubtreeLog,
        osk::Par,
        osk::Row,
    });

    for (auto const& it : steps) {
        if (markupKinds.contains(it.kind)) { ++markupLayersCount; }
    }

    if (2 <= markupLayersCount) { result.excl(markupKinds); }

    for (auto const& it : steps) {
        // if (visited.contains(it.kind)) { __builtin_debugtrap(); }
        visited.incl(it.kind);
        result.excl(it.kind);
        switch (it.kind) {
            case OrgSemKind::Document: {
                result.excl(OrgSemKind::DocumentGroup);
                break;
            }
            case OrgSemKind::Paragraph: {
                result.excl(SemSet{
                    osk::Example,
                    osk::Center,
                    osk::Subtree,
                    osk::Code,
                    osk::CommandGroup,
                    osk::Quote,
                    osk::AdmonitionBlock,
                    osk::Table,
                    osk::TextSeparator,
                    osk::Export,
                    osk::List,
                    osk::Caption,
                    osk::Include,
                    osk::StmtList,
                    // Paragraph can contain newlines, but they are not
                    // arbitrarily generated.
                    osk::Newline,
                });
            }
            default: {
            }
        }
    }

    return result;
}

SemSet GenerateNodeContext::getAttachedSet(OrgSemKind node) const {
    SemSet result;
    result.incl(osk::Caption);

    return result;
}
