#pragma once

#include <hstd/stdlib/Func.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <hstd/stdlib/Json.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/depth_first_search.hpp>

template <typename Graph>
struct boost_lambda_bfs_visitor : public boost::default_bfs_visitor {
    using VD = typename boost::graph_traits<Graph>::vertex_descriptor;
    using ED = typename boost::graph_traits<Graph>::edge_descriptor;

    Func<void(CR<VD>, CR<Graph>)> initialize_vertex_fn;
    Func<void(CR<VD>, CR<Graph>)> discover_vertex_fn;
    Func<void(CR<VD>, CR<Graph>)> examine_vertex_fn;
    Func<void(CR<ED>, CR<Graph>)> examine_edge_fn;
    Func<void(CR<ED>, CR<Graph>)> tree_edge_fn;
    Func<void(CR<ED>, CR<Graph>)> non_tree_edge_fn;
    Func<void(CR<ED>, CR<Graph>)> gray_target_fn;
    Func<void(CR<ED>, CR<Graph>)> black_target_fn;
    Func<void(CR<VD>, CR<Graph>)> finish_vertex_fn;


    // clang-format off
    void initialize_vertex                     (VD v, CR<Graph> g) { if (initialize_vertex_fn) { initialize_vertex_fn               (v, g); } }
    void discover_vertex                       (VD v, CR<Graph> g) { if (discover_vertex_fn) { discover_vertex_fn                   (v, g); } }
    void examine_vertex                        (VD v, CR<Graph> g) { if (examine_vertex_fn) { examine_vertex_fn                     (v, g); } }
    void examine_edge                          (ED e, CR<Graph> g) { if (examine_edge_fn) { examine_edge_fn                         (e, g); } }
    void tree_edge                             (ED e, CR<Graph> g) { if (tree_edge_fn) { tree_edge_fn                               (e, g); } }
    void non_tree_edge                         (ED e, CR<Graph> g) { if (non_tree_edge_fn) { non_tree_edge_fn                       (e, g); } }
    void gray_target                           (ED e, CR<Graph> g) { if (gray_target_fn) { gray_target_fn                           (e, g); } }
    void black_target                          (ED e, CR<Graph> g) { if (black_target_fn) { black_target_fn                         (e, g); } }
    void finish_vertex                         (VD v, CR<Graph> g) { if (finish_vertex_fn) { finish_vertex_fn                       (v, g); } }

    boost_lambda_bfs_visitor &set_initialize_vertex (Func<void (CR<VD>, CR<Graph>)> fn) { initialize_vertex_fn = std::move (fn); return *this; }
    boost_lambda_bfs_visitor &set_discover_vertex   (Func<void (CR<VD>, CR<Graph>)> fn) { discover_vertex_fn = std::move   (fn); return *this; }
    boost_lambda_bfs_visitor &set_examine_vertex    (Func<void (CR<VD>, CR<Graph>)> fn) { examine_vertex_fn = std::move    (fn); return *this; }
    boost_lambda_bfs_visitor &set_examine_edge      (Func<void (CR<ED>, CR<Graph>)> fn) { examine_edge_fn = std::move      (fn); return *this; }
    boost_lambda_bfs_visitor &set_tree_edge         (Func<void (CR<ED>, CR<Graph>)> fn) { tree_edge_fn = std::move         (fn); return *this; }
    boost_lambda_bfs_visitor &set_non_tree_edge     (Func<void (CR<ED>, CR<Graph>)> fn) { non_tree_edge_fn = std::move     (fn); return *this; }
    boost_lambda_bfs_visitor &set_gray_target       (Func<void (CR<ED>, CR<Graph>)> fn) { gray_target_fn = std::move       (fn); return *this; }
    boost_lambda_bfs_visitor &set_black_target      (Func<void (CR<ED>, CR<Graph>)> fn) { black_target_fn = std::move      (fn); return *this; }
    boost_lambda_bfs_visitor &set_finish_vertex     (Func<void (CR<VD>, CR<Graph>)> fn) { finish_vertex_fn = std::move     (fn); return *this; }
    // clang-format on
};


template <typename Graph>
struct boost_lambda_dfs_visitor : public boost::default_dfs_visitor {
    using VD = typename boost::graph_traits<Graph>::vertex_descriptor;
    using ED = typename boost::graph_traits<Graph>::edge_descriptor;

    Func<void(CR<VD>, CR<Graph>)> initialize_vertex_fn;
    Func<void(CR<VD>, CR<Graph>)> start_vertex_fn;
    Func<void(CR<VD>, CR<Graph>)> discover_vertex_fn;
    Func<void(CR<ED>, CR<Graph>)> examine_edge_fn;
    Func<void(CR<ED>, CR<Graph>)> tree_edge_fn;
    Func<void(CR<ED>, CR<Graph>)> back_edge_fn;
    Func<void(CR<ED>, CR<Graph>)> forward_or_cross_edge_fn;
    Func<void(CR<ED>, CR<Graph>)> finish_edge_fn;
    Func<void(CR<VD>, CR<Graph>)> finish_vertex_fn;

    // clang-format off
    void initialize_vertex                         (VD v, CR<Graph> g) { if (initialize_vertex_fn) { initialize_vertex_fn                   (v, g); } }
    void start_vertex                              (VD v, CR<Graph> g) { if (start_vertex_fn) { start_vertex_fn                             (v, g); } }
    void discover_vertex                           (VD v, CR<Graph> g) { if (discover_vertex_fn) { discover_vertex_fn                       (v, g); } }
    void examine_edge                              (ED e, CR<Graph> g) { if (examine_edge_fn) { examine_edge_fn                             (e, g); } }
    void tree_edge                                 (ED e, CR<Graph> g) { if (tree_edge_fn) { tree_edge_fn                                   (e, g); } }
    void back_edge                                 (ED e, CR<Graph> g) { if (back_edge_fn) { back_edge_fn                                   (e, g); } }
    void forward_or_cross_edge                     (ED e, CR<Graph> g) { if (forward_or_cross_edge_fn) { forward_or_cross_edge_fn           (e, g); } }
    void finish_edge                               (ED e, CR<Graph> g) { if (finish_edge_fn) { finish_edge_fn                               (e, g); } }
    void finish_vertex                             (VD v, CR<Graph> g) { if (finish_vertex_fn) { finish_vertex_fn                           (v, g); } }

    boost_lambda_dfs_visitor &set_initialize_vertex     (Func<void (CR<VD>, CR<Graph>)> fn) { initialize_vertex_fn = std::move     (fn); return *this; }
    boost_lambda_dfs_visitor &set_start_vertex          (Func<void (CR<VD>, CR<Graph>)> fn) { start_vertex_fn = std::move          (fn); return *this; }
    boost_lambda_dfs_visitor &set_discover_vertex       (Func<void (CR<VD>, CR<Graph>)> fn) { discover_vertex_fn = std::move       (fn); return *this; }
    boost_lambda_dfs_visitor &set_examine_edge          (Func<void (CR<ED>, CR<Graph>)> fn) { examine_edge_fn = std::move          (fn); return *this; }
    boost_lambda_dfs_visitor &set_tree_edge             (Func<void (CR<ED>, CR<Graph>)> fn) { tree_edge_fn = std::move             (fn); return *this; }
    boost_lambda_dfs_visitor &set_back_edge             (Func<void (CR<ED>, CR<Graph>)> fn) { back_edge_fn = std::move             (fn); return *this; }
    boost_lambda_dfs_visitor &set_forward_or_cross_edge (Func<void (CR<ED>, CR<Graph>)> fn) { forward_or_cross_edge_fn = std::move (fn); return *this; }
    boost_lambda_dfs_visitor &set_finish_edge           (Func<void (CR<ED>, CR<Graph>)> fn) { finish_edge_fn = std::move           (fn); return *this; }
    boost_lambda_dfs_visitor &set_finish_vertex         (Func<void (CR<VD>, CR<Graph>)> fn) { finish_vertex_fn = std::move         (fn); return *this; }
    // clang-format on
};

template <typename Graph>
struct boost_lambda_dijkstra_visitor {
    using VD = typename boost::graph_traits<Graph>::vertex_descriptor;
    using ED = typename boost::graph_traits<Graph>::edge_descriptor;

    Func<void(CR<VD>, CR<Graph>)> initialize_vertex_fn;
    Func<void(CR<VD>, CR<Graph>)> examine_vertex_fn;
    Func<void(CR<ED>, CR<Graph>)> examine_edge_fn;
    Func<void(CR<VD>, CR<Graph>)> discover_vertex_fn;
    Func<void(CR<ED>, CR<Graph>)> edge_relaxed_fn;
    Func<void(CR<ED>, CR<Graph>)> edge_not_relaxed_fn;
    Func<void(CR<VD>, CR<Graph>)> finish_vertex_fn;

    // clang-format off
    void initialize_vertex (VD v, CR<Graph> g) { if (initialize_vertex_fn) { initialize_vertex_fn (v, g); } }
    void examine_vertex    (VD v, CR<Graph> g) { if (examine_vertex_fn) { examine_vertex_fn       (v, g); } }
    void examine_edge      (ED e, CR<Graph> g) { if (examine_edge_fn) { examine_edge_fn           (e, g); } }
    void discover_vertex   (VD v, CR<Graph> g) { if (discover_vertex_fn) { discover_vertex_fn     (v, g); } }
    void edge_relaxed      (ED e, CR<Graph> g) { if (edge_relaxed_fn) { edge_relaxed_fn           (e, g); } }
    void edge_not_relaxed  (ED e, CR<Graph> g) { if (edge_not_relaxed_fn) { edge_not_relaxed_fn   (e, g); } }
    void finish_vertex     (VD v, CR<Graph> g) { if (finish_vertex_fn) { finish_vertex_fn         (v, g); } }

    boost_lambda_dijkstra_visitor &set_initialize_vertex (Func<void (CR<VD>, CR<Graph>)> fn) { initialize_vertex_fn = std::move (fn); return *this; }
    boost_lambda_dijkstra_visitor &set_examine_vertex    (Func<void (CR<VD>, CR<Graph>)> fn) { examine_vertex_fn = std::move    (fn); return *this; }
    boost_lambda_dijkstra_visitor &set_examine_edge      (Func<void (CR<ED>, CR<Graph>)> fn) { examine_edge_fn = std::move      (fn); return *this; }
    boost_lambda_dijkstra_visitor &set_discover_vertex   (Func<void (CR<VD>, CR<Graph>)> fn) { discover_vertex_fn = std::move   (fn); return *this; }
    boost_lambda_dijkstra_visitor &set_edge_relaxed      (Func<void (CR<ED>, CR<Graph>)> fn) { edge_relaxed_fn = std::move      (fn); return *this; }
    boost_lambda_dijkstra_visitor &set_edge_not_relaxed  (Func<void (CR<ED>, CR<Graph>)> fn) { edge_not_relaxed_fn = std::move  (fn); return *this; }
    boost_lambda_dijkstra_visitor &set_finish_vertex     (Func<void (CR<VD>, CR<Graph>)> fn) { finish_vertex_fn = std::move     (fn); return *this; }
    // clang-format on
};


template <typename Graph>
struct boost_lambda_bellman_ford_visitor {
    using ED = typename boost::graph_traits<Graph>::edge_descriptor;

    Func<void(CR<ED>, CR<Graph>)> examine_edge_fn;
    Func<void(CR<ED>, CR<Graph>)> edge_relaxed_fn;
    Func<void(CR<ED>, CR<Graph>)> edge_not_relaxed_fn;
    Func<void(CR<ED>, CR<Graph>)> edge_minimized_fn;
    Func<void(CR<ED>, CR<Graph>)> edge_not_minimized_fn;

    // clang-format off
    void examine_edge       (ED e, CR<Graph> g) { if (examine_edge_fn) { examine_edge_fn             (e, g); } }
    void edge_relaxed       (ED e, CR<Graph> g) { if (edge_relaxed_fn) { edge_relaxed_fn             (e, g); } }
    void edge_not_relaxed   (ED e, CR<Graph> g) { if (edge_not_relaxed_fn) { edge_not_relaxed_fn     (e, g); } }
    void edge_minimized     (ED e, CR<Graph> g) { if (edge_minimized_fn) { edge_minimized_fn         (e, g); } }
    void edge_not_minimized (ED e, CR<Graph> g) { if (edge_not_minimized_fn) { edge_not_minimized_fn (e, g); } }

    boost_lambda_bellman_ford_visitor &set_examine_edge       (Func<void (CR<ED>, CR<Graph>)> fn) { examine_edge_fn = std::move       (fn); return *this; }
    boost_lambda_bellman_ford_visitor &set_edge_relaxed       (Func<void (CR<ED>, CR<Graph>)> fn) { edge_relaxed_fn = std::move       (fn); return *this; }
    boost_lambda_bellman_ford_visitor &set_edge_not_relaxed   (Func<void (CR<ED>, CR<Graph>)> fn) { edge_not_relaxed_fn = std::move   (fn); return *this; }
    boost_lambda_bellman_ford_visitor &set_edge_minimized     (Func<void (CR<ED>, CR<Graph>)> fn) { edge_minimized_fn = std::move     (fn); return *this; }
    boost_lambda_bellman_ford_visitor &set_edge_not_minimized (Func<void (CR<ED>, CR<Graph>)> fn) { edge_not_minimized_fn = std::move (fn); return *this; }
    // clang-format on
};

template <typename Graph>
struct boost_lambda_astar_visitor {
    using VD = typename boost::graph_traits<Graph>::vertex_descriptor;
    using ED = typename boost::graph_traits<Graph>::edge_descriptor;

    Func<void(CR<VD>, CR<Graph>)> initialize_vertex_fn;
    Func<void(CR<VD>, CR<Graph>)> discover_vertex_fn;
    Func<void(CR<VD>, CR<Graph>)> examine_vertex_fn;
    Func<void(CR<ED>, CR<Graph>)> examine_edge_fn;
    Func<void(CR<ED>, CR<Graph>)> edge_relaxed_fn;
    Func<void(CR<ED>, CR<Graph>)> edge_not_relaxed_fn;
    Func<void(CR<ED>, CR<Graph>)> black_target_fn;
    Func<void(CR<VD>, CR<Graph>)> finish_vertex_fn;

    // clang-format off
    void initialize_vertex (VD v, CR<Graph> g) { if (initialize_vertex_fn) { initialize_vertex_fn (v, g); } }
    void discover_vertex   (VD v, CR<Graph> g) { if (discover_vertex_fn) { discover_vertex_fn     (v, g); } }
    void examine_vertex    (VD v, CR<Graph> g) { if (examine_vertex_fn) { examine_vertex_fn       (v, g); } }
    void examine_edge      (ED e, CR<Graph> g) { if (examine_edge_fn) { examine_edge_fn           (e, g); } }
    void edge_relaxed      (ED e, CR<Graph> g) { if (edge_relaxed_fn) { edge_relaxed_fn           (e, g); } }
    void edge_not_relaxed  (ED e, CR<Graph> g) { if (edge_not_relaxed_fn) { edge_not_relaxed_fn   (e, g); } }
    void black_target      (ED e, CR<Graph> g) { if (black_target_fn) { black_target_fn           (e, g); } }
    void finish_vertex     (VD v, CR<Graph> g) { if (finish_vertex_fn) { finish_vertex_fn         (v, g); } }

    boost_lambda_astar_visitor &set_initialize_vertex (Func<void (CR<VD>, CR<Graph>)> fn) { initialize_vertex_fn = std::move (fn); return *this; }
    boost_lambda_astar_visitor &set_discover_vertex   (Func<void (CR<VD>, CR<Graph>)> fn) { discover_vertex_fn = std::move   (fn); return *this; }
    boost_lambda_astar_visitor &set_examine_vertex    (Func<void (CR<VD>, CR<Graph>)> fn) { examine_vertex_fn = std::move    (fn); return *this; }
    boost_lambda_astar_visitor &set_examine_edge      (Func<void (CR<ED>, CR<Graph>)> fn) { examine_edge_fn = std::move      (fn); return *this; }
    boost_lambda_astar_visitor &set_edge_relaxed      (Func<void (CR<ED>, CR<Graph>)> fn) { edge_relaxed_fn = std::move      (fn); return *this; }
    boost_lambda_astar_visitor &set_edge_not_relaxed  (Func<void (CR<ED>, CR<Graph>)> fn) { edge_not_relaxed_fn = std::move  (fn); return *this; }
    boost_lambda_astar_visitor &set_black_target      (Func<void (CR<ED>, CR<Graph>)> fn) { black_target_fn = std::move      (fn); return *this; }
    boost_lambda_astar_visitor &set_finish_vertex     (Func<void (CR<VD>, CR<Graph>)> fn) { finish_vertex_fn = std::move     (fn); return *this; }
    // clang-format on
};
