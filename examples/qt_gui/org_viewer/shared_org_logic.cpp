#include "shared_org_logic.hpp"
#include <haxorg/sem/SemOrgCereal.hpp>
#include <hstd/stdlib/JsonSerde.hpp>

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
                return org::parseStringOpts(
                    hstd::readFile(path), parse_opts);
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

        hstd::writeFile(
            graph_path, org::imm::serializeToText(graph_state->graph));
        hstd::writeFile(
            context_path, org::imm::serializeToText(version.getContext()));
        hstd::writeFile(
            epoch_path, org::imm::serializeToText(version.getEpoch()));

        writeOrgFileCache(infile, cache_file);

        return node.value();
    } else {
        auto initial_context = org::initImmutableAstContext();

        std::string context_data = hstd::readFile(context_path);
        org::imm::serializeFromText(context_data, initial_context);

        auto version = initial_context->getEmptyVersion();

        std::string epoch_data = hstd::readFile(epoch_path);
        org::imm::serializeFromText(epoch_data, version.getEpoch());

        auto node = initial_context->get(version.getRoot());

        auto graph_state = org::graph::MapGraphState::FromAstContext(
            version.getContext());

        std::string graph_data = hstd::readFile(graph_path);
        org::imm::serializeFromText(graph_data, graph_state->graph);

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

void OrgAgendaNode::pushBack(OrgAgendaNode::Ptr other) {
    auto kind = other->data->getKind();
    assert(AGENDA_NODE_TYPES.contains(kind));
    children.push_back(other);
}

OrgAgendaNode::OrgAgendaNode(
    org::sem::SemId<org::sem::Org> data,
    OrgAgendaNode::WPtr            parent,
    hstd::Vec<OrgAgendaNode::Ptr>  children)
    : data{data}, parent{parent}, children{children} {
    LOGIC_ASSERTION_CHECK_FMT(
        AGENDA_NODE_TYPES.contains(data->getKind()),
        "{}",
        data->getKind());
}

hstd::Vec<hstd::Pair<hstd::UserTime, hstd::UserTime>> OrgAgendaNode::
    getClockPeriods(bool recursive) const {
    hstd::Vec<hstd::Pair<hstd::UserTime, hstd::UserTime>> result;

    std::function<void(OrgAgendaNode::Ptr const&)> aux =
        [&](OrgAgendaNode::Ptr const& node) {
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

    aux(mshared_from_this());
    return result;
}

hstd::Str OrgAgendaNode::getTitle() const {
    if (auto subtree = data.asOpt<org::sem::Subtree>()) {
        return subtree->getCleanTitle();
    } else if (auto file = data.asOpt<org::sem::File>()) {
        return file->relPath;
    } else if (auto dir = data.asOpt<org::sem::Directory>()) {
        return dir->relPath;
    } else {
        return hstd::fmt1(data->getKind());
    }
}

hstd::Pair<int, int> OrgAgendaNode::getRecursiveCompletion() const {
    int nom   = 0;
    int denom = 0;

    std::function<void(OrgAgendaNode::Ptr const&)> aux =
        [&](OrgAgendaNode::Ptr const& node) {
            auto todo = node->getTodo();
            if (!todo.empty()) {
                if (COMPLETED_TASK_SET.contains(todo)) {
                    nom++;
                    denom++;
                } else {
                    denom++;
                }
            }

            for (const auto& sub : node->children) { aux(sub); }
        };

    aux(mshared_from_this());
    return {nom, denom};
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

    auto insert_time = [&](fs::path const& path) {
        auto ftime = fs::last_write_time(path);
        auto sctp  = std::chrono::time_point_cast<
             std::chrono::system_clock::duration>(
            ftime - fs::file_time_type::clock::now()
            + std::chrono::system_clock::now());
        auto time_t = std::chrono::system_clock::to_time_t(sctp);
        current_times[path.string()] = static_cast<double>(time_t);
    };

    if (fs::is_directory(infile)) {
        for (const auto& entry : fs::directory_iterator(infile)) {
            if (entry.path().extension() == ".org") {
                insert_time(entry.path());
            }
        }
    } else if (fs::is_regular_file(infile)) {
        insert_time(infile);
    } else if (fs::is_symlink(infile)) {
        fs::path target = fs::read_symlink(infile);
        while (fs::is_symlink(target)) {
            target = fs::read_symlink(target);
        }
        insert_time(target);
    }

    return current_times;
}

bool checkOrgFilesChanged(
    const fs::path& infile,
    const fs::path& cache_file) {
    auto current_times = getOrgFileTimes(infile);

    if (fs::exists(cache_file)) {
        json cached_times = json::parse(hstd::readFile(cache_file));
        std::unordered_map<std::string, double> cached_map;
        hstd::from_json_eval(cached_times, cached_map);

        return current_times != cached_map;
    } else {
        return true;
    }
}

void writeOrgFileCache(
    const fs::path& infile,
    const fs::path& cache_file) {
    auto current_times = getOrgFileTimes(infile);

    hstd::writeFile(cache_file, hstd::to_json_eval(current_times).dump(2));
}
OrgAgendaNode::Ptr buildAgendaTree(
    org::sem::SemId<org::sem::Org> const& node,
    OrgAgendaNode::WPtr                   parent) {
    auto result = OrgAgendaNode::shared(node, parent);

    for (const auto& sub : node) {
        auto kind = sub->getKind();
        if (AGENDA_NODE_TYPES.contains(kind)) {
            auto added              = buildAgendaTree(sub, result);
            auto [completed, total] = added->getRecursiveCompletion();
            if (total != 0) { result->pushBack(added); }
        }
    }

    return result;
}
