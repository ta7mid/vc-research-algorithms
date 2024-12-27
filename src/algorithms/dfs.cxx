#include <stdexcept>
#include <vector>

#include <algorithms/dfs.h>

using namespace std;


vector<vector<unsigned>> dfs(const vector<vector<unsigned>>& g, const unsigned source)
{
    const auto n = unsigned(g.size());
    if (source >= n)
        throw invalid_argument{"invalid source node ID for DFS"};
    vector<vector<unsigned>> tree(n);
    vector<unsigned> next_neigh_idx(n, 0);  // next_neigh_idx[v] == 0 => v is unvisited
    vector<unsigned> stack{source};
    stack.reserve(n);
    while (not stack.empty()) {
        const auto parent = stack.back();
        const auto& neighbors = g[parent];
        auto& child_idx = next_neigh_idx[parent];
        while (child_idx != neighbors.size() and next_neigh_idx[neighbors[child_idx]] != 0)
            ++child_idx;
        if (child_idx == neighbors.size()) {
            stack.pop_back();
            continue;
        }
        const auto child = neighbors[child_idx];
        ++child_idx;
        stack.push_back(child);
        tree[parent].push_back(child);
        tree[child].push_back(parent);
    }
    return tree;
}
