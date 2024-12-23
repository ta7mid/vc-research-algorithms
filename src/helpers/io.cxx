#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

#include <fmt/format.h>

#include "io.h"
#include <common/constants.h>
#include <helpers/io.h>

using namespace std;


vector<vector<unsigned>> read_simple_graph(const char* const graph_representation)
{
    istringstream iss{graph_representation};
    return read_simple_graph(iss);
}

vector<vector<unsigned>> read_simple_graph_from_file(const char* const filepath)
{
    ifstream fin{filepath};
    assert(fin and fin.is_open());
    return read_simple_graph(fin);
}

vector<vector<unsigned>> read_simple_graph_from_stdin()
{
    return read_simple_graph(cin);
}

vector<vector<unsigned>> read_simple_graph(istream& iss)
{
    unsigned n, m;
    iss >> n >> m;
    if (n < min_order or n > max_order) {
        throw domain_error{
            fmt::format("graph order out of range [{},{}]", min_order, max_order)
        };
    }

    vector<vector<unsigned>> g(n);

    while (m--) {
        unsigned u, v;

        iss >> u;
        if (u >= n) {
            throw domain_error{
                fmt::format("node ID out of range [0,{})", fmt::group_digits(n))
            };
        }

        iss >> v;
        if (v >= n) {
            throw domain_error{
                fmt::format("node ID out of range [0,{})", fmt::group_digits(n))
            };
        }

        // skip self-loops
        if (u == v)
            continue;

        auto& uadj = g[u];

        // skip multiple edges between the same pair of vertices
        if (find(uadj.cbegin(), uadj.cend(), v) != uadj.cend())
            continue;

        uadj.push_back(v);
        g[v].push_back(u);
    }

    return g;
}
