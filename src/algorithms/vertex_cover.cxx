#include <algorithm>
#include <cassert>
#include <limits>
#include <unordered_set>
#include <vector>

#include "vertex_cover.h"
#include <common/constants.h>
#include <algorithms/vertex_cover.h>

using namespace std;


constexpr auto not_a_node = numeric_limits<unsigned>::max();


unordered_set<unsigned> ilst_output_to_cvc(const vector<vector<unsigned>>& g, const bool is_ilst, vector<vector<unsigned>>& ilst, unsigned& root)
{
    unordered_set<unsigned> cvc;

    // take all non-leaf nodes
    for (unsigned v{0}; v < g.size(); ++v) {
        if (ilst[v].size() != 1)
            cvc.insert(v);
    }

    // if it’s a non-indenedence Hamiltonian path, the root is a leaf, but it should be in the CVC tree
    if (not is_ilst)
        cvc.insert(root);

    // modify the tree correspondingly
    for (unsigned v{0}; v < g.size(); ++v) {
        if (cvc.find(v) == cvc.cend()) {
            if (v == root)
                root = delete_leaf(ilst, v);
            else
                (void)delete_leaf(ilst, v);
        }
    }

    return cvc;
}

unsigned delete_leaf(vector<vector<unsigned>>& tree, const unsigned leaf)
{
    assert(tree[leaf].size() == 1);
    const auto parent = tree[leaf][0];
    auto& parent_adj = tree[parent];
    parent_adj.erase(find(parent_adj.begin(), parent_adj.end(), leaf));
    tree[leaf].clear();
    return parent;
}

bool is_vc(const vector<vector<unsigned>>& g, const unordered_set<unsigned>& node_set)
{
    for (unsigned u{0}; u < g.size(); ++u) {
        for (const auto v : g[u]) {  // for each edge (u, v)
            if (node_set.find(u) == node_set.cend() and node_set.find(v) == node_set.cend())
                return false;
        }
    }
    return true;
}

bool is_vc(const vector<vector<unsigned>>& g, const vector<unsigned>& node_list)
{
    unordered_set<unsigned> set(node_list.cbegin(), node_list.cend());
    return is_vc(g, set);
}

unordered_set<unsigned> cvc_tree_to_vc(const vector<vector<unsigned>>& g, vector<vector<unsigned>> cvc_tree, const unsigned root)
{
    const auto n = unsigned(g.size());
    assert(n == cvc_tree.size());

    vector<unsigned> nchildren(n);
    vector<unordered_set<unsigned>> nodes_with_nchildren(n);

    /// mapping: node -> whether the node is incident on a an edge of g that is not in cvc_tree
    vector<bool> covers_nontree_edge(n, false);

    /// mapping: node -> node's parent (or `not_a_node` if node is root) in cvc_tree
    vector<unsigned> parent(n, not_a_node);

    init_data_structures(g, cvc_tree, root, parent, nchildren, nodes_with_nchildren, covers_nontree_edge);

    /// recursively delete the node and its children
    auto delete_node_and_descendents = [&](unsigned node) -> void {
        vector<unsigned> to_delete{node};
        while (not to_delete.empty()) {
            node = to_delete.back();
            auto& neighbors = cvc_tree[node];
            const auto the_parent = parent[node];

            to_delete.pop_back();
            for (const auto child : neighbors) {
                if (child != the_parent)
                    to_delete.push_back(child);
            }

            if (the_parent != not_a_node) {
                neighbors.erase(find(neighbors.begin(), neighbors.end(), the_parent));

                auto& neighbors_of_parent = cvc_tree[the_parent];
                neighbors_of_parent.erase(find(neighbors_of_parent.begin(), neighbors_of_parent.end(), node));
            }
        }
    };

    // From Wikipedia[1]:
    //
    // > For tree graphs, an algorithm finds a minimal vertex cover in polynomial time
    // > by finding the first leaf in the tree and adding its parent to the minimal
    // > vertex cover, then deleting the leaf and parent and all associated edges and
    // > continuing repeatedly until no edges remain in the tree.
    //
    // We use the same approach here, except if a node covers some non-tree edge
    // (i.e. an edge that is on the original graph but not in the cvc_tree), we
    // always include it in the vertex cover.
    //
    // [1] https://en.wikipedia.org/wiki/Vertex_cover#Exact_evaluation

    unordered_set<unsigned> vc;

    while (not nodes_with_nchildren[0].empty()) {
        const auto leaf = *nodes_with_nchildren[0].begin();
        nodes_with_nchildren[0].erase(nodes_with_nchildren[0].begin());

        const auto the_parent = parent[leaf];

        if (covers_nontree_edge[leaf] or the_parent == not_a_node) {
            vc.insert(leaf);
            delete_node_and_descendents(leaf);
        } else {
            vc.insert(the_parent);
            delete_node_and_descendents(the_parent);
        }
    }

    for (unsigned u{0}; u < n; ++u) {
        if (covers_nontree_edge[u])
            vc.insert(u);
    }

    return vc;
}

void init_data_structures(
    const vector<vector<unsigned>>& g,
    const vector<vector<unsigned>>& tree,
    const unsigned root,

    // out params
    vector<unsigned>& parent,
    vector<unsigned>& nchildren,
    vector<unordered_set<unsigned>>& nodes_with_nchildren,
    vector<bool>& covers_nontree_edge
)
{
    const auto n = unsigned(g.size());
    vector<unsigned> next_neighbor(n, 0);
    vector<unsigned> stack{root};
    stack.reserve(n);

    while (not stack.empty()) {
        const auto node = stack.back();
        const auto& neighbors = tree[node];
        const auto degree = neighbors.size();

        auto& neigh_idx = next_neighbor[node];
        while (neigh_idx != degree and next_neighbor[neighbors[neigh_idx]] != 0)
            ++neigh_idx;

        if (neigh_idx == degree) {
            const auto nchilds = degree - (node != root);
            nchildren[node] = static_cast<unsigned>(nchilds);
            nodes_with_nchildren[nchilds].insert(node);
            covers_nontree_edge[node] = degree != g[node].size();
            stack.pop_back();
            continue;
        }

        const auto child = neighbors[neigh_idx];
        ++neigh_idx;
        assert(next_neighbor[child] == 0);
        stack.push_back(child);
        parent[child] = node;
    }
}
