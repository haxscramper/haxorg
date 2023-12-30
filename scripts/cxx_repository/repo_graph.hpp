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
};

struct CommitEdge {
    bool is_main = false;
};


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

    Graph g;

    std::unordered_map<git_oid, VDesc> rev_map;
    // TODO check if this heurstics is reliable and covers all the
    // necessary cases
    /// For merge commits 'main' is the first commit that was merged in the
    /// sequence -- one that everything else was merged *to*.
    std::unordered_set<VDesc> main_set;


  public:
    inline int in_degree(VDesc v) const { return bg::in_degree(v, g); }
    inline int out_degree(VDesc v) const { return bg::out_degree(v, g); }
    inline CommitInfo& operator[](VDesc v) { return g[v]; }
    inline CommitEdge& operator[](EDesc e) { return g[e]; }
    inline VDesc operator[](CR<git_oid> oid) { return get_desc(oid); }
    inline VDesc source(EDesc e) const { return bg::source(e, g); }
    inline VDesc target(EDesc e) const { return bg::target(e, g); }
    inline bool  is_merge(VDesc v) const { return 1 < in_degree(v); }

    inline bool is_main(VDesc v) const {
        return main_set.find(v) != main_set.end();
    }

    inline Opt<VDesc> get_base(VDesc v) const {
        for (auto in : parent_commits(v)) {
            if (g[in].is_main) {
                return source(in);
            }
        }

        return Opt<VDesc>{};
    }

    inline generator<EDesc> parent_commits(VDesc v) const {
        for (auto [begin, end] = bg::in_edges(v, g); begin != end;
             ++begin) {
            co_yield *begin;
        }
    }

    inline generator<EDesc> next_commits(VDesc v) const {
        for (auto [begin, end] = bg::out_edges(v, g); begin != end;
             ++begin) {
            co_yield *begin;
        }
    }

    inline generator<VDesc> commits() const {
        for (auto [begin, end] = bg::vertices(g); begin != end; ++begin) {
            co_yield *begin;
        }
    }

    /// \brief iterate over pairs commit-base (in this order). Merge
    /// commits are also included in the iteration results, they can be
    /// filtered out using `is_base()` predicate.
    ///
    /// can return empty 'base' commit for starting commits
    inline generator<Pair<VDesc, Opt<VDesc>>> commit_pairs() const {
        std::unordered_set<VDesc> tried;
        for (auto v : commits()) {
            if (tried.find(v) == tried.end()) {
                tried.insert(v);
                Pair<VDesc, Opt<VDesc>> value{v, get_base(v)};
                co_yield value;
            }
        }
    }


    VDesc get_desc(CR<git_oid> oid);
    CommitGraph(SPtr<git_repository> repo);

    std::string toGraphviz() const;
};
