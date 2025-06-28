#pragma once

// #define NDEBUG 0

#include <haxorg/sem/SemOrg.hpp>
#include <haxorg/sem/SemBaseApi.hpp>
#include <haxorg/sem/ImmOrg.hpp>
#include <haxorg/sem/ImmOrgGraph.hpp>

#include <unordered_map>
#include <string>
#include <filesystem>
#include <chrono>
#include <optional>
#include <nlohmann/json.hpp>
#include <hstd/stdlib/Filesystem.hpp>

namespace fs = std::filesystem;

std::unordered_map<std::string, double> getOrgFileTimes(
    const fs::path& infile);

bool checkOrgFilesChanged(
    const fs::path& infile,
    const fs::path& cache_file);

void writeOrgFileCache(const fs::path& infile, const fs::path& cache_file);

org::sem::SemId<org::sem::Org> loadCachedImmNode(
    const fs::path& infile,
    const fs::path& graph_path,
    const fs::path& context_path,
    const fs::path& epoch_path,
    const fs::path& cache_file,
    bool            use_cache = true);

class OrgAgendaNode : public hstd::SharedPtrApi<OrgAgendaNode> {
  public:
    org::sem::SemId<org::sem::Org> data;
    OrgAgendaNode::WPtr            parent;
    hstd::Vec<OrgAgendaNode::Ptr>  children;

    OrgAgendaNode(
        org::sem::SemId<org::sem::Org> data,
        OrgAgendaNode::WPtr            parent   = OrgAgendaNode::WPtr{},
        hstd::Vec<OrgAgendaNode::Ptr>  children = {});

    std::string getPriority() const {
        if (auto subtree = data.asOpt<org::sem::Subtree>()) {
            return subtree->priority.value_or("");
        } else {
            return "";
        }
    }

    hstd::Vec<hstd::Pair<hstd::UserTime, hstd::UserTime>> getClockPeriods(
        bool recursive = false) const;

    int getClockedSeconds(bool recursive = true) const {
        int  result  = 0;
        auto periods = getClockPeriods(recursive);

        for (const auto& [from, to] : periods) {
            result += to.time - from.time;
        }

        return result;
    }

    bool isEvent() const {
        return getScheduledTime().has_value()
            || getDeadlineTime().has_value();
    }

    hstd::Opt<std::chrono::seconds> getDuration() const {

        if (auto subtree = data.asOpt<org::sem::Subtree>()) {
            for (auto const& prop : org::getSubtreeProperties<
                     org::sem::NamedProperty::Effort>(subtree)) {
                return std::chrono::seconds(
                    (prop.hours * 60 + prop.minutes) * 60);
            }
        }
        return std::nullopt;
    }

    hstd::Opt<org::sem::Time::Repeat> getScheduledRepeat() const {
        if (auto subtree = data.asOpt<org::sem::Subtree>()) {
            if (subtree->scheduled) {
                return subtree->scheduled.value()->getStatic().repeat.get(
                    0);
            }
        }
        return std::nullopt;
    }

    hstd::Opt<org::sem::Time::Repeat> getDeadlineRepeat() const {
        if (auto subtree = data.asOpt<org::sem::Subtree>()) {
            if (subtree->deadline) {
                return subtree->deadline.value()->getStatic().repeat.get(
                    0);
            }
        }
        return std::nullopt;
    }

    hstd::Str getTitle() const;

    hstd::Opt<hstd::UserTime> getScheduledTime() const {
        if (auto subtree = data.asOpt<org::sem::Subtree>()) {
            if (subtree->scheduled) {
                return subtree->scheduled.value()->getStaticTime();
            }
        }
        return std::nullopt;
    }

    hstd::Opt<hstd::UserTime> getDeadlineTime() const {
        if (auto subtree = data.asOpt<org::sem::Subtree>()) {
            if (subtree->deadline) {
                return subtree->deadline.value()->getStaticTime();
            }
        }
        return std::nullopt;
    }

    hstd::Opt<hstd::UserTime> getClosedTime() const {
        if (auto subtree = data.asOpt<org::sem::Subtree>()) {
            if (subtree->closed) {
                return subtree->closed.value()->getStaticTime();
            }
        }
        return std::nullopt;
    }

    hstd::Opt<hstd::UserTime> getCreatedTime() const {
        if (auto subtree = data.asOpt<org::sem::Subtree>()) {
            for (auto const& time : subtree->getTimePeriods(
                     {org::sem::SubtreePeriod::Kind::Created})) {
                return time.from;
            }
        }
        return std::nullopt;
    }

    hstd::Str getTodo() const {
        if (auto subtree = data.asOpt<org::sem::Subtree>()) {
            return subtree->todo.value_or("");
        } else {
            return "";
        }
    }

    hstd::Pair<int, int> getRecursiveCompletion() const;

    int getPriorityOrder() const {
        std::string priority = getPriority();
        static const std::unordered_map<std::string, int>
            priority_order = {
                {"X", 0},
                {"S", 1},
                {"A", 2},
                {"B", 3},
                {"C", 4},
                {"D", 5},
                {"E", 6},
                {"F", 7}};

        auto it = priority_order.find(priority);
        return it != priority_order.end() ? it->second : -1;
    }

    hstd::Vec<hstd::Str> getTags() const {
        if (auto subtree = data.asOpt<org::sem::Subtree>()) {
            hstd::Vec<hstd::Str> result;
            for (const auto& tag : subtree->tags) {
                auto flat_tags = tag->text.getFlatHashes();
                for (const auto& flat : flat_tags) {
                    hstd::Str joined;
                    for (size_t i = 0; i < flat.tags.size(); ++i) {
                        if (i > 0) { joined += "##"; }
                        joined += flat.tags[i];
                    }
                    result.push_back(joined);
                }
            }
            return result;
        }
        return {};
    }

    int getAgeSeconds() const;

    hstd::Str getAgeDisplay() const;

    void pushBack(OrgAgendaNode::Ptr other);

    auto begin() { return children.begin(); }
    auto end() { return children.end(); }
    auto begin() const { return children.begin(); }
    auto end() const { return children.end(); }
};

OrgAgendaNode::Ptr buildAgendaTree(
    org::sem::SemId<org::sem::Org> const& node,
    OrgAgendaNode::WPtr                   parent = OrgAgendaNode::WPtr{});
