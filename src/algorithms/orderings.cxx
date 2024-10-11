#include <vector>

using namespace std;


bool degree_descending(const vector<vector<unsigned>>& g, const unsigned u, const unsigned v)
{
    if (g[u].size() != g[v].size())
        return g[u].size() > g[v].size();
    return u < v;
}
