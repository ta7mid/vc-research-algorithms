#include <cassert>
#include <fstream>
#include <istream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <fmt/format.h>

#include "io.h"
#include <common/constants.h>
#include <helpers/io.h>

using namespace std;


vector<vector<unsigned>> read_simple_graph(const char* const graph_representation)
{
    istringstream iss{graph_representation};
    return read(iss);
}

vector<vector<unsigned>> read_simple_graph_from_file(const char* const filepath)
{
    ifstream fin{filepath};
    assert(fin and fin.is_open());
    return read(fin, fmt::format(" in file `{}`", filepath));
}

vector<vector<unsigned>> read(istream& iss, const string& additional_ctx)
{
    unsigned n, m;
    iss >> n >> m;

    // validate n
    if (n < min_n)
        throw invalid_argument{fmt::format("# of nodes must be at least min_n={}, but n={} was input{}", min_n, n, additional_ctx)};
    if (n > max_n)
        throw invalid_argument{fmt::format("# of nodes must not exceed max_n={}, but n={} was input{}", max_n, n, additional_ctx)};

    vector<vector<unsigned>> g(n);
    while (m--) {
        unsigned u, v;
        iss >> u >> v;

        // validate u and v
        const bool u_is_bad{u >= n};
        const bool v_is_bad{v >= n};
        if (u_is_bad or v_is_bad) {
            auto msg = fmt::format("invalid node ID(s) provided{}\n", additional_ctx);
            if (u_is_bad)
                msg += fmt::format("\tu = {} is not in the range [0, {})", u, n);
            if (v_is_bad)
                msg += fmt::format("\tv = {} is not in the range [0, {})", v, n);
            throw invalid_argument{msg};
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
