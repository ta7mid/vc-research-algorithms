#include <algorithm>
#include <vector>

#include <helpers/graph.h>

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
