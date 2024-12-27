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
    for (unsigned node {0}; node < g.size(); ++node) {
        auto& uadj = g[node];
        sort(uadj.begin(), uadj.end(), [&](const unsigned u, const unsigned v) {
            return precedes(g, u, v);
        });
        if (precedes(g, uadj[0], root))
            root = uadj[0];
    }
    return root;
}

std::vector<std::vector<unsigned>> compress_node_ids(const std::vector<std::vector<unsigned>>& g, std::vector<unsigned>& kept_nodes)
{
    sort(kept_nodes.begin(), kept_nodes.end());
    vector<vector<unsigned>> res(kept_nodes.size());
    for (unsigned u{0}; u < g.size(); ++u) {
        for (const auto v : g[kept_nodes[u]]) {
            if (
                const auto it = lower_bound(kept_nodes.cbegin(), kept_nodes.cend(), v);
                it != kept_nodes.cend() and *it == v
            ) {
                const auto mapped_id = unsigned(it - kept_nodes.cbegin());
                res[u].push_back(mapped_id);
            }
        }
    }
    return res;
}
