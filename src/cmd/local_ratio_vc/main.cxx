#include <vector>

#include <fmt/base.h>
#include <fmt/ranges.h>

#include <io_helpers/io_helpers.h>

using namespace std;


int main()
{
    // input
    const vector<vector<unsigned>> g{read_simple_graph_from_stdin()};  //< the input graph

    vector<unsigned> vc;  //< the approximate minimum vertex cover

    vector<int> cost(g.size(), 1);
    vector<bool> in_cover(g.size(), false);

    for (unsigned u{0}; u < g.size(); ++u) {
        if (in_cover[u])
            continue;

        for (const auto v : g[u]) {
            if (in_cover[v])
                continue;

            if (cost[u] <= cost[v]) {
                in_cover[u] = true;
                vc.push_back(u);
                cost[v] -= cost[u];
            }
            else {
                in_cover[v] = true;
                vc.push_back(v);
                cost[u] -= cost[v];
            }

            break;
        }
    }

    // output
    fmt::println("{} => {}", fmt::join(vc, ", "), vc.size());
}
