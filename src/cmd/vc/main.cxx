#include <cassert>
#include <vector>

#include <fmt/base.h>
#include <fmt/ranges.h>

#include <algorithms/connectivity.h>
#include <algorithms/dfs.h>
#include <algorithms/ilst.h>
#include <algorithms/orderings.h>
#include <algorithms/vertex_cover.h>
#include <graph_helpers/graph_helpers.h>
#include <io_helpers/io_helpers.h>

using namespace std;


int main()
{
    // input
    const vector<vector<unsigned>> g{read_simple_graph_from_stdin()};  //< the input graph

    // initialize output variables
    vector<unsigned> cvc;  //< the approximate minimum connected vertex cover
    vector<unsigned> vc;  //< the approximate minimum vertex cover

    // process each connected component
    for (vector<bool> visited(g.size(), false); ; ) {
        vector<unsigned> component_nodes{next_connected_component(g, visited)};
        if (component_nodes.empty())
            break;

        vector<vector<unsigned>> component{compress_node_ids(g, component_nodes)};
        const auto order = unsigned(component.size());  //< the number of vertices in the input graph

        // sort the nodes in descending of their degrees
        unsigned root{order_vertices(component, degree_descending)};  //< root of the DFS tree

        // ILST algorithm
        auto tree = dfs(component, root);  //< eventually an ILST or a non-independence Hamiltonian path
        const bool is_independence{make_ilst_or_hamil_path(component, tree, root)};  //< whether tree is an ILST

        // derive CVC from the ILST output
        const auto approx_min_cvc = ilst_output_to_cvc(component, is_independence, tree, root);
        assert(is_vc(component, approx_min_cvc));
        for (unsigned v{0}; v < order; ++v) {
            if (approx_min_cvc[v])
                cvc.push_back(component_nodes[v]);
        }

        // derive a VC from the CVC tree
        const auto approx_min_vc = cvc_tree_to_vc(component, tree, root);
        assert(is_vc(component, approx_min_vc));
        for (unsigned v{0}; v < order; ++v) {
            if (approx_min_vc[v])
                vc.push_back(component_nodes[v]);
        }
    }

    // output
    fmt::println("{} => {}", fmt::join(cvc, ", "), cvc.size());
    fmt::println("{} => {}", fmt::join(vc, ", "), vc.size());
}
