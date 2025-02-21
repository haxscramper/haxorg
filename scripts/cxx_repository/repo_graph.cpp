#include "repo_graph.hpp"

#include <boost/graph/graphml.hpp>
#include <boost/graph/graphviz.hpp>
#include <absl/log/log.h>

using namespace hstd;

CommitGraph::CommitGraph(
    SPtr<git_repository> repo,
    Str const&           branch_name) {
    SPtr<git_revwalk> walker = git::revwalk_new(repo.get()).value();
    git::revwalk_sorting(walker.get(), GIT_SORT_NONE);

    SPtr<git_reference>
        branch = git::branch_lookup(repo.get(), branch_name).value();
    GitResult<SPtr<git_commit>> first_commit = git::reference_peel(
        branch.get());
    git_oid_cpy(&first_oid, git_commit_id(first_commit.value().get()));
    git_revwalk_push(walker.get(), &first_oid);

    LOG(INFO) << std::format(
        "[repo-graph] First commit on branch '{}' is '{}'",
        branch_name,
        first_oid);

    git_oid oid;
    while (git_revwalk_next(&oid, walker.get()) == 0) {
        VDesc            current = get_desc(oid);
        SPtr<git_commit> commit  = git::commit_lookup(repo.get(), &oid)
                                      .value();

        if (git_oid_cmp(&oid, &first_oid) == 0) {
            g[current].is_main = true;
        }

        // Extract DAG graph of commits from the history
        for (int i = 0; i < git::commit_parentcount(commit.get()); ++i) {
            auto oid        = *git::commit_parent_id(commit.get(), i);
            auto parent     = get_desc(oid);
            auto [edge, ok] = bg::add_edge(parent, current, g);
            if (i == 0) { g[parent].is_main = true; }
        }
    }
}


std::string CommitGraph::toGraphviz() const {
    std::stringstream         os;
    boost::dynamic_properties dp;

    dp //
        .property("node_id", get(boost::vertex_index, g))
        .property(
            "splines",
            boost::make_constant_property<Graph*>(std::string("polyline")))
        .property(
            "shape",
            boost::make_constant_property<Graph::vertex_descriptor>(
                std::string("rect")))
        .property(
            "color",
            make_transform_value_property_map<std::string>(
                [&](CommitInfo const& prop) -> std::string {
                    return prop.is_main ? "green" : "yellow";
                },
                get(boost::vertex_bundle, g)))
        .property(
            "label",
            make_transform_value_property_map<std::string>(
                [&](CommitInfo const& prop) -> std::string {
                    return fmt("{}", prop.oid).substr(0, 8);
                },
                get(boost::vertex_bundle, g)));


    write_graphviz_dp(os, g, dp);

    return os.str();
}

CommitGraph::VDesc CommitGraph::get_desc(CR<git_oid> oid) {
    auto iter = rev_map.find(oid);
    if (iter != rev_map.end()) {
        return iter->second;

    } else {
        VDesc vert   = bg::add_vertex(g);
        g[vert].oid  = oid;
        rev_map[oid] = vert;
        return vert;
    }
}
Opt<CommitGraph::VDesc> CommitGraph::get_base(VDesc v) const {
    for (auto in : parent_commits(v)) {
        if (g[bg::target(in, g)].is_main) { return source(in); }
    }

    return Opt<VDesc>{};
}

Vec<CommitGraph::EDesc> CommitGraph::parent_commits(VDesc v) const {
    Vec<EDesc> result;
    for (auto [begin, end] = bg::in_edges(v, g); begin != end; ++begin) {
        result.push_back(*begin);
    }
    return result;
}

auto CommitGraph::commit_pairs() const -> Vec<Pair<VDesc, Opt<VDesc>>> {
    Vec<Pair<VDesc, Opt<VDesc>>> result;
    VDesc                        current = rev_map.at(first_oid);
    while (true) {
        Opt<VDesc> prev = get_base(current);
        result.push_back({current, prev});
        if (prev) {
            current = *prev;
        } else {
            break;
        }
    }

    std::reverse(result.begin(), result.end());
    return result;
}
