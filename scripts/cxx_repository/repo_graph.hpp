#pragma once

#include <boost/graph/adjacency_list.hpp>
#include <unordered_map>
#include <hstd/system/generator.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <absl/log/log.h>

#include "git_interface.hpp"


namespace bg {
using boost::add_edge;
using boost::add_vertex;
using boost::in_degree;
using boost::in_edges;
using boost::num_vertices;
using boost::out_degree;
using boost::out_edges;
using boost::source;
using boost::target;
using boost::vertices;
}; // namespace bg

struct CommitInfo {
    git_oid oid;
    bool    is_main = false;
};

struct CommitEdge {};


struct CommitGraph {
    using Graph = boost::adjacency_list<
        boost::vecS,
        boost::vecS,
        boost::bidirectionalS,
        CommitInfo,
        CommitEdge>;

    using GraphTraits = boost::graph_traits<Graph>;
    using VDesc       = GraphTraits::vertex_descriptor;
    using EDesc       = GraphTraits::edge_descriptor;

    Graph                              g;
    std::unordered_map<git_oid, VDesc> rev_map;
    git_oid                            first_oid;

  public:
    inline int in_degree(VDesc v) const { return bg::in_degree(v, g); }
    inline int out_degree(VDesc v) const { return bg::out_degree(v, g); }
    inline CommitInfo& operator[](VDesc v) { return g[v]; }
    inline CommitEdge& operator[](EDesc e) { return g[e]; }
    inline VDesc operator[](git_oid const& oid) { return get_desc(oid); }
    inline VDesc source(EDesc e) const { return bg::source(e, g); }
    inline VDesc target(EDesc e) const { return bg::target(e, g); }
    inline bool  is_merge(VDesc v) const { return 1 < in_degree(v); }

    hstd::Opt<VDesc> get_base(VDesc v) const;

    hstd::Vec<EDesc> parent_commits(VDesc v) const;

    inline hstd::generator<VDesc> commits() const {
        for (auto [begin, end] = bg::vertices(g); begin != end; ++begin) {
            co_yield *begin;
        }
    }

    /// \brief iterate over pairs commit-base (in this order). Merge
    /// commits are also included in the iteration results, they can be
    /// filtered out using `is_base()` predicate.
    ///
    /// can return empty 'base' commit for starting commits
    hstd::Vec<hstd::Pair<VDesc, hstd::Opt<VDesc>>> commit_pairs() const;


    VDesc get_desc(git_oid const& oid);
    CommitGraph(hstd::SPtr<git_repository> repo, const hstd::Str& branch);

    std::string toGraphviz() const;
};
