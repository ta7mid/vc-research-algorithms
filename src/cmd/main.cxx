#include <bitset>
#include <vector>

#include <fmt/core.h>

#include <algorithms/dfs.h>
#include <algorithms/ilst.h>
#include <algorithms/orderings.h>
#include <algorithms/vc.h>
#include <common/constants.h>
#include <helpers/graph.h>
#include <helpers/io.h>

using namespace std;


int main()
{
    // input
    vector<vector<unsigned>> g{read_simple_graph_from_stdin()};
    const auto order = unsigned(g.size());

    // sort the nodes in descending of their degrees
    unsigned root{order_vertices(g, degree_descending)};

    // ILST algorithm
    auto tree = dfs(g, root);
    const bool is_ilst{make_ilst_or_hamil_path(g, tree, root)};

    bitset<max_order> approx_minvc;
    if (is_ilst) {  // g is not a ring graph and tree is an ILST of it
        // run the modified DP algorithm for MinVC of trees
        approx_minvc = ilst_to_vc(g, tree, root);
    }
    else {  // tree is a Hamiltonian path for the ring graph g
        // add all nodes but the root
        for (unsigned v{0}; v < order; ++v) {
            if (v != root)
                approx_minvc.set(v);
        }
    }

    // output
    for (unsigned v{0}; v < order; ++v) {
        if (approx_minvc[v])
            fmt::print("{} ", v);
    }
    fmt::println("=> {}", approx_minvc.count());
}
