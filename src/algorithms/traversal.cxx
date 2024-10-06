#include <cassert>
#include <vector>

#include <algorithms/traversal.h>

using namespace std;


vector<vector<unsigned>> dfs(const vector<vector<unsigned>>& adj, unsigned root)
{
    const auto n = unsigned(adj.size());
    vector<vector<unsigned>> tree(n);
    vector<unsigned> neigh_offs(n, 0);  // neigh_offs[v] == 0 => v is unvisited
    vector<unsigned> stack{root};
    stack.reserve(n);
    while (not stack.empty()) {
        const auto parent = stack.back();
        const auto& neighbors = adj[parent];
        auto& child_idx = neigh_offs[parent];
        while (child_idx != neighbors.size() and neigh_offs[neighbors[child_idx]] != 0)
            ++child_idx;
        if (child_idx == neighbors.size()) {
            stack.pop_back();
            continue;
        }
        const auto child = neighbors[child_idx];
        ++child_idx;
        assert(neigh_offs[child] == 0);
        stack.push_back(child);
        tree[parent].push_back(child);
        tree[child].push_back(parent);
    }
    return tree;
}
