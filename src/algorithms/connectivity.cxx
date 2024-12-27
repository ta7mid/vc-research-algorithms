#include <vector>

#include <algorithms/connectivity.h>

using namespace std;


vector<unsigned> next_connected_component(const vector<vector<unsigned>>& g, vector<bool>& visited)
{
    vector<unsigned> component_nodes;
    const auto n = unsigned(g.size());
    const auto root = unsigned(find(visited.cbegin(), visited.cend(), false) - visited.cbegin());

    if (root == n)
        return component_nodes;

    visited[root] = true;
    component_nodes.push_back(root);
    vector<unsigned> stack{root};
    stack.reserve(n);
    vector<unsigned> next_neigh_idx(n, 0);  // (next_neigh_idx[v] != 0) == visited[v]

    while (not stack.empty()) {
        const auto parent = stack.back();
        const auto& neighbors = g[parent];
        auto& child_idx = next_neigh_idx[parent];

        while (child_idx != neighbors.size() and visited[neighbors[child_idx]])
            ++child_idx;

        if (child_idx == neighbors.size()) {
            stack.pop_back();
            continue;
        }

        const auto child = neighbors[child_idx];
        ++child_idx;
        visited[child] = true;
        component_nodes.push_back(child);
        stack.push_back(child);
    }

    return component_nodes;
}


bool is_connected(const vector<vector<unsigned>>& g)
{
    const auto n = unsigned(g.size());
    vector<unsigned> next_neigh_idx(n, 0);  // next_neigh_idx[v] == 0 => v is unvisited
    vector<unsigned> stack{0};
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
    }

    for (unsigned v{0}; v < n; ++v) {
        if (g[v].size() != next_neigh_idx[v])
            return false;
    }

    return true;
}
