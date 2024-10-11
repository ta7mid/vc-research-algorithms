#include <algorithm>
#include <vector>

#include <helpers/graph.h>

using namespace std;


bool has_edge(const vector<vector<unsigned>>& g, const unsigned u, const unsigned v)
{
    const auto& uadj = g[u];
    return find(uadj.cbegin(), uadj.cend(), v) != uadj.cend();
}
