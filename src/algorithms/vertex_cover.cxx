#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <limits>
#include <vector>

#include "vertex_cover.h"
#include <common/constants.h>
#include <algorithms/vertex_cover.h>

using namespace std;

using Bitmask = bitset<max_order>;

constexpr auto non_node = numeric_limits<unsigned>::max();


Bitmask ilst_output_to_cvc(const vector<vector<unsigned>>& g, const bool is_ilst, vector<vector<unsigned>>& ilst, unsigned& root)
{
    Bitmask res;

    // take all non-leaf nodes
    for (unsigned v{0}; v < g.size(); ++v) {
        if (ilst[v].size() != 1)
            res.set(v);
    }

    // if it’s a non-indenedence Hamiltonian path, the root is a leaf, but it should be in the CVC tree
    if (not is_ilst)
        res.set(root);

    // modify the tree correspondingly
    for (unsigned v{0}; v < g.size(); ++v) {
        if (not res.test(v)) {
            if (v == root)
                root = delete_leaf(ilst, v);
            else
                (void)delete_leaf(ilst, v);
        }
    }

    return res;
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

Bitmask cvc_tree_to_vc(const vector<vector<unsigned>>& g, const vector<vector<unsigned>>& cvc_tree, const unsigned root)
{
    assert(any_of(cvc_tree.cbegin(), cvc_tree.cend(), [](const vector<unsigned>& nn) { return nn.size() == 1; }));

    const auto n = unsigned(g.size());

    /// mapping: node -> # of node's children whose subtrees remain to be solved
    vector<unsigned> nchildren_todo(n);

    /// mapping: # -> list of nodes with # children whose subtrees remain to be solved
    vector<vector<unsigned>> nodes_with_nchildren_todo(n - 1);

    /// mapping: node -> whether the node is incident on a an edge of g that is not in cvc_tree
    vector<bool> covers_nontree_edge(n, false);

    /// mapping: node -> node's parent (or -1u if node is root) in cvc_tree
    vector<unsigned> parent_of_node(n, non_node);

    init_data_structures(g, cvc_tree, root, parent_of_node, nchildren_todo, nodes_with_nchildren_todo, covers_nontree_edge);

    /// best_vc_for_subtree[v][false] := smallest of the VCs of the subtree rooted at v.
    /// best_vc_for_subtree[v][true]  := smallest of the VCs, _including_ v, of the subtree rooted at v.
    vector<array<Bitmask, 2>> best_vc_for_subtree(n, {Bitmask{}, Bitmask{}});

    auto& nodes_with_all_children_done = nodes_with_nchildren_todo[0];
    while (not nodes_with_all_children_done.empty()) {
        const auto subtree_root = nodes_with_all_children_done.back();
        nodes_with_all_children_done.pop_back();
        const auto parent = parent_of_node[subtree_root];
        const auto& neighbors = cvc_tree[subtree_root];

        auto& best_vc_incl_root = best_vc_for_subtree[subtree_root][true];
        best_vc_incl_root.set(subtree_root);
        for (const auto neighbor : neighbors) {
            if (neighbor == parent)
                continue;
            // `neighbor` is a child of `subtree_root`
            best_vc_incl_root |= best_vc_for_subtree[neighbor][false];
        }

        auto& best_vc = best_vc_for_subtree[subtree_root][false];
        if (covers_nontree_edge[subtree_root])
            best_vc = best_vc_incl_root;
        else {
            for (const auto neighbor : neighbors) {
                if (neighbor == parent)
                    continue;
                // `neighbor` is a child of `subtree_root`
                best_vc |= best_vc_for_subtree[neighbor][true];
            }

            if (best_vc_incl_root.count() < best_vc.count())
                best_vc = best_vc_incl_root;
        }

        if (parent == non_node) {
            // subtree_root == root, so we're done
            break;
        }

        auto& ntodo = nchildren_todo[parent];
        assert(ntodo > 0);
        auto& old_slot = nodes_with_nchildren_todo[ntodo];

        // the subtree rooted at the child `subtree_root` of `parent` is done,
        old_slot.erase(find(old_slot.begin(), old_slot.end(), parent));
        nodes_with_nchildren_todo[--ntodo].push_back(parent);
    }

    return best_vc_for_subtree[root][false];
}

Bitmask ilst_to_vc(const vector<vector<unsigned>>& g, const vector<vector<unsigned>>& ilst, const unsigned root)
{
    const auto n = unsigned(g.size());

    /// mapping: node -> # of node's children whose subtrees remain to be solved
    vector<unsigned> nchildren_todo(n);

    /// mapping: # -> list of nodes with # children whose subtrees remain to be solved
    vector<vector<unsigned>> nodes_with_nchildren_todo(n - 1);

    /// mapping: node -> whether the node is incident on a an edge of g that is not in ilst
    vector<bool> covers_nontree_edge(n, false);

    /// mapping: node -> node's parent (or -1u if node is root) in ilst
    vector<unsigned> parent_of_node(n, non_node);

    init_data_structures(g, ilst, root, parent_of_node, nchildren_todo, nodes_with_nchildren_todo, covers_nontree_edge);

    /// best_vc_for_subtree[v][false] := smallest of the VCs for the subtree rooted at v.
    /// best_vc_for_subtree[v][true]  := smallest of the VCs _including_ v, for the subtree rooted at v.
    vector<array<Bitmask, 2>> best_vc_for_subtree(n, {Bitmask{}, Bitmask{}});

    auto& nodes_with_all_children_done = nodes_with_nchildren_todo[0];
    while (not nodes_with_all_children_done.empty()) {
        const auto subtree_root = nodes_with_all_children_done.back();
        nodes_with_all_children_done.pop_back();
        const auto parent = parent_of_node[subtree_root];
        const auto& neighbors = ilst[subtree_root];

        auto& best_vc_incl_root = best_vc_for_subtree[subtree_root][true];
        best_vc_incl_root.set(subtree_root);
        for (const auto neighbor : neighbors) {
            if (neighbor == parent)
                continue;
            // `neighbor` is a child of `subtree_root`
            best_vc_incl_root |= best_vc_for_subtree[neighbor][false];
        }

        auto& best_vc = best_vc_for_subtree[subtree_root][false];
        if (covers_nontree_edge[subtree_root])
            best_vc = best_vc_incl_root;
        else {
            for (const auto neighbor : neighbors) {
                if (neighbor == parent)
                    continue;
                // `neighbor` is a child of `subtree_root`
                best_vc |= best_vc_for_subtree[neighbor][true];
            }

            if (best_vc_incl_root.count() < best_vc.count())
                best_vc = best_vc_incl_root;
        }

        if (parent == non_node) {
            // subtree_root == root, so we're done
            break;
        }

        auto& ntodo = nchildren_todo[parent];
        assert(ntodo > 0);
        auto& old_slot = nodes_with_nchildren_todo[ntodo];

        // the subtree rooted at the child `subtree_root` of `parent` is done,
        old_slot.erase(find(old_slot.begin(), old_slot.end(), parent));
        nodes_with_nchildren_todo[--ntodo].push_back(parent);
    }

    return best_vc_for_subtree[root][false];
}

void init_data_structures(
    const vector<vector<unsigned>>& g,
    const vector<vector<unsigned>>& tree,
    const unsigned root,

    // out params
    vector<unsigned>& node_parent,
    vector<unsigned>& level,
    vector<vector<unsigned>>& nodes_with_nchildren_todo,
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
            const auto nchildren = degree - (node != root);
            level[node] = nchildren;
            nodes_with_nchildren_todo[nchildren].push_back(node);
            covers_nontree_edge[node] = degree != g[node].size();
            stack.pop_back();
            continue;
        }

        const auto child = neighbors[neigh_idx];
        ++neigh_idx;
        assert(next_neighbor[child] == 0);
        stack.push_back(child);
        node_parent[child] = node;
    }
}

bool is_vc(const vector<vector<unsigned>>& g, const Bitmask& is_included)
{
    for (unsigned u{0}; u < g.size(); ++u) {
        for (const auto v : g[u]) {  // for each edge (u, v)
            if (not (is_included[u] or is_included[v]))
                return false;
        }
    }
    return true;
}
