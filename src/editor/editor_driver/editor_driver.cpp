#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <editor/editor_lib/common/app_state.hpp>
#include <editor/editor_lib/common/app_init.hpp>


template <typename E, IsVariant Var>
void from_json_variant(CR<Str> variantField, json const& in, Var& out) {
    if (!in.is_object() || !in.contains(variantField)) {
        throw std::domain_error(
            fmt("Input JSON must be an object and have '{}' field",
                variantField));
    }
    if (auto parsed = enum_serde<E>::from_string(in[variantField])) {
        out = variant_from_index<Var>(
            value_domain<E>::ord(parsed.value()));
        std::visit([&](auto& var_item) { from_json(in, var_item); }, out);
    } else {
        throw std::domain_error(
            fmt("'kind' field must be one of {} but got {}",
                enumerator_names<E>(),
                in[variantField].dump()));
    }
}

template <typename E, IsVariant Var>
void to_json_variant(
    CR<Str>    variantField,
    json&      out,
    Var const& in,
    E const&   kind) {

    std::visit([&](auto const& in_item) { to_json(out, in_item); }, in);
    out[variantField] = enum_serde<E>::to_string(kind);
}


struct Action {
    struct MindMap {
        DESC_FIELDS(MindMap, ());
    };

    struct None {
        DESC_FIELDS(None, ());
    };

    struct DocumentModel {
        DESC_FIELDS(DocumentModel, ());
    };


    SUB_VARIANTS(Kind, Data, data, getKind, None, DocumentModel, MindMap);

    Data data;
};

struct DriverConfig {
    Vec<Str> input_paths;
    Str      output_path;
    Action   action;

    DESC_FIELDS(DriverConfig, (input_paths, output_path, action));
};

struct DriverResult {
    struct DocumentDump {
        json main_document;
        json outline_document;
        Str  path;
        DESC_FIELDS(DocumentDump, (main_document, outline_document, path));
    };

    Vec<DocumentDump> document_dumps;


    Action action;
    DESC_FIELDS(DriverResult, (action, document_dumps));
};

void from_json(json const& j, Action& out) {
    from_json_variant<Action::Kind>("kind", j, out.data);
}

void to_json(json& j, Action const& in) {
    to_json_variant("kind", j, in.data, in.getKind());
}


int main(int argc, char** argv) {
    if (argc != 2) {
        throw std::invalid_argument(
            "Expected one argument for the driver execution: json object "
            "for driver config");
    }

    auto config = from_json_eval<DriverConfig>(
        json::parse(readFile(argv[1])));

    qInstallMessageHandler(customMessageHandler);
    editorInitMain();

    OrgStore store;
    for (auto const& file : config.input_paths) {
        auto parsed = sem::parseFile(file, sem::OrgParseParameters{});
        store.addRoot(parsed);
    }

    DriverResult result;
    result.action = config.action;

    switch (config.action.getKind()) {
        case Action::Kind::None: {
            throw std::invalid_argument(
                "No driver action specified: add `action:` field in the "
                "main "
                "JSON.");
        }
        case Action::Kind::DocumentModel: {
            for (auto const& root : store.roots) {
                OrgDocumentModel model{&store, nullptr};
                model.root = root.get();
                DriverResult::DocumentDump dump;
                dump.main_document = dumpModelTree(
                    &model, QModelIndex(), [](QModelIndex const&) {
                        return json();
                    });
                result.document_dumps.push_back(dump);
            }
        }
    }

    writeFile(
        fs::path{config.output_path.toBase()},
        to_json_eval(result).dump(2));
}
