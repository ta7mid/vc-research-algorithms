#include <cassert>
#include <stdexcept>
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
    vector<vector<unsigned>> g{read_simple_graph_from_stdin()};  //< the input graph
    if (not is_connected(g))
        throw domain_error{"not a connected graph"};
    const auto order = unsigned(g.size());  //< the number of vertices in the input graph

    // sort the nodes in descending of their degrees
    unsigned root{order_vertices(g, degree_descending)};  //< root of the DFS tree

    // ILST algorithm
    auto tree = dfs(g, root);  //< eventually an ILST or a non-independence Hamiltonian path
    const bool is_independence{make_ilst_or_hamil_path(g, tree, root)};  //< whether tree is an ILST

    // derive CVC from the ILST output
    const auto approx_min_cvc = ilst_output_to_cvc(g, is_independence, tree, root);
    assert(is_vc(g, approx_min_cvc));

    // output
    fmt::println("{} => {}", fmt::join(approx_min_cvc, ", "), approx_min_cvc.size());
}
