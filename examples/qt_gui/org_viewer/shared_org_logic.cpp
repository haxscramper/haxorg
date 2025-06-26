#include "shared_org_logic.hpp"
#include <haxorg/sem/SemOrgCereal.hpp>

const std::unordered_set<std::string> COMPLETED_TASK_SET = {
    "DONE",
    "FAILED",
    "COMPLETED",
    "CANCELED",
};

const SemSet AGENDA_NODE_TYPES = {
    OrgSemKind::Subtree,
    OrgSemKind::Document,
    OrgSemKind::Directory,
    OrgSemKind::File,
    OrgSemKind::Symlink,
};


org::sem::SemId<org::sem::Org> loadCachedImmNode(
    const fs::path& infile,
    const fs::path& graph_path,
    const fs::path& context_path,
    const fs::path& epoch_path,
    const fs::path& cache_file,
    bool            use_cache) {
    auto dir_opts   = org::OrgDirectoryParseParameters::shared();
    auto parse_opts = org::OrgParseParameters::shared();

    if (!use_cache || checkOrgFilesChanged(infile, cache_file)
        || !fs::exists(graph_path) || !fs::exists(context_path)
        || !fs::exists(epoch_path)) {

        dir_opts->getParsedNode = [&](const std::string& path)
            -> org::sem::SemId<org::sem::Org> {
            try {
                std::ifstream file(path);
                std::string   content(
                    (std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());
                return org::parseStringOpts(content, parse_opts);
            } catch (const std::exception& e) {
                return org::sem::SemId<org::sem::Empty>::New();
            }
        };

        auto node = org::parseDirectoryOpts(infile.string(), dir_opts);
        auto initial_context = org::initImmutableAstContext();
        auto version         = initial_context->addRoot(node.value());

        auto graph_state = org::graph::MapGraphState::FromAstContext(
            version.getContext());
        auto conf = org::graph::MapConfig::shared();
        auto root = version.getRootAdapter();

        graph_state->addNodeRec(version.getContext(), root, conf);

        std::ofstream graph_file(graph_path, std::ios::binary);
        auto graph_data = org::imm::serializeToText(graph_state->graph);
        graph_file.write(
            reinterpret_cast<const char*>(graph_data.data()),
            graph_data.size());

        std::ofstream context_file(context_path, std::ios::binary);
        auto          context_data = org::imm::serializeToText(
            version.getContext());
        context_file.write(
            reinterpret_cast<const char*>(context_data.data()),
            context_data.size());

        std::ofstream epoch_file(epoch_path, std::ios::binary);
        auto epoch_data = org::imm::serializeToText(version.getEpoch());
        epoch_file.write(
            reinterpret_cast<const char*>(epoch_data.data()),
            epoch_data.size());

        writeOrgFileCache(infile, cache_file);

        return node.value();
    } else {
        auto initial_context = org::initImmutableAstContext();

        std::ifstream        context_file(context_path, std::ios::binary);
        std::vector<uint8_t> context_data(
            (std::istreambuf_iterator<char>(context_file)),
            std::istreambuf_iterator<char>());
        org::imm::serializeFromText(context_data, initial_context);

        auto version = initial_context->getEmptyVersion();

        std::ifstream        epoch_file(epoch_path, std::ios::binary);
        std::vector<uint8_t> epoch_data(
            (std::istreambuf_iterator<char>(epoch_file)),
            std::istreambuf_iterator<char>());
        org::imm::serializeFromText(epoch_data, version.getEpoch());

        auto node = initial_context.get(version.getRoot());

        auto graph_state = org::graphMapGraphState::FromAstContextStatic(
            version.getContext());

        std::ifstream        graph_file(graph_path, std::ios::binary);
        std::vector<uint8_t> graph_data(
            (std::istreambuf_iterator<char>(graph_file)),
            std::istreambuf_iterator<char>());
        org::serializeMapGraphFromText(graph_data, graph_state.graph);

        return node;
    }
}

hstd::Str OrgAgendaNode::getAgeDisplay() const {
    int seconds = getAgeSeconds();

    if (seconds == 0) { return ""; }

    hstd::Vec<hstd::Pair<std::string, int>> units = {
        {"y", 365 * 24 * 3600},
        {"mo", 30 * 24 * 3600},
        {"w", 7 * 24 * 3600},
        {"d", 24 * 3600},
        {"h", 3600},
        {"m", 60},
        {"s", 1},
    };

    hstd::Vec<std::string> parts;
    for (const auto& [unit_name, unit_seconds] : units) {
        if (seconds >= unit_seconds) {
            int count = seconds / unit_seconds;
            parts.push_back(std::format("{}{}", count, unit_name));
            seconds %= unit_seconds;
            if (parts.size() == 2) { break; }
        }
    }

    std::string result;
    for (const auto& part : parts) { result += part; }

    return parts.empty() ? "0s" : result;
}

OrgAgendaNode::OrgAgendaNode(
    org::sem::SemId<org::sem::Org> data,
    OrgAgendaNode*                 parent,
    hstd::Vec<OrgAgendaNode*>      children)
    : data{data}, parent{parent}, children{children} {
    auto kind = data->getKind();
    auto it   = std::find(
        AGENDA_NODE_TYPES.begin(), AGENDA_NODE_TYPES.end(), kind);
    assert(it != AGENDA_NODE_TYPES.end());
}

hstd::Vec<hstd::Pair<hstd::UserTime, hstd::UserTime>> OrgAgendaNode::
    getClockPeriods(bool recursive) const {
    hstd::Vec<hstd::Pair<hstd::UserTime, hstd::UserTime>> result;

    std::function<void(const OrgAgendaNode*)> aux =
        [&](const OrgAgendaNode* node) {
            if (auto subtree = data.asOpt<org::sem::Subtree>()) {
                auto periods = subtree->getTimePeriods(
                    {org::sem::SubtreePeriod::Kind::Clocked});
                for (const auto& time : periods) {
                    if (time.to) {
                        result.push_back({time.from, time.to.value()});
                    }
                }
            }

            if (recursive) {
                for (const auto& sub : node->children) { aux(sub); }
            }
        };

    aux(this);
    return result;
}

int OrgAgendaNode::getAgeSeconds() const {
    if (auto subtree = data.asOpt<org::sem::Subtree>()) {
        auto created = subtree->getTimePeriods(
            {org::sem::SubtreePeriod::Kind::Created});
        if (!created.empty()) {
            auto created_time = created[0].from.time;
            auto now_civil    = cctz::convert(
                std::chrono::system_clock::now(), cctz::utc_time_zone());
            auto duration_civil = now_civil - created_time;
            return duration_civil;
        }
    }
    return 0;
}

std::unordered_map<std::string, double> getOrgFileTimes(
    const fs::path& infile) {
    std::unordered_map<std::string, double> current_times;

    for (const auto& entry : fs::directory_iterator(infile)) {
        if (entry.path().extension() == ".org") {
            auto ftime = fs::last_write_time(entry.path());
            auto sctp  = std::chrono::time_point_cast<
                 std::chrono::system_clock::duration>(
                ftime - fs::file_time_type::clock::now()
                + std::chrono::system_clock::now());
            auto time_t = std::chrono::system_clock::to_time_t(sctp);
            current_times[entry.path().string()] = static_cast<double>(
                time_t);
        }
    }

    return current_times;
}
