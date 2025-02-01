#include <algorithm>
#include <vector>

#include <graph_helpers/graph_helpers.h>

using namespace std;


bool has_edge(const vector<vector<unsigned>>& g, const unsigned u, const unsigned v)
{
    const auto& uadj = g[u];
    return find(uadj.cbegin(), uadj.cend(), v) != uadj.cend();
}

unsigned order_vertices(vector<vector<unsigned>>& g, bool (*const precedes)(const vector<vector<unsigned>>&, const unsigned, const unsigned))
{
    unsigned root{0};
    for (unsigned node{0}; node < g.size(); ++node) {
        auto& neighbors = g[node];
        sort(neighbors.begin(), neighbors.end(), [&](const unsigned u, const unsigned v) {
            return precedes(g, u, v);
        });
        if (precedes(g, node, root))
            root = node;
    }
    return root;
}

vector<vector<unsigned>> compress_node_ids(const vector<vector<unsigned>>& g, vector<unsigned>& kept_nodes)
{
    sort(kept_nodes.begin(), kept_nodes.end());
    vector<vector<unsigned>> res(kept_nodes.size());
    for (unsigned compressed_u{0}; compressed_u < kept_nodes.size(); ++compressed_u) {
        const auto u = kept_nodes[compressed_u];
        for (const auto v : g[u]) {
            if (
                const auto it = lower_bound(kept_nodes.cbegin(), kept_nodes.cend(), v);
                it != kept_nodes.cend() and *it == v
            ) {
                const auto compressed_v = static_cast<unsigned>(it - kept_nodes.cbegin());
                res[compressed_u].push_back(compressed_v);
            }
        }
    }
    return res;
}
