#include "repo_graph.hpp"

CommitGraph::CommitGraph(SPtr<git_repository> repo) {
    SPtr<git_revwalk> walker = git::revwalk_new(repo.get()).value();
    git::revwalk_sorting(walker.get(), GIT_SORT_NONE);

    git::revwalk_push_head(walker.get());

    git_oid oid;
    while (git_revwalk_next(&oid, walker.get()) == 0) {
        auto             current = get_desc(oid);
        SPtr<git_commit> commit  = git::commit_lookup(repo.get(), &oid)
                                      .value();

        for (int i = 0; i < git::commit_parentcount(commit.get()); ++i) {
            auto oid        = *git::commit_parent_id(commit.get(), i);
            auto parent     = get_desc(oid);
            auto [edge, ok] = bg::add_edge(parent, current, g);
            if (i == 0) {
                g[edge].is_main = true;
            }
        }

        int main_in_count = 0;
        for (auto [begin, end] = bg::in_edges(current, g); begin != end;
             ++begin) {
            auto e = *begin;
            if (g[e].is_main) {
                ++main_in_count;
            }
        }

        if (1 < main_in_count) {
            assert(false);
        }
    }

    VDesc head;
    for (auto [begin, end] = bg::vertices(g); begin != end; ++begin) {
        VDesc v = *begin;
        if (boost::out_degree(v, g) == 0) {
            head = v;
        } else {
            int in_count = 0;
            for (auto [begin, end] = bg::in_edges(v, g); begin != end;
                 ++begin) {
                ++in_count;
            }
            if (in_count == 0) {
                // TODO somehow handle multiple starting commits - they are
                // not particularly useful, but might come in handy for
                // some analytics
            }
        }
    }

    VDesc current = head;
    while (boost::in_degree(current, g) != 0) {
        main_path.push_back(current);
        main_set.insert(current);
        for (auto [begin, end] = bg::in_edges(current, g); begin != end;
             ++begin) {
            auto e = *begin;
            if (g[e].is_main) {
                current = bg::source(e, g);
            }
        }
    }
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
