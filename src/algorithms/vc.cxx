#include <array>
#include <bitset>
#include <cassert>
#include <limits>
#include <vector>

#include "vc.h"

using namespace std;


/**
 * @pre g is a connected non-ring graph
 * @pre ilst is an independent-leaves spanning tree of g
 * @param g the base graph
 * @param ilst an ILST of g
 * @param root the root of the ILST
 * @return a vertex cover of g
 */
bitset<max_n> ilst_to_vc(const vector<vector<unsigned>>& g, const vector<vector<unsigned>>& ilst, const unsigned root)
{
    const auto n = unsigned(ilst.size());

    /// mapping: node -> # of node's children whose subtrees remain to be solved
    vector<unsigned> num_proper_subtrees_to_do(n);

    /// mapping: # -> list of nodes with # children whose subtrees remain to be solved
    vector<vector<unsigned>> nodes_with_num_proper_subtrees_to_do(n - 1);

    /// mapping: node -> whether the node is incident on a an edge of g that is not in ilst
    vector<bool> covers_nontree_edge(n, false);

    /// mapping: node -> node's parent (or -1u if node is root) in ilst
    vector<unsigned> parent(n, numeric_limits<unsigned>::max());

    // DFS to populate the data structures
    {
        vector<unsigned> next_neighbor(n, 0);
        vector<unsigned> stack{root};
        stack.reserve(n);
        while (not stack.empty()) {
            const auto the_parent = stack.back();
            const auto& neighbors = ilst[the_parent];
            const auto degree_in_tree = neighbors.size();
            auto& neigh_idx = next_neighbor[the_parent];
            while (neigh_idx != degree_in_tree and next_neighbor[neighbors[neigh_idx]] != 0)
                ++neigh_idx;
            if (neigh_idx == degree_in_tree) {
                const auto nchildren = degree_in_tree - (the_parent != root);
                num_proper_subtrees_to_do[the_parent] = nchildren;
                nodes_with_num_proper_subtrees_to_do[nchildren].push_back(the_parent);
                covers_nontree_edge[the_parent] = degree_in_tree != g[the_parent].size();
                stack.pop_back();
                continue;
            }
            const auto child = neighbors[neigh_idx];
            ++neigh_idx;
            assert(next_neighbor[child] == 0);
            stack.push_back(child);
            parent[child] = the_parent;
        }
    }

    /// best_vc_for_subtree[v][false] := smallest of the VCs for the subtree rooted at v.
    /// best_vc_for_subtree[v][true]  := smallest of the VCs _including_ v, for the subtree rooted at v.
    vector<array<bitset<max_n>, 2>> best_vc_for_subtree(n, {bitset<max_n>{}, bitset<max_n>{}});

    auto& lowest_slot = nodes_with_num_proper_subtrees_to_do[0];
    while (not lowest_slot.empty()) {
        const auto subtree_root = lowest_slot.back();
        lowest_slot.pop_back();
        const auto parent_to_root = parent[subtree_root];
        const auto& neighbors = ilst[subtree_root];

        auto& best_vc_including_root = best_vc_for_subtree[subtree_root][true];
        best_vc_including_root.set(subtree_root);
        for (const auto neighbor : neighbors) {
            if (neighbor == parent_to_root)
                continue;
            assert(parent[neighbor] == subtree_root);
            best_vc_including_root |= best_vc_for_subtree[neighbor][false];
        }

        auto& best_vc_optioanlly_including_root = best_vc_for_subtree[subtree_root][false];
        if (covers_nontree_edge[subtree_root])
            best_vc_optioanlly_including_root = best_vc_including_root;
        else {
            for (const auto neighbor : neighbors) {
                if (neighbor == parent_to_root)
                    continue;
                assert(parent[neighbor] == subtree_root);
                best_vc_optioanlly_including_root |= best_vc_for_subtree[neighbor][true];
            }

            if (best_vc_including_root.count() < best_vc_optioanlly_including_root.count())
                best_vc_optioanlly_including_root = best_vc_including_root;
        }

        if (parent_to_root == numeric_limits<unsigned>::max())  // root done
            break;
        auto& ntodo = num_proper_subtrees_to_do[parent_to_root];
        assert(ntodo > 0);

        auto& parent_old_slot = nodes_with_num_proper_subtrees_to_do[ntodo];
        parent_old_slot.erase(find(parent_old_slot.begin(), parent_old_slot.end(), parent_to_root));

        nodes_with_num_proper_subtrees_to_do[--ntodo].push_back(parent_to_root);
    }

    return best_vc_for_subtree[root][false];
}
