#include "tOrgFuzzUtils.hpp"

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
        "[{}] ... {}",
        steps
            | rv::transform([](GenerateNodePath const& p) -> std::string {
                  return fmt("{}:{}", p.kind, p.line);
              })
            | rv::intersperse("->") //
            | rv::join              //
            | rs::to<std::string>(),
        getDomainSet());
}

std::string GenerateNodeContext::indent() const {
    return std::string(steps.size() * 2, ' ');
}

void GenerateNodeContext::debug(const char* function, int line) const {
    std::cerr << indent() << function << " " << format() << "\n";
}

SemSet GenerateNodeContext::getDomainSet() const {
    SemSet result{sliceT<OrgSemKind>()};
    SemSet visited;
    for (auto const& it : steps) {
        // if (visited.contains(it.kind)) { __builtin_debugtrap(); }
        visited.incl(it.kind);
        result.excl(it.kind);
        switch (it.kind) {
            case OrgSemKind::Document: {
                result.excl(OrgSemKind::DocumentOptions);
                result.excl(OrgSemKind::DocumentGroup);
                break;
            }
            default: {
            }
        }
    }

    return result;
}
